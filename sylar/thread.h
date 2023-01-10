//
// Created by 33145 on 2023/1/10.
//

#ifndef SYLAR_THREAD_H
#define SYLAR_THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <pthread.h>
#include <semaphore.h>

namespace sylar {

  class Semaphore {
  public:
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();
  private:
    Semaphore(const Semaphore&) = delete;
    Semaphore(const Semaphore&&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
  private:
    sem_t m_semaphore;
  };

  template<class T>
  class ScopedLockImpl {
  public:
    ScopedLockImpl(T& mutex) : m_mutex(mutex) {
      m_mutex.lock();
      m_locked = true;
    }
    ~ScopedLockImpl() {
      unlock();
    }
    void lock() {
      if (!m_locked) {
        m_mutex.lock();
        m_locked = true;
      }
    }
    void unlock() {
      // 应该先设置好状态再解锁，所有临界区的属性，
      // 线程出临界区(unlock)后，都不应该去尝试改变
      if (m_locked) {
        m_locked = false;
        m_mutex.unlock();
      }
    }
  private:
    T& m_mutex;
    bool m_locked;
  };

  template<class T>
  class ReadScopedLockImpl {
  public:
    ReadScopedLockImpl(T& mutex) : m_mutex(mutex) {
      m_mutex.rdlock();
      m_locked = true;
    }
    ~ReadScopedLockImpl() {
      unlock();
    }
    void lock() {
      // mypoint 读锁不是可以重入吗
      if (!m_locked) {
        m_mutex.rdlock();
        m_locked = true;
      }
    }
    void unlock() {
      if (m_locked) {
        m_locked = false;
        m_mutex.unlock();
      }
    }
  private:
    T& m_mutex;
    bool m_locked;
  };

  template<class T>
  struct WriteScopedLockImpl {
  public:
    WriteScopedLockImpl(T& mutex)
            :m_mutex(mutex) {
      m_locked = true;
      m_mutex.wrlock();
    }
    ~WriteScopedLockImpl() {
      unlock();
    }
    void lock() {
      if(!m_locked) {
        m_locked = true;
        m_mutex.wrlock();

      }
    }
    void unlock() {
      if(m_locked) {
        m_locked = false;
        m_mutex.unlock();
      }
    }
  private:
    /// Mutex
    T& m_mutex;
    /// 是否已上锁
    bool m_locked;
  };


  class Mutex {
  public:
    typedef ScopedLockImpl<Mutex> Lock;
    Mutex() {
      pthread_mutex_init(&m_mutex, nullptr);
    }
    ~Mutex() {
      pthread_mutex_unlock(&m_mutex);
    }
    void lock() {
      pthread_mutex_lock(&m_mutex);
    }
    void unlock() {
      pthread_mutex_unlock(&m_mutex);
    }
  private:
    pthread_mutex_t m_mutex{};
  };

  class RWMutex {
  public:
    typedef ReadScopedLockImpl<RWMutex> ReadLock;
    typedef WriteScopedLockImpl<RWMutex> WriteLock;

    RWMutex() {
      pthread_rwlock_init(&m_lock, nullptr);
    }
    ~RWMutex() {
      pthread_rwlock_destroy(&m_lock);
    }
    void rdlock() {
      pthread_rwlock_rdlock(&m_lock);
    }
    void wrlock() {
      pthread_rwlock_wrlock(&m_lock);
    }
    void unlock() {
      pthread_rwlock_unlock(&m_lock);
    }
  private:
    pthread_rwlock_t m_lock;
  };

  class Thread {
  public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, const std::string& name);
    ~Thread();

    pid_t getId() const { return m_id; }
    const std::string& getName() const { return m_name; }

    void join();
    static Thread* GetThis();
    static const std::string& GetThreadName();
    static void SetName(const std::string& name);
    // 互斥量和互斥信号量都是不能拷贝的，拷贝会破坏他们的作用
    Thread(const Thread&) = delete;
    Thread(const Thread&&) = delete;
    Thread& operator=(const Thread&) = delete;
  private:
    static void* run(void* arg);
  private:
    pid_t m_id = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;

    Semaphore m_semaphore;
  };
}


#endif //SYLAR_THREAD_H
