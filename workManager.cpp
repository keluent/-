#include "workManager.h"

WorkManager::WorkManager()
{
  ifstream ifs;
  ifs.open(FILENAME,ios::in);
  if(!ifs.is_open())
  {
    cout<<"文件不存在"<<endl;
    this->m_EmpNum = 0;//初始化人数
    this->m_EmpArray = NULL;//初始化数组指针
    this->m_FileIsEmpty = true;//判断初始化文件为空
    ifs.close();
    return;
  }

  char ch;
  ifs>>ch;
  if(ifs.eof())
  {
    cout<<"文件为空"<<endl;
    this->m_EmpNum = 0;
    this->m_FileIsEmpty = true;
    this->m_EmpArray = NULL;
    ifs.close();
    return;
  }

  int num  = get_EmpNumber();
  cout<<"职工个数为: "<<num<<endl;
  this->m_EmpNum = num;

  this->m_EmpArray = new Worker*[this->m_EmpNum];
  this->init_Emp();
  /*for(int i = 0; i < this->m_EmpNum; i++)
  {
  cout<<"职工编号: " <<this->m_EmpArray[i]->m_Id
   <<"职工姓名: " <<this->m_EmpArray[i]->m_Name
   <<"职工岗位: " <<this->m_EmpArray[i]->m_DeptId<<endl;

  }*/


  
}
  



WorkManager::~WorkManager()
{
  if(this->m_EmpArray != NULL)
    {
      delete[] this->m_EmpArray;
      this->m_EmpArray = NULL;
    }
}

void WorkManager::Show_Menu()
{
  cout<<"欢迎您使用职工管理系统"<<endl;
  cout<<"0.退出管理系统"<<endl;
  cout<<"1.增加职工信息"<<endl;
  cout<<"2.显示职工信息"<<endl;
  cout<<"3.删除职工信息"<<endl;
  cout<<"4.修改职工信息"<<endl;
  cout<<"5.查找职工信息"<<endl;
  cout<<"6.按照编号排序"<<endl;
  cout<<"7.清空所有文档"<<endl;
  cout<<endl;
}


void WorkManager::exitSystem()
{
  cout<<"欢迎下次使用"<<endl;
  system("read -p 'Any press to continue'var");
  exit(0);
}

void WorkManager::add_Emp()
{
  cout<<"请输入输入职工数量"<<endl;
  int addNum = 0;
  cin >> addNum;
  if(addNum > 0)
    {
      //先计算新添加的空间大小
      int newSize = this->m_EmpNum + addNum;
      Worker** newSpace = new Worker*[newSize];
      //将原来空间下数据拷贝到新空间下
      if(this->m_EmpArray != NULL)
        {
          for(int i = 0; i < this->m_EmpNum; i++)
            {
              newSpace[i] = this->m_EmpArray[i];
            }
        }
      //添加新数据
      for(int i = 0 ; i < addNum ; i++)
        {
          int id;
          string name;
          int dSelect;
          cout << "请输入第"<<i+1<<"个职工的编号: "<<endl;
          cin >>id;
          cout << "请输入第"<<i+1<<"个职工的姓名: "<<endl;
          cin >>name;
          cout << "请选择该职工的岗位: "<<endl;
          cout << "1,普通员工"<<endl;
          cout << "2,经理"<<endl;
          cout << "3,老板"<<endl;
          cin >> dSelect;

          Worker * worker =NULL;
          switch(dSelect)
            {
            case 1:
              worker = new Employee(id, name, 1);
              break;
            case 2:
              worker = new Manager(id, name, 2);
              break;
            case 3:
              worker = new Boss(id, name, 3);
              break;
            default:
              break;
            }

          newSpace[this->m_EmpNum + i] = worker;
          //将创建的职工职责存入数组中

        }
      delete[] this->m_EmpArray;//释放原有空间

      //更改新空间的指向
      this->m_EmpArray = newSpace;

      this->m_EmpNum = newSize;

      //保存到文件中
      this->save();

      //更新职工不为空的情况
      this->m_FileIsEmpty = false;

      //提示添加成功
      cout<< "成功添加"<<addNum<<"名新职工"<<endl;
    }
  else
    {
      cout<<"数据输入有误"<<endl;
    }

  system("read -p 'Any press to continue'var");
  system("clear");
}
// void WorkManager::exitSystem()
// {
//   cout <<"欢迎下次使用"<<endl;
//   system("read -p 'Ant press to continue'var");
//   exit(0);
// }


