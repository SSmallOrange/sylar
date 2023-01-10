//
// Created by 33145 on 2023/1/10.
//
#include "thread.h"

#include <utility>
#include "log.h"
#include "util.h"

namespace sylar {

  // 有且只有 thread_local 关键字修饰的变量具有线程（thread）周期
  // 这些变量在线程开始的时候被生成，在线程结束的时候被销毁，并且每一个线程都拥有一个独立的变量实例
  static thread_local Thread* t_thread = nullptr;
  static thread_local std::string t_thread_name = "UNKNOW";

  // 弹幕：    这里又出现前面的不同文件的静态变量的初始化顺序问题了
  //     g_logger应该加在log。cpp里面确定初始化顺序
  static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

  Thread *Thread::GetThis() {
    return t_thread;
  }

  const std::string &Thread::GetThreadName() {
    return t_thread_name;
  }

  void Thread::SetName(const std::string &name) {
    if (t_thread) {
      t_thread->m_name = name;
    }
    t_thread_name = name;
  }

  void* Thread::run(void* arg) {
    Thread* thread = (Thread*)arg;
    t_thread = thread;
    t_thread_name = thread->getName();
    thread->m_id = sylar::GetThreadId();
    // 设置线程名称。。。pthread_self() 获取调用线程的线程ID
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());

    std::function<void()> cb;
    cb.swap(thread->m_cb);
    thread->m_semaphore.notify();
    cb();
    return nullptr;
  }
  Thread::Thread(std::function<void()> cb, const std::string &name) {
    if(name.empty()) {
      m_name = "UNKNOW";
    }
    m_name = name;
    m_cb = std::move(cb);
    int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);
    if (rt) {
      SYLAR_LOG_ERROR(g_logger) << "pthread_create thread fail, rt = " << rt
                                << " name: " << name;
      throw std::logic_error("pthread_create error");
    }
    // 确保在构造函数退出之后线程已经开始执行从而达到函数执行顺序与构造顺序相同的目的
    m_semaphore.wait();
  }

  Thread::~Thread() {
    if (m_thread) {
      //1. pthread_join是一个阻塞函数，调用方会阻塞到pthread_join所指定的tid的线程结束后才被回收
      //   但是在此之前，调用方是霸占系统资源的。
      //2. pthread_detach，不会阻塞，调用它后，线程运行结束后会自动释放资源。
      pthread_detach(m_thread);
    }
  }

  void Thread::join() {
    if (m_thread) {
      int rt = pthread_join(m_thread, nullptr);
      if (rt) {
        SYLAR_LOG_ERROR(g_logger) << "pthread_join thread fail, rt = " << rt
                                  << " name: " << m_name;
        throw std::logic_error("pthread_join error");
      }
      m_thread = 0;
    }
  }



}

sylar::Semaphore::Semaphore(uint32_t count) {
  if (sem_init(&m_semaphore, 0, count)) {
    throw std::logic_error("sem_init error");
  }
}

sylar::Semaphore::~Semaphore() {
  sem_destroy(&m_semaphore);
}

void sylar::Semaphore::wait() {
  // while(true) {
    // 使用while(true) 是因为有可能被中段？
    // 当前值大于0，则递减后立即返回，等于0则阻塞，直到高于0
    if (sem_wait(&m_semaphore)) {
      throw std::logic_error("sem_wait error");
    }
  // }
}

void sylar::Semaphore::notify() {
  if (sem_post(&m_semaphore)) {
    throw std::logic_error("sem_post error");
  }
}
