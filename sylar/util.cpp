//
// Created by 33145 on 2023/1/4.
//
#include "util.h"

namespace sylar {
  pid_t GetThreadId() { return syscall(SYS_gettid); }
  uint32_t GetFiberId() { return 0; }
}
