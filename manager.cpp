#include "manager.h"


Manager::Manager(int id ,string name , int did)
{
  this->m_Id = id;
  this->m_Name = name;
  this->m_DeptId = did;
}

void Manager::showInfo()
{
  cout<<"职工编号:"<<this->m_Id
      <<"\t职工姓名:"<<this->m_Name
      <<"\t职工岗位:"<<this->getDeptname()
      <<"\t岗位职责: 完成老板交给的任务,并分发给员工"<<endl;
}


string Manager::getDeptname()
{
  return string("经理");
}
