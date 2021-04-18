#pragma once
#include<iostream>
#include<string>

using namespace std;

class Worker
{
 public:
 //父类要为子类写一个虚析构函数
  virtual  ~Worker(){};
  virtual void showInfo() = 0;
  virtual string getDeptname() = 0;
  int m_Id;
  string m_Name;
  int m_DeptId;
};


