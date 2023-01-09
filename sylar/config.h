//
// Created by 33145 on 2023/1/5.
//

#ifndef SYLAR_CONFIG_H
#define SYLAR_CONFIG_H

#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "../sylar/log.h"
/* mypoint:
 *  目前来看，config是用来处理yml内容的，读取并修改原本yml格式（tree -> map），从而通过yml达到修改程序参数的目的
 * */
namespace sylar {
class ConfigVarBase {
public:
  typedef std::shared_ptr<ConfigVarBase> ptr;
  ConfigVarBase(const std::string& name, const std::string& description = "") :
        m_name(name),
        m_description(description) {
    std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
  }
  virtual ~ConfigVarBase() = default;
  const std::string& getName() const { return m_name; }
  const std::string& getDescription() const { return m_description; }

  virtual std::string toString() = 0;
  virtual bool fromString(const std::string& val) = 0;
  virtual std::string getTypeName() const = 0;
protected:
  std::string m_name;
  std::string m_description;
};

// F from_type T to_type
template <class F, class T>
class LexicalCast {
public:
  T operator() (const F& v) {
    return boost::lexical_cast<T>(v);
  }
};

// 偏特化以适应一些常用的STL
template <class T>
class LexicalCast<std::string, std::vector<T>> {
public:
  std::vector<T> operator() (const std::string& v) {
    // 把一段字符串转化为Node类型的数据（即？）
    YAML::Node node = YAML::Load(v);
    // mypoint: 使用typename
    //  模板在实例化之前并不知道std::vector<T>是什么东西，使用typename可以让定义确定下来
    //  typename 可以确保引用的是模板中的类型，不是成员变量
    typename std::vector<T> vec;
    std::stringstream ss;
    for (size_t i = 0; i < node.size(); ++i) {
      ss.str("");
      ss << node[i];
      // 这里形成递归调用（why？how？）
      vec.push_back(LexicalCast<std::string, T>()(ss.str()));
    }
    return vec;
  }
};
// 用于变量声明的唯一情况是消除使用泛型 T 的内嵌类型来声明变量时的二义性
template <class T>
class LexicalCast<std::vector<T>, std::string> {
public:
  std::string operator() (const std::vector<T>& v) {
    YAML::Node node;
    for (auto& i : v) {
      // 递归调用，处理可能出现的模板嵌套？
      // 把当前vector的值转化为YAML节点并放入node
      node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
  }
};

  template <class T>
  class LexicalCast<std::string, std::list<T>> {
  public:
    std::list<T> operator() (const std::string& v) {
      YAML::Node node = YAML::Load(v);
      typename std::list<T> vec;
      std::stringstream ss;
      for (size_t i = 0; i < node.size(); ++i) {
        ss.str("");
        ss << node[i];
        // 这里形成递归调用（why？how？）
        vec.push_back(LexicalCast<std::string, T>()(ss.str()));
      }
      // std::cout << "string to list" << std::endl;
      return vec;
    }
  };
// 用于变量声明的唯一情况是消除使用泛型 T 的内嵌类型来声明变量时的二义性
  template <class T>
  class LexicalCast<std::list<T>, std::string> {
  public:
    std::string operator() (const std::list<T>& v) {
      YAML::Node node;
      for (auto& i : v) {
        // 递归调用，处理可能出现的模板嵌套？
        // 把当前vector的值转化为YAML节点并放入node
        node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
      }
      // std::cout << "list to string" << std::endl;
      std::stringstream ss;
      ss << node;
      return ss.str();
    }
  };

  template <class T>
  class LexicalCast<std::string, std::set<T>> {
  public:
    std::set<T> operator() (const std::string& v) {
      YAML::Node node = YAML::Load(v);
      typename std::set<T> vec;
      std::stringstream ss;
      for (size_t i = 0; i < node.size(); ++i) {
        ss.str("");
        ss << node[i];
        // 这里形成递归调用（why？how？）
        vec.insert(LexicalCast<std::string, T>()(ss.str()));
      }
      // std::cout << "string to set" << std::endl;
      return vec;
    }
  };
// 用于变量声明的唯一情况是消除使用泛型 T 的内嵌类型来声明变量时的二义性
  template <class T>
  class LexicalCast<std::set<T>, std::string> {
  public:
    std::string operator() (const std::set<T>& v) {
      YAML::Node node;
      for (auto& i : v) {
        // 递归调用，处理可能出现的模板嵌套？
        // 把当前vector的值转化为YAML节点并放入node
        node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
      }
      // std::cout << "set to string" << std::endl;
      std::stringstream ss;
      ss << node;
      return ss.str();
    }
  };

