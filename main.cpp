#include "workManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;


int main()
{
  // Worker * worker = NULL;
  // worker = new Employee(1,"张三",1);
  // worker->showInfo();
  // delete worker;

  // worker = new Manager(2,"李四",2);
  // worker->showInfo();
  // delete worker;

  // worker = new Boss(3,"王二麻子",3);
  // worker->showInfo();
  // delete worker;

  WorkManager wm;
  int choice = 0;
  while(true)
    {
      wm.Show_Menu();
      cout<<"Please input your choice"<<endl;
      cin >> choice;
      switch(choice)
        {
        case 0:   //推出系统
          wm.exitSystem();
          break;
        case 1:  //增加职工信息
          wm.add_Emp();
          break;
        case 2: //显示职工信息
          wm.show_Emp();
          break;
        case 3://删除职工信息
          wm.del_Emp();
          break;
        case 4://修改职工信息
          wm.mod_Emp();
          break;
        case 5://查找职工信息
          wm.find_Emp();
          break;
        case 6://排序
          wm.sort_Emp();
          break;
        case 7://清除
          break;
        default:
          system("clear");
          break;

        } 
    }
  
  return 0;
}
