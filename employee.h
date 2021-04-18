//普通员工
#pragma once
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;


class Employee :public Worker
{
 public:
  virtual void showInfo();
  virtual string getDeptname();
  Employee(int Id, string Name, int DeptId);


};
