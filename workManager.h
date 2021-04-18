#pragma once//防止头文件包含多次
#include<cstdlib>
#include<iostream>
#include<string>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#define FILENAME "empFile.txt"

using namespace std;

class WorkManager
{
 public:
  WorkManager();
  ~WorkManager();
  void Show_Menu();
  void exitSystem();
  void add_Emp();
  void save();
  int m_EmpNum;//职工人数
  Worker ** m_EmpArray;
  bool m_FileIsEmpty;//判断文件是否为空
  int get_EmpNumber();
  void init_Emp();
  void show_Emp();
  void del_Emp();
  int EmpisExist(int id);
  void mod_Emp();
  void find_Emp();
  void sort_Emp();
  void clean_File();
};
