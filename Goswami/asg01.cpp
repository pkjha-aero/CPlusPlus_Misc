#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

class student
{
private:
  int no_student;
  char name[80];
  char dob[15];
public:
  void student_no(int num)
  {
    no_student=num;
  }

  int get_no_student()
  {
    return no_student;
  }

  void read_name()
  {
    int i=0;
    cout<<"\nEnter the name of the student:\n";
    do
      {
    	name[i]=getchar();
    	i++;
      }while(name[i-1]!='\n');
    //scanf(" %[^\n]",name);
  }

  void check_name()
  {
    int count=0,i=0;
    while(name[i]!='\n')
      {
	if((name[i]>=64 && name[i]<=90)||(name[i]>=97 && name[i]<=122))
	  count++;
	i++;
      }
    if(count>15)
      {
	cout<<"Name exceeds 15 characters.\nPlease Enter again:\n";
	read_name();
      }
  }

  void read_dob()
  {
    int i=0;
    cout<<"\nEnter the D.O.B.in proper format(dd/mm/yyyy):\n";
    do
      {
	dob[i]=getchar();
	i++;
      }while(dob[i-1]!='\n');
  }

  void check_dob()
  {
    int d=(dob[0]-48)*10+(dob[1]-48);
    int m=(dob[2]-48)*10+(dob[3]-48);
    int y=(dob[4]-48)*1000+(dob[5]-48)*100+(dob[6]-48)*10+(dob[7]-48);
    cout<<d<<" "<<m<<" "<<y<<"\n";
  }
  void show()
  {
    cout<<"\n\n*****STUDENT NO. "<<no_student<<"*****";
    cout<<"\nName:"; 
    int i=0;
    while(name[i]!='\n')
      {
	cout<<name[i];
	i++;
      }
    cout<<"\nD.O.B.: ";
    for(int i=0;i<=1;++i)
      cout<<dob[i];
    cout<<" ";
    for(int i=2;i<=3;i++)
      cout<<dob[i];
    cout<<" ";
    for(int i=4;dob[i]!='\n';i++)
      cout<<dob[i];
  }
};

main()
{
  student ob[5];
  for(int i=0;i<5;i++)
    {
      ob[i].student_no(i+1);
      cout<<"\nStudent No:"<<ob[i].get_no_student();//no_student not// accessible directly as private
      ob[i].read_name();
      ob[i].check_name();
      ob[i].read_dob();
      ob[i].check_dob();
    }

  for(int i=0;i<5;i++)
    {
      ob[i].show();
    }
  cout<<"\n";
}