  template <class T>
  class LexicalCast<std::string, std::unordered_set<T>> {
  public:
    std::unordered_set<T> operator() (const std::string& v) {
      // 把一段字符串转化为Node类型的数据（即？）
      YAML::Node node = YAML::Load(v);
      typename std::unordered_set<T> vec;
      std::stringstream ss;
      for (size_t i = 0; i < node.size(); ++i) {
        ss.str("");
        ss << node[i];
        // 这里形成递归调用（why？how？）
        vec.insert(LexicalCast<std::string, T>()(ss.str()));
      }
      // std::cout << "string to set" << std::endl;
      return vec;
    }
  };
// 用于变量声明的唯一情况是消除使用泛型 T 的内嵌类型来声明变量时的二义性
  template <class T>
  class LexicalCast<std::unordered_set<T>, std::string> {
  public:
    std::string operator() (const std::unordered_set<T>& v) {
      YAML::Node node;
      for (auto& i : v) {
        // 递归调用，处理可能出现的模板嵌套？
        // 把当前vector的值转化为YAML节点并放入node
        node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
      }
      // std::cout << "set to string" << std::endl;
      std::stringstream ss;
      ss << node;
      return ss.str();
    }
  };

  template <class T>
  class LexicalCast<std::string, std::map<std::string, T>> {
  public:
    std::map<std::string, T> operator() (const std::string& v) {
      // 把一段字符串转化为Node类型的数据（即？）
      YAML::Node node = YAML::Load(v);
      typename std::map<std::string, T> vec;
      std::stringstream ss;
      for (auto it = node.begin(); it != node.end(); ++it) {
        ss.str("");
        ss << it->second;
        // 这里形成递归调用（why？how？）
        vec.insert(std::make_pair(it->first.Scalar(), LexicalCast<std::string, T>()(ss.str())));
      }
      // std::cout << "string to set" << std::endl;
      return vec;
    }
  };
  template <class T>
  class LexicalCast<std::map<std::string, T>, std::string> {
  public:
    std::string operator() (const std::map<std::string, T>& v) {
      YAML::Node node;
      for (auto& i : v) {
        node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
      }
      // std::cout << "set to string" << std::endl;
      std::stringstream ss;
      ss << node;
      return ss.str();
    }
  };

  template <class T>
  class LexicalCast<std::string, std::unordered_map<std::string, T>> {
  public:
    std::unordered_map<std::string, T> operator() (const std::string& v) {
      // 把一段字符串转化为Node类型的数据（即？）
      YAML::Node node = YAML::Load(v);
      typename std::unordered_map<std::string, T> vec;
      std::stringstream ss;
      for (auto it = node.begin(); it != node.end(); ++it) {
        ss.str("");
        ss << it->second;
        // 这里形成递归调用（why？how？）
        vec.insert(std::make_pair(it->first.Scalar(), LexicalCast<std::string, T>()(ss.str())));
      }
      // std::cout << "string to set" << std::endl;
      return vec;
    }
  };
  template <class T>
  class LexicalCast<std::unordered_map<std::string, T>, std::string> {
  public:
    std::string operator() (const std::unordered_map<std::string, T>& v) {
      YAML::Node node;
      for (auto& i : v) {
        node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
      }
      // std::cout << "set to string" << std::endl;
      std::stringstream ss;
      ss << node;
      return ss.str();
    }
  };

