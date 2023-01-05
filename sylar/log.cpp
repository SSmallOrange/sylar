//
// Created by 33145 on 2023/1/3.
//
#include "log.h"
#include <map>
#include <functional>
#include <iostream>
#include <time.h>
#include <string.h>

namespace sylar {
  const char* LogLevel::ToString(LogLevel::Level level) {
    switch (level) {
#define XX(name) \
      case LogLevel::name: \
        return #name;      \
        break;
      XX(DEBUG);
      XX(INFO);
      XX(WARN);
      XX(ERROR);
      XX(FATAL);
#undef XX
      default:
        return "UNKNOW";
    }
    return "UNKNOW";
  }

  class MessageFormatItem : public LogFormatter::FormatItem {
  public:
    MessageFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getContent();
    }
  };

  class LevelFormatItem : public LogFormatter::FormatItem {
  public:
    LevelFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      // std::cout << "levelformatItem" << std::endl;
      os << LogLevel::ToString(level);
    }
  };

  class ElapseFormatItem : public LogFormatter::FormatItem {
  public:
    ElapseFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getElapse();
    }
  };

  class NameFormatItem : public LogFormatter::FormatItem {
  public:
    NameFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << logger->getName();
    }
  };

  class ThreadIdFormatItem : public LogFormatter::FormatItem {
  public:
    ThreadIdFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getThreadId();
    }
  };

  class FiberIdFormatItem : public LogFormatter::FormatItem {
  public:
    FiberIdFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getFiberId();
    }
  };

  class DateTimeFormatItem : public LogFormatter::FormatItem {
  public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S") : m_format(format) {
      if (m_format.empty()) {
        m_format = "%Y-%m-%d %H:%M:%S";
      }
    }
    // mypoint 一些时间相关的函数
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      struct tm tm;
      time_t time = event->getTime();
      // mypoint: _r版本的函数基本都是线程安全的
      localtime_r(&time, &tm);
      char buf[64];
      strftime(buf, sizeof(buf), m_format.c_str(), &tm);
      os << buf;
    }
  private:
    std::string m_format;
  };

  class FileNameFormatItem : public LogFormatter::FormatItem {
  public:
    FileNameFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getFile();
    }
  };

  class LineFormatItem : public LogFormatter::FormatItem {
  public:
    LineFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << event->getLine();
    }
  };

  class NewLineFormatItem : public LogFormatter::FormatItem {
  public:
    NewLineFormatItem(const std::string &str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << std::endl;
    }
  };

  class StringFormatItem : public LogFormatter::FormatItem {
  public:
    StringFormatItem(const std::string& str) : m_string(str) {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << m_string;
    }
  private:
    std::string m_string;
  };

  class TableFormatItem : public LogFormatter::FormatItem {
  public:
    TableFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
      os << "  ";
    }
  private:
    std::string m_string;
  };

  Logger::Logger(const std::string &name) :
          m_name(name),
          m_level(LogLevel::Level::DEBUG) {
    m_formatter.reset(new LogFormatter("%d%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
  }

  void Logger::log(LogLevel::Level level, const LogEvent::ptr event) {
    if (level >= m_level) {
      // std::cout << "aaa" << std::endl;
      auto self = shared_from_this();
      // std::cout << "aaa" << std::endl;
      if(!m_appenders.empty()) {
        for(auto& i : m_appenders) {
          i->log(self, level, event);
        }
      }
    }
  }

  void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::DEBUG, event);
  }

  void Logger::info(LogEvent::ptr event) {
    log(LogLevel::INFO, event);
  }

  void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::WARN, event);
  }

  void Logger::error(LogEvent::ptr event) {
    log(LogLevel::ERROR, event);
  }

  void Logger::fatal(LogEvent::ptr event) {
    log(LogLevel::FATAL, event);
  }

  void Logger::addAppender(const LogAppender::ptr& appender) {
    if (!appender->getFormatter()) {
      appender->setFormatter(m_formatter);
    }
    // std::cout << "addAppender" << std::endl;
    m_appenders.push_back(appender);
  }

  void Logger::delAppender(const LogAppender::ptr& appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end(); it++) {
      if (appender == *it) {
        m_appenders.erase(it);
        break;
      }
    }
  }

  FileLogAppender::FileLogAppender(const std::string& filename) : m_filename(filename) { reopen(); }

  void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
      // std::cout << "FileLogAppender::log" << std::endl;
      if (!m_formatter->format(m_filestream, logger, level, event)) {
        // std::cout << "error" << std::endl;
      }
    }
  }

  bool FileLogAppender::reopen() {
    if (m_filestream) {
      m_filestream.close();
    }
    // std::cout << m_filename << std::endl;
    m_filestream.open(m_filename);
    return !!m_filestream;
  }

  void StdoutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
      std::cout << m_formatter->format(logger, level, event);
    }
  }

  LogFormatter::LogFormatter(const std::string &pattern) : m_pattern(pattern) {
    // std::cout << "hello this world" << std::endl;
    Init();
  }

  // %xxx %xxx{xxx} %%
  void LogFormatter::Init() {
    // str, format, type
    std::vector<std::tuple<std::string, std::string , int>> vec;
    size_t last_pos = 0;  // 上次位置
    std::string nstr;
    // mypoint: 默认要解析的格式： "%d [%p] <%f:%l>   %m %n"
    for (size_t i = 0; i < m_pattern.size(); ++i) {
      if (m_pattern[i] != '%') {
        nstr.append(1, m_pattern[i]);
        continue;
      }
      // mypoint: 这里应该要i++，不然可能会出现误判
      if (i + 1 < m_pattern.size() && m_pattern[i + 1] == '%') {
        nstr.append(1, '%');
        continue;
      }
      std::string str;
      std::string fmt;
      size_t n = i + 1;
      int fmt_status = 0;  // 记录状态
      size_t fmt_begin = 0;
      while (n < m_pattern.size()) {
        if (!isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}') {
          str = m_pattern.substr(i + 1, n - i - 1);
          break;
        }
        if (fmt_status == 0) {
          if (m_pattern[n] == '{') {
            str = m_pattern.substr(i + 1, n - i - 1);
            fmt_status = 1;  // 解析格式
            fmt_begin = n++;
            continue;
          }
        }
        if (fmt_status == 1) {
          if (m_pattern[n] == '}') {
            fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
            fmt_status = 0;
            ++n;
            break;
          }
        }
        ++n;
        if(n == m_pattern.size()) {
          if(str.empty()) {
            str = m_pattern.substr(i + 1);
          }
        }
      }
      if (fmt_status == 0) {
        if (!nstr.empty()) {
          vec.emplace_back(nstr, "", 0);
          nstr.clear();
        }
        // str = m_pattern.substr(i + 1, n - i - 1);
        vec.emplace_back(str, fmt, 1);
        i = n - 1;
      } else if (fmt_status == 1) {
        std::cout << "pattern parse error: " << m_pattern << m_pattern.substr(i) << std::endl;
        vec.emplace_back("<<pattern_error>>", fmt, 0);
      }
    }
    if (!nstr.empty()) {
      vec.emplace_back(nstr, "", 0);
    }
    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)>> s_format_items = {
#define XX(str, C) \
            {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}

            XX(m, MessageFormatItem),
            XX(p, LevelFormatItem),
            XX(r, ElapseFormatItem),
            XX(c, NameFormatItem),
            XX(t, ThreadIdFormatItem),
            XX(n, NewLineFormatItem),
            XX(d, DateTimeFormatItem),
            XX(f, FileNameFormatItem),
            XX(l, LineFormatItem),
            XX(T, TableFormatItem),
            XX(F, FiberIdFormatItem)
#undef XX
    };
    // 三元组
    for (auto& i : vec) {
      if (std::get<2>(i) == 0) {
        m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
      } else {
        auto it = s_format_items.find(std::get<0>(i));
        if (it == s_format_items.end()) {
          m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
        } else {
          m_items.push_back(it->second(std::get<1>(i)));
        }
      }
      // std::cout << "(" <<std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" <<std::endl;
    }
  }

  std::string LogFormatter::format(const std::shared_ptr<Logger>& logger, LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for (auto& i : m_items) {
      i->format(ss, logger, level, event);
    }
    return ss.str();
  }

  std::ostream &
  LogFormatter::format(std::ostream &ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    for(auto& i : m_items) {
      // std::cout << "LogFormatter::format" << std::endl;
      i->format(ofs, logger, level, event);
    }
    return ofs;
  }

  LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char *file, int32_t line, uint32_t elapse, uint32_t thread_id,
                     uint32_t fiber_id, uint64_t time) :
          m_level(level),
          m_file(file),
          m_line(line),
          m_elapse(elapse),
          m_threadId(thread_id),
          m_fiberId(fiber_id),
          m_time(time),
          m_logger(logger) {}

  void LogEvent::format(const char *fmt, ...) {
    va_list al;  // 初始化一个能指向可变长参数列表的指针
    va_start(al, fmt);  // fmt为最后一个指定参数，该宏将al指向可变长参数列表的开头
    format(fmt, al);
    va_end(al);  // 将al置空
  }

  void LogEvent::format(const char *fmt, va_list al) {
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if (len != -1) {
      m_ss << std::string(buf, len);
      free(buf);
    }
  }

  LogEventWarp::LogEventWarp(LogEvent::ptr event) : m_event(event) {}

  std::stringstream& LogEventWarp::getSS() {
    return m_event->getSS();
  }

  LogEventWarp::~LogEventWarp() {
    m_event->getLogger()->log(m_event->getLevel(), m_event);
  }

  LoggerManager::LoggerManager() {
    m_root.reset(new Logger);

    m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));
  }

  Logger::ptr LoggerManager::getLogger(const std::string &name) {
    auto it = m_loggers.find(name);
    return it == m_loggers.end() ? m_root : it->second;
  }
}
