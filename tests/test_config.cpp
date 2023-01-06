//
// Created by 33145 on 2023/1/6.
//
#include "../sylar/log.h"
#include "../sylar/config.h"
#include <iostream>
sylar::ConfigVar<int>::ptr g_int_value_config = sylar::Config::LookUp("system.port", (int)8080, "system port");
int main(int argc, char** argv) {
  SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
  SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->toString();
  return 0;
}