  // FromStr T operator() (const std::string&)
// ToStr std::string operator() (const T&)
// fromstr tostr 用于支持序列化和反序列化
template<class T, class FromStr = LexicalCast<std::string, T>,
                  class ToStr = LexicalCast<T, std::string>>
class ConfigVar : public ConfigVarBase {
public:
  typedef std::shared_ptr<ConfigVar> ptr;
  // cpp11新特性
  typedef std::function<void (const T& old_value, const T& new_value)> on_change_callback;
  //@param: （name，default_value）: (key,value) 所有map都是开始定义好的，后期只能修改value
  ConfigVar(const std::string& name,
            const T& default_value,
            const std::string& description = "") :
          ConfigVarBase(name, description),
          m_val(default_value) {}
  std::string toString() override {
    try {
      // 用于字符串和数值之间的转换，转换失败会抛出异常
      // return boost::lexical_cast<std::string>(m_val);
      return ToStr()(m_val);
    } catch (std::exception& e) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
        << e.what() << "convert: " << typeid(m_val).name() << " to string";
    }
    return "";
  }
  // 将字符串类型的 T 类型的值转化为 T 类型
  bool fromString(const std::string& val) override {
    try {
      // m_val = boost::lexical_cast<T>(val);
      // std::cout << "from string!" << std::endl;
      setValue(FromStr()(val));
    } catch (std::exception& e) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
          << e.what() << "convert: string to" << typeid(m_val).name();
    }
    return false;
  }
  const T getValue() const { return m_val; }
  void setValue(const T& v) {
     // std::cout << "setvalue   " << typeid(v).name() << std::endl;
     //std::cout << v.name << "  " << v.formatter << "   " << v.level << std::endl;
    if (v == m_val) {
      return;
    }
    // std::cout << "hello wrold" << std::endl;
    for (auto & i : m_callback) {
      // std::cout << "for set value   " << typeid(m_val).name() << std::endl;
      i.second(m_val, v);
    }
     m_val = v;
  }
  std::string getTypeName() const override  { return typeid(T).name(); }

  void addListener(uint64_t key, on_change_callback callback) { m_callback[key] = callback; }
  void delListener(uint64_t key) { m_callback.erase(key); }
  on_change_callback getListener(uint64_t key) {
    auto it = m_callback.find(key);
    return it == m_callback.end() ? nullptr : it->second;
  }
  void clearListener() { m_callback.clear(); }
private:
  T m_val;
  // 变更回调函数
  // mypoint：选择map的原因， 本身function没有 ‘==’ 或者其他的比较方式，所以只能选择map来对function进行一个外围的包装
  std::map<uint64_t, on_change_callback> m_callback;
};
//@brief: 负责对外的接口，通过其 静态的 ConfigVarMap 成员变量来管理所有的 “参数”，包括初始化一个ConfigVar
//        通过LoadFromYaml函数访问yml文件从而修改 “参数”
class Config {
public:
  typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

  template<class T>
  static typename ConfigVar<T>::ptr LookUp(const std::string& name,
                  const T& default_value, const std::string& description = "") {
    auto it = GetDatas().find(name);
    if (it != GetDatas().end()) {
      // 测试类型是否相同，如果不同则无法转换，返回nullptr
      auto tmp = std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
      if (tmp) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Lookup name = " << name <<" exists";
        return tmp;
      } else {
        // 基类成员无法访问派生类的特有函数
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Lookup name = " << name <<" exists but type: not "
                          << typeid(T).name() << " real type is " << it->second->getTypeName()
                          << "  " << it->second->toString();
        return nullptr;
      }
    }
    // 在name中查找第一个与str中任意一个字符都不匹配的字符的index，如果没有就返回string::npos
    // 即检查有没有非法字符
    if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._123456789")
        != std::string::npos) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invaild " << name;
      throw std::invalid_argument(name);
    }
    typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
    // std::cout << "Look up" << std::endl;
    GetDatas()[name] = v;
    return v;
  }

  template<class T>
  static typename ConfigVar<T>::ptr LookUp(const std::string& name) {
    auto it = GetDatas().find(name);
    if (it == GetDatas().end()) {
      return nullptr;
    }
    return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
  }

  static void LoadFromYaml(const YAML::Node& root);
  // c++中只要声明和定义返回的都是指针或者引用，抽象类就可以作为返回值类型
  static ConfigVarBase::ptr LookupBase(const std::string& name);
private:
  static ConfigVarMap& GetDatas() {
    static ConfigVarMap s_datas;
    return s_datas;
  }
};
}

#endif //SYLAR_CONFIG_H
