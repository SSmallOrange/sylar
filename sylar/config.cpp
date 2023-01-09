//
// Created by 33145 on 2023/1/6.
//
#include "config.h"
#include <iostream>

namespace sylar {

  ConfigVarBase::ptr Config::LookupBase(const std::string &name) {
    auto it = GetDatas().find(name);
    return it == GetDatas().end() ? nullptr : it->second;
  }
  /* mypoint:  ListAllMember接口的作用
   *  log
      x  log
      system
      system.port
      system.port   9900
      system.value
      system.value   15
      system
      x
      将yml内的树形内容转化为字典结构，即（key：value）型
   * */
  static void ListAllMember(const std::string& prefix, const YAML::Node& node,
                            std::list<std::pair<std::string, const YAML::Node>>& output) {
    if (prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos) {
      SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Config invalid name: " << prefix <<" : " << node;
      return;
    }
    //  std::cout << prefix << std::endl;
    output.emplace_back(prefix, node);
    if (node.IsMap()) {
      for (auto it = node.begin(); it != node.end(); ++it) {
        ListAllMember(prefix.empty() ? it->first.Scalar() : prefix + "." + it->first.Scalar(), it->second, output);
      }
    }
    // std::cout << "  x  " << prefix << "   " << node.Scalar() << std::endl;
  }
  void Config::LoadFromYaml(const YAML::Node &root) {
    std::list<std::pair<std::string, const YAML::Node>> all_nodes;
    ListAllMember("", root, all_nodes);

    for(auto& i : all_nodes) {
      std::string key = i.first;
      if (key.empty()) {
        continue;
      }
      std::transform(key.begin(), key.end(), key.begin(), ::tolower);
      ConfigVarBase::ptr var = LookupBase(key);  //mypoint: 返回一个智能指针，通过智能指针修改原本的值
      // std::cout << key << std::endl;

      // std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
      // std::cout << var->toString();
      // std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;

      if (var) {
        // std::cout << "hello wrold" << std::endl;
        if (i.second.IsScalar()) {  // 将值转化为字符串存储
          var->fromString(i.second.Scalar());
        } else {
          std::stringstream ss;
          ss << i.second;
          var->fromString(ss.str());
        }
      }
    }
  }

}