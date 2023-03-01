#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
class Banking
{
 private:
	 int acc_no;
	 char name[30];
	 char address[30];
	 float balance; //initial balance
	 char type[8]; //transaction by cheque or cash
	 char tran; //deposit or withdrawal
	 float amount; // transaction amount
	 float curr_balance; //current balance

 public:
	void inputdata();
	void modify_data();
	static void add_to_file(Banking);
	static void disp_list();
	void putdata();
	static void see_p();
	static void trans();
	void put_info();
	static void m_report();
	void disp_m1();
	void disp_m2();
	static void modify_acc();
	static void del_account();
 };
 void line_p(int);
 void Banking::inputdata()
 {
  cout<<"\nEnter the new account number:";
  cin>>acc_no;
  cout<<"\nEnter the account holders name:";
  cin>>name;
  cout<<"\nEnter the address:";
  cin>>address;
  cout<<"\nEnter the initial deposit:";
  cin>>balance;
  }
  void Banking::modify_data()
 {
  cout<<"\nEnter the new account holder's name:";
  cin>>name;
  cout<<"\nEnter new address:";
  cin>>address;
  }
 void Banking::add_to_file(Banking obj)
 {
  if(obj.balance<500)
  {
   cout<<"\nInitial deposit should be atleast 500";
   exit(1);
  }
  fstream file;
  file.open("person.dat",ios::out|ios::app|ios::binary);
  file.write((char*)&obj,sizeof(obj));
  file.close();
 }
 void Banking::putdata()
 {
  cout<<"\n";
  cout<<acc_no<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<balance;
  }
 void Banking::disp_list()
 {
   fstream file;
   Banking temp;
   file.open("person.dat",ios::in|ios::binary);
   file.seekg(0);
   line_p(54);
   cout<<"\nAcc.no"<<"\t\t"<<"Name"<<"\t\t"<<"Address"<<"\t\t"<<"Balance";
   cout<<"\n";
   line_p(54);
   while(file.read((char*)&temp,sizeof(temp)))
   {
    temp.putdata();
    }
    file.close();
 }
 void Banking::see_p()
 {
  fstream file;
  Banking temp;
  file.open("person.dat",ios::in|ios::binary);
  file.seekg(0);
  int number;
  cout<<"\nEnter the account number to be searched:";
  cin>>number;
  line_p(54);
  cout<<"\nAcc.no"<<"\t\t"<<"Name"<<"\t\t"<<"Address"<<"\t\t"<<"Balance";
  cout<<"\n";
  line_p(54);
  while(file.read((char*)&temp,sizeof(temp)))
 {
  if(temp.acc_no==number)
   {
    temp.putdata();
    break;
    }
  }
  file.close();
 }
 void Banking::trans()
 {
  int number;
  cout<<"\nEnter your account number:";
  cin>>number;
  Banking temp,obj;
  fstream file,file1;
  int m=0;
  file.open("person.dat",ios::in|ios::binary);
  while(file.read((char*)&temp,sizeof(temp)))
  {
   m=m+1;
   }
  file.close();
  file.open("person.dat",ios::in|ios::out|ios::binary);
  file.seekg(0,ios::end);
  int endposition=file.tellg();
  int position=endposition/m;
  file.seekg(0);
  int n=0;
  while(file.read((char*)&temp,sizeof(temp)))
 {
   n=n+1;
   if(temp.acc_no==number)
  {
   cout<<"\n";
   line_p(54);
   cout<<"\nAcc.no"<<"\t\t"<<"Name"<<"\t\t"<<"Address"<<"\t\t"<<"Balance";
   cout<<"\n";
   line_p(54);
   temp.putdata();
   break;
   }
  }
  int p=(n-1)*position;
  temp.put_info();
  obj=temp;
  file1.open("record.dat",ios::out|ios::app|ios::binary);
  file1.write((char*)&temp,sizeof(temp));
  file1.close();
  file.seekp(p);
  file.write((char*)&obj,sizeof(obj));
  file.close();
  }
  void Banking::put_info()
  {
   cout<<"\n";
   cout<<"\nWhat you want to do->Deposit/Withdrawal Enter(D/W):";
   cin>>tran;
   cout<<"\nEnter mode of payment->Cash/Cheque:";
   cin>>type;
   cout<<"\nEnter transaction amount:";
   cin>>amount;
   if(tran=='D')
   {
    curr_balance=balance+amount;
    balance=curr_balance;
    }
   if(tran=='W')
   {
     curr_balance=balance-amount;
     if(curr_balance<0)
     {
      cout<<"\nCannot withdraw money, not enough balance sorry!";
      amount=0;
      curr_balance=balance;
      exit(1);
      }
      balance=curr_balance;
    }
   }
  void Banking::m_report()
  {
   Banking temp;
   fstream file1,file2;
   int number;
   cout<<"\nEnter account number whose monthly report is demanded:";
   cin>>number;
   file1.open("person.dat",ios::in|ios::binary);
   file1.seekg(0);
   while(file1.read((char*)&temp,sizeof(temp)))
   {
    if(temp.acc_no==number)
    {
     temp.disp_m1();
     break;
     }
    }
    file2.open("record.dat",ios::in|ios::binary);
    file2.seekg(0);
    cout<<"\n";
    line_p(54);
    cout<<"\nParticular"<<"\t"<<"Deposit"<<"\t\t"<<"Withdraw"<<"\t"<<"Balance";
    cout<<"\n";
    line_p(54);
    while(file2.read((char*)&temp,sizeof(temp)))
    {
     if(temp.acc_no==number)
     temp.disp_m2();
     }
     file1.close();
     file2.close();
   }
   void Banking::disp_m1()
   {
    cout<<"\nAccount No. "<<acc_no<<"\t\t"<<address;
    cout<<"\nMonthly report";
    }
   void Banking::disp_m2()
   {
    cout<<"\n";
    if(tran=='D')
    cout<<type<<"\t\t"<<amount<<"\t\t"<<"0"<<"\t\t"<<curr_balance;
    if(tran=='W')
    cout<<type<<"\t\t"<<"0"<<"\t\t"<<amount<<"\t\t"<<curr_balance;
    }
    void Banking::modify_acc()
    {
     int number;
     Banking temp;
     fstream file;
     cout<<"\nEnter the account number to be modified:";
     cin>>number;
     file.open("person.dat",ios::in|ios::binary);
     int m=0;
     while(file.read((char*)&temp,sizeof(temp)))
     {
      m=m+1;
      }
     file.close();
     file.open("person.dat",ios::in|ios::out|ios::binary);
     file.seekg(0,ios::end);
     int endposition=file.tellg();
     int position=endposition/m;
     int n=0;
     file.seekg(0);
     while(file.read((char*)&temp,sizeof(temp)))
     {
      n=n+1;
      if(temp.acc_no==number)
     {
      line_p(54);
      cout<<"\nAcc.no"<<"\t\t"<<"Name"<<"\t\t"<<"Address"<<"\t\t"<<"Balance";
      cout<<"\n";
      line_p(54);
      temp.putdata();
      break;
      }
     }
     int p=(n-1)*position;
     file.seekp(p);
     cout<<"\n";
     temp.modify_data();
     file.write((char*)&temp,sizeof(temp));
     file.close();
     }
     void Banking::del_account()
    {
     Banking temp;
     long int number;
     fstream file1,file2;
     file1.open("person.dat",ios::in|ios::binary);
     file1.seekg(0);
     file2.open("temp.dat",ios::out|ios::app|ios::binary);
     cout<<"\nEnter the account number of account to be closed:";
     cin>>number;
     while(file1.read((char*)&temp,sizeof(temp)))
     {
     if(temp.acc_no==number)
     continue;
     file2.write((char*)&temp,sizeof(temp));
     }
     file1.close();
     file2.close();
     remove("person.dat");
     rename("temp.dat","person.dat");
    }
    void line_p(int n)
    {
     int i;
     for(i=0;i<=n;i++)
     cout<<"=";
     }
     int main()
     {
      int m,n;
      char ch;
      do
      {
      cout<<"MADE BY:- Anubhav Negi\n";
      cout<<"\nWelcome to the Banking System!";
      cout<<"\nSelect from the below mentioned options";
      cout<<"\n1.Open New Account";
      cout<<"\n2.List of all the Account Holders";
      cout<<"\n3.See Individual Account Details";
      cout<<"\n4.Do Daily Transaction";
      cout<<"\n5.Generate Monthly Report";
      cout<<"\n6.Edit Account Details";
      cout<<"\n7.Quit";
      cout<<"\nEnter your choice:";
      cin>>m;
      switch(m)
      {
       case 1:{
	       Banking obj;
	       obj.inputdata();
	       Banking::add_to_file(obj);
	       break;
	       }
       case 2:
	       Banking::disp_list();
	       break;
       case 3:
	       Banking::see_p();
	       break;
       case 4:
	       Banking::trans();
	       break;
       case 5:
	       Banking::m_report();
	       break;
       case 6:
	     cout<<"\nWhat do you want?";
	     cout<<"\n1.Modify Account Details";
	     cout<<"\n2.Close Account";
	     cout<<"\nEnter your choice:";
	     cin>>n;
	      switch(n)
	      {
	       case 1:
		       Banking::modify_acc();
		       break;
	       case 2:
		       Banking::del_account();
		       break;
	       default:
		       cout<<"\nWrong Choice";
	       }
	       break;
       case 7:
	      cout<<"\nThank you for using our service"
		  <<"\nHave a nice day!";
	      getch();
	      exit(1);
      default:
	      cout<<"\nSorry wrong choice";
    }
    cout<<"\n";
    cout<<"\nDo you want to continue y/n:";
    cin>>ch;
    }while(ch=='y');
    }