void WorkManager::save()
{
  ofstream ofs;
  ofs.open(FILENAME, ios::out);

  for(int i  = 0;i < this->m_EmpNum;i++)
    {
      ofs<<this->m_EmpArray[i]->m_Id<<" "
         <<this->m_EmpArray[i]->m_Name<<" "
         <<this->m_EmpArray[i]->m_DeptId<<endl;
    }

  ofs.close();
}

int WorkManager::get_EmpNumber()
{
  ifstream ifs;
  ifs.open(FILENAME , ios::in);
  int id ;
  string name;
  int did;
  int num = 0;
  while(ifs>>id&&ifs>>name&&ifs>>did)
  {
    num++;
  }
  return num;
}

void WorkManager::init_Emp()
{
  ifstream ifs;
  ifs.open(FILENAME, ios::in);

  int id;
  string name;
  int did;
   
  int index = 0;
  while(ifs >> id && ifs>>name&& ifs>> did)
  {
    Worker  *worker = NULL;
    if(did =1)
    {
      worker = new Employee(id, name , did);

    }

    else if (did = 2)
    {
      worker = new Manager(id, name , did);
    }

    else 
    {
      worker = new Boss(id, name ,did);

    }

    this->m_EmpArray[index] = worker;
    index++;

    
  }
}


void WorkManager::show_Emp()
{
  if(this->m_FileIsEmpty)
  {
    cout<<"文件不存在或为空"<<endl;

  }
  else
  {
    for(int i = 0;i< this->m_EmpNum; i++)
    {
      this->m_EmpArray[i]->showInfo();  
    }
  }
  system("read -p 'Any press to continue'var");
  system("clear");

}


int WorkManager::EmpisExist(int id)
{
  int index = -1;
  for (int i= 0; i < this->m_EmpNum;i++)
  {
    if(this->m_EmpArray[i]->m_Id == id)
    {
      index = i;
      break;
    }
  }
  return index;
}

void WorkManager::del_Emp()
{
  if(this->m_FileIsEmpty)
  {
    cout<<"文件不存在"<<endl;
  }
  else
  {
    cout<<"请输入删除职工的编号"<<endl;
    int id  = 0;
    cin >> id;
    int index =this->EmpisExist(id);
    if (index != -1)//职工存在,并要执行删除操作
    {
      for(int i = index;i<this->m_EmpNum -1; i++)
      {
        this->m_EmpArray[i] = m_EmpArray[i+1];
      }
      this->m_EmpNum--;
      this->save();
      cout<<"删除成功"<<endl;
    }
    else
    {
      cout<<"没有这个员工"<<endl;
    }

  }
  system("read -p 'Any press to continue'var");
  system("clear");
}

void WorkManager::mod_Emp()
{
  if(this->m_FileIsEmpty)
  {
    cout<<"文件为空"<<endl;
  }
  else
  {
    cout<<"请输入修改职工的编号: "<<endl;
    int id;
    cin >> id;

    int ret = this->EmpisExist(id);
    if(ret!=-1)
    {
      delete this->m_EmpArray[ret];
      int newId = 0;
      string newName = "";
      int dSelect = 0;
      cout<<"查到"<<id<<"号的职工,请输入新的职工号: "<<endl;
      cin >> newId;
      cout<<"请输入新姓名"<<endl;
      cin >>newName;
      cout<<"请输入岗位: "<<endl;
      cout<<"1.普通员工"<<endl;
      cout<<"2.经理"<<endl;
      cout<<"3.老板"<<endl;
      cin>>dSelect;
      Worker * worker = NULL;
      switch(dSelect)
      {
        case 1:
          worker = new Employee(newId,newName,dSelect);
        break;

        case 2:
          worker = new Manager(newId,newName,dSelect);
        break;

        case 3:
          worker = new Boss(newId,newName,dSelect);
        break;

        default:
        break;
      }


      this->m_EmpArray[ret] = worker;
      cout<<"修改成功"<<endl;
      //保存到文件中
      this->save();


    }
    else
    {
      cout<<"修改失败,查无此人"<<endl;
    }

  }

  system("read -p 'Any press to continue'var");
  system("clear");
}


