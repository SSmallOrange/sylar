//
// Created by 33145 on 2023/1/5.
//

#ifndef SYLAR_SINGLETON_H
#define SYLAR_SINGLETON_H

#include <memory>

namespace sylar {
  // mypoint: 单例模式模板类，之所以不在日志管理器里面实现单例模式，因为分布式多线程等可能是每个线程一个单例，
  //          使用模板就可以解决这类问题
  //  static可以延长对象的生命周期，直到程序结束时对象才会被析构
  template<class T, class X = void, int N = 0>
  class Singleton {
  public:
    static T* GetInstance() {
      static T v;
      return &v;
    }
  };

  template<class T, class X = void, int N = 0>
  class SingletonPtr {
  public:
    static std::shared_ptr<T> GetInstance() {
      static std::shared_ptr<T> v(new T);
      return v;
    }
  };
}


#endif //SYLAR_SINGLETON_H
