//
// Created by 33145 on 2023/1/5.
//

#ifndef SYLAR_CONFIG_H
#define SYLAR_CONFIG_H

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "../sylar/log.h"

namespace sylar {
class ConfigVarBase {
public:
  typedef std::shared_ptr<ConfigVarBase> ptr;
  ConfigVarBase(const std::string& name, const std::string& description = "") :
        m_name(name),
        m_description(description) {}
  virtual ~ConfigVarBase() = default;
  const std::string& getName() const { return m_name; }
  const std::string& getDescription() const { return m_description; }

  virtual std::string toString() = 0;
  virtual bool formString(const std::string& val) = 0;
protected:
  std::string m_name;
  std::string m_description;
};

template<class T>
class ConfigVar : public ConfigVarBase {
public:
  typedef std::shared_ptr<ConfigVar> ptr;
  ConfigVar(const std::string& name,
            const T& default_value,
            const std::string& description = "") :
          ConfigVarBase(name, description),
          m_val(default_value) {}
  std::string toString() override {
    try {
      // 用于字符串和数值之间的转换，转换失败会抛出异常
      boost::lexical_cast<std::string>(m_val);
    } catch (std::exception& e) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
        << e.what() << "convert: " << typeid(m_val).name() << " to string";
    }
    return "";
  }
  bool formString(const std::string& val) override {
    try {
      m_val = boost::lexical_cast<T>(val);
    } catch (std::exception& e) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
          << e.what() << "convert: string to" << typeid(m_val).name();
    }
    return false;
  }
  const T getValue() const { return m_val; }
  void setValue(const T& v) { m_val = v; }
private:
  T m_val;
};

class Config {
public:
  typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

  template<class T>
  static typename ConfigVar<T>::ptr LookUp(const std::string& name,
                  const T& default_value, const std::string& description = "") {
    auto tmp = LookUp<T>(name);
    if (tmp) {
      SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Lookup name = " << name <<" exists";
      return tmp;
    }

    if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._123456789")
        != std::string::npos) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invaild " << name;
      throw std::invalid_argument(name);
    }
    typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
    s_datas[name] = v;
    return v;
  }

  template<class T>
  static typename ConfigVar<T>::ptr LookUp(const std::string& name) {
    auto it = s_datas.find(name);
    if (it == s_datas.end()) {
      return nullptr;
    }
    return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
  }
private:
  static ConfigVarMap s_datas;
};
}

#endif //SYLAR_CONFIG_H
