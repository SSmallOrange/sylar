//
// Created by 33145 on 2023/1/3.
//

/*
 * mypoint
  * Logger(对外接口)
      |
      |   (调用Logger->log对LogEvent进行输出)
      |
      log() : 检查m_appenders (LogAppender) 对每个输出路径进行输出
	          即对每个路径调用LogAppender->log()
                                |
                                |
		        LogAppender->log()是一个虚接口，外面有Stdout和Fileout的继承
                    |
                    |
      每个LogAppender有一个成员m_formatter负责该方向日志输出的格式
                                  |
                                  |
					通过m_formatter调用LogFormatter->format()接口负责将LogEvent按照相应格式输出
                                                                        |
                                                                        |
												相应格式：LogFormatter中有vector<FormatItem::ptr>：负责存储该格式要输出的内容，比如在Init()时，检查到格式中有%d
												则会申请一个DateTimeFormatItem对象，在输出时只要调用该对象的format接口就行             |
                                                                                                        |
                                                                                  Init()在Logger接口初始化时被调用， 获得一个默认的格式
 * */

#ifndef SYLAR_LOG_H
#define SYLAR_LOG_H

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>  // 用流的方式实现日志输出
#include <fstream>
#include <vector>
#include <map>
#include "util.h"
#include "singleton.h"
/*
 * mypoint: 关于流相关的宏： 这里用wrap的原因是，wrap作为临时对象，在使用完后直接析构，触发日志写入，然而日志本身的智能指针，
 *                  如果声明在主函数里面，程序不结束就永远无法释放，LogEventWrap在if语句结束后会结束生命周期调用析构函数实现打印
 *                  这里很巧妙的利用了局部变量的生命周期实现了打印，SYLAR_LOG_LEVEL宏在if语句内部构造了局部变量LogEventWrap
 * */
#define SYLAR_LOG_LEVEL(logger, level) \
  if (logger->getLevel() <= level)    \
    sylar::LogEventWarp(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, __FILE__, __LINE__, 0, sylar::GetThreadId(), \
                 sylar::GetFiberId(), time(nullptr)))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::Level::FATAL)


#define SYLAR_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWarp(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, sylar::GetThreadId(),\
                sylar::GetFiberId(), time(nullptr)))).getEvent()->format(fmt, __VA_ARGS__)

#define SYLAR_LOG_FMT_DEBUG(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::INFO, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_WARN(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::WARN, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::ERROR, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::FATAL, fmt, __VA_ARGS__)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()

namespace sylar {
  class Logger;

// 日志级别
  class LogLevel {
  public:
    enum Level{ UNKNOW = 0, DEBUG = 1, INFO, WARN, ERROR, FATAL };
    static const char* ToString(LogLevel::Level level);
  };

// 日志事件  mypoint: 相当于一个日志的结构体，包含一个日志所需要的全部内容（时间、内容等）
  class LogEvent {
  public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t m_line, uint32_t elapse,
             uint32_t thread_id, uint32_t fiber_id, uint64_t time);
    ~LogEvent() = default;

    const char* getFile() const { return m_file; }
    int32_t getLine() const { return m_line; }
    uint32_t getElapse() const { return m_elapse; }
    uint32_t getThreadId() const { return m_threadId; }
    uint32_t getFiberId() const { return m_fiberId; }
    uint64_t getTime() const { return m_time; }
    std::string getContent() const { return m_ss.str(); }
    std::shared_ptr<Logger> getLogger() const { return m_logger; }
    LogLevel::Level getLevel() const {return m_level; }

    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);

    std::stringstream& getSS() { return m_ss; }
  private:
    const char* m_file = nullptr;  // 文件
    int32_t m_line = 0;            // 行号
    uint32_t m_elapse = 0;         // 程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;       // 线程ID
    uint32_t m_fiberId = 0;        // 协程ID
    uint64_t m_time = 0;           // 时间戳
    std::stringstream m_ss;        // 内容

    std::shared_ptr<Logger> m_logger;  // 要写到的目标对象
    LogLevel::Level m_level;
  };

  class LogEventWarp {
  public:
    LogEventWarp(LogEvent::ptr event);
    ~LogEventWarp();

    std::stringstream& getSS();
    LogEvent::ptr getEvent() { return m_event; }
  private:
    LogEvent::ptr m_event;
  };

// 日志格式
  class LogFormatter {
  public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    // %t   %threadID %m%n
    std::string format(const std::shared_ptr<Logger>& logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
  public:
    class FormatItem {
    public:
      FormatItem(const std::string& fmt = "") {}
      typedef std::shared_ptr<FormatItem> ptr;
      virtual ~FormatItem() = default;
      virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };
    void Init();
  private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
  };

// 日志输出位置
  class LogAppender {
  public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender() = default;
    virtual ~LogAppender() = default;
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
    LogFormatter::ptr getFormatter() const { return m_formatter; }

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) { m_level = val; }
  protected:
    LogLevel::Level m_level = LogLevel::Level::DEBUG;
    LogFormatter::ptr m_formatter;
  };

// 日志定义类别  mypoint ：负责对外接口
  class Logger : public std::enable_shared_from_this<Logger> {
  public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string &name = "root");
    void log(LogLevel::Level level, const LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(const LogAppender::ptr& appender);
    void delAppender(const LogAppender::ptr& appender);
    [[nodiscard]] LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) { m_level = val; }

    const std::string& getName() const { return m_name; }

  private:
    std::string m_name;       // 日志名称
    LogLevel::Level m_level;  //只有满足日志级别的才会被输出
    std::list<LogAppender::ptr> m_appenders;         //Appender集合
    LogFormatter::ptr m_formatter;
  };
// 输出到控制台的Appender
  class StdoutLogAppender : public LogAppender {
  public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
  private:
  };

// 输出到文件的Appender mypoint: 可能要在析构函数中关闭文件描述符，但是代码里好像没写
  class FileLogAppender : public LogAppender {
  public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;

    // 重新打开文件， 打开成功返回true
    bool reopen();
  private:
    std::string m_filename;
    std::ofstream m_filestream;
  };

  class LoggerManager {
  public:
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);
    void init();
    Logger::ptr getRoot() const { return m_root; }
  private:
    /// 日志器容器
    std::map<std::string, Logger::ptr> m_loggers;
    /// 主日志器
    Logger::ptr m_root;
  };

  typedef sylar::Singleton<LoggerManager> LoggerMgr;

}

#endif //SYLAR_LOG_H