void  WorkManager::find_Emp()
{
  if(this->m_FileIsEmpty)
  {
    cout<<"文件不存在或为空"<<endl;

  }
  else
  {
    cout<<"请输入查找方式"<<endl;
    cout<<"1.按职工编号查找"<<endl;
    cout<<"2.按职工名字查找"<<endl;

    int Select = 0;
    cin >> Select;
    if(Select  == 1)
    {
      int id;
      cout<<"输入要查找职工的编号"<<endl;
      cin >> id;
      int ret = EmpisExist(id);
      if(ret != -1)
      {
        cout<<"查找成功,该入职工的信息:"<<endl; 
        this->m_EmpArray[ret]->showInfo();
      }
      else
      {
        cout<<"输入有误,查无此人"<<endl;

      }

    }
    else if(Select == 2)
    {
      string name;
      cout<<"请输入查找的姓名"<<endl;
      cin >>name; 


      bool flag =false;

      for(int i =0 ;i<this->m_EmpNum;i++)
      {
        if(this->m_EmpArray[i]->m_Name == name)
        {
          cout<<"查找成功,职工编号为"<<m_EmpArray[i]->m_Id<<"号职工信息如下: "<<endl;

          flag =true;
          this->m_EmpArray[i]->showInfo();
        }
      }

      if(flag == false)
      {
        cout<<"查找失败"<<endl;

      }

    }
    else
    {
      cout<<"输入的选项有误"<<endl;
    }

  }
  system("read -p 'Any press to continue'var");
  system("clear");
}

void WorkManager::sort_Emp()
{
  if(this->m_FileIsEmpty)
  {
    cout<<"文件为空或不存在"<<endl;
    system("read -p 'Any press to continue'var");
    system("clear");
  }

  else
  {
    cout<<"请选择排序方式"<<endl;
    cout<<"1.按职工号升序"<<endl;
    cout<<"2.按职工号降序"<<endl;
    int Select  =0;
    cin >>Select;
    for(int i = 0;i< m_EmpNum;i++)
    {
      int minOrMax = i;
      for(int j = i+1;j<this->m_EmpNum;j++)
      {
        if(Select == 1)
       {
        if(this->m_EmpArray[minOrMax]->m_Id     >    m_EmpArray[j]->m_Id)
         {
           minOrMax = j;
         }
       }

       else
       {
         if(this->m_EmpArray[minOrMax]->m_Id     <    m_EmpArray[j]->m_Id)
         {
           minOrMax = j;
         }

         
       }

       if(i!=minOrMax)
         {
           Worker *temp = this->m_EmpArray[i];
           this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
           this->m_EmpArray[minOrMax] = temp;
         }

       
      }
    
    }
      cout<<"排序成功,排序后的结果为: "<<endl;
      this->save();
      this->show_Emp();
      system("read -p 'Any press to continue'var");
      system("clear");
  }
}

void WorkManager::clean_File()
{
  cout <<"确认清空?"<<endl;
  cout<<"1.确认清空"<<endl;
  cout<<"2.操作失误"<<endl;
  int select = 0;
  cin >> select;
  if(select ==1)
  {
    ofstream ofs(FILENAME, ios::trunc); 
    ofs.close();
    if(this->m_EmpArray != NULL)
    {
      for(int i = 0;i < this->m_EmpNum;i++)
      {
        //删除堆区的每个职工对象
        delete this->m_EmpArray[i];
        this->m_EmpArray = NULL;
      }
      //删除堆区数组指针
      delete[] this->m_EmpArray;
      this->m_EmpArray = NULL;
      this->m_EmpNum = 0;
      this->m_FileIsEmpty =true;

    }
    cout<<"清空成功"<<endl;
  }
  system("read -p 'Any press to continue'var");
  system("clear");
}