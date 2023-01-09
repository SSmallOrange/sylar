//
// Created by 33145 on 2023/1/3.
//
#include <iostream>
#include <thread>
#include "../sylar/log.h"
#include "../sylar/util.h"
#include "../sylar/config.h"

using namespace std;
int main(int argc, char** argv) {

   // std::cout << "hello wrold" << std::endl;
  sylar::Logger::ptr logger(new sylar::Logger);
  // std::cout << "hello wrold" << std::endl;
  sylar::StdoutLogAppender::ptr std_fmt= make_shared<sylar::StdoutLogAppender>();
  sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
  std_fmt->setFormatter(fmt);
  logger->addAppender(std_fmt);

  sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
  sylar::LogFormatter::ptr fmtt(new sylar::LogFormatter("%d%T%p%T%m%n"));
  file_appender->setFormatter(fmtt);
  file_appender->setLevel(sylar::LogLevel::ERROR);

  logger->addAppender(file_appender);

  SYLAR_LOG_INFO(logger) << "test macro";
  SYLAR_LOG_ERROR(logger) << "test macro error";

  SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

  auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
  int a = 0;
  SYLAR_LOG_INFO(l) << typeid(a).name();


   // std::cout << "hello wrold" << std::endl;
  /*time_t time_seconds = time(0);
  struct tm now_time;
  localtime_r(&time_seconds, &now_time);

  printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
         now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);*/

  return 0;
}
