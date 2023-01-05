//
// Created by 33145 on 2023/1/4.
//

#ifndef SYLAR_UTIL_H
#define SYLAR_UTIL_H

#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

namespace sylar {

pid_t GetThreadId();
uint32_t GetFiberId();

}
#endif //SYLAR_UTIL_H
