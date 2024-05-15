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
	cout<<"Name exceeds 15 characters.\nPlease Try Again:\n";
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
    //cout<<d<<" "<<m<<" "<<y<<"\n";
    int val;
    if(m>12)
      val=6;
    if(y%4==0 && m==2 && d>29)
      val=1;  
    if((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&(d>31))
      val=3;
    if((m==4||m==6||m==9||m==11)&&(d>30))
      val=4;
    if(m==2 && y%4!=0 && d>28)
      val=5;
    if((y>2004)||(y==2004 && m>8)||(y==2004&& m==8 && d>5))
      val=2;
    switch(val)
      {
      case 1:cout<<"\nIn a Leap Year February has atmost 29 days.";
	break;
      case 2:cout<<"\nThis day has not yet come.";
	break;
      case 3:cout<<"\nMonth can't be of more than 31 days.";
	break;
      case 4:cout<<"\nMonth can be max of 30 days. ";
	break;
      case 5:cout<<"\nFebruary in a non-leap year can be max of 28 days.";
	break;
      case 6:cout<<"\nOnly 12 months are there.";
      default:;
      }
  }

  double getdob()
  {
    int d=(dob[0]-48)*10+(dob[1]-48);
    int m=(dob[2]-48)*10+(dob[3]-48);
    int y=(dob[4]-48)*1000+(dob[5]-48)*100+(dob[6]-48)*10+(dob[7]-48);
    double z=y*1000000+m*1000+d;  
    return z;
  }
  char *getname()
  {
    return name;
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

void sortbyname(student obj[],int n)
{
  student temp;
  int i,j,k;
  for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++)
      {
	if(strcmp(obj[j].getname(),obj[i].getname())<0)//strcmpi not allowed
	  {
	    temp=obj[i];
	    obj[i]=obj[j];
	    obj[j]=temp;
	    k=obj[i].get_no_student();
	    obj[i].student_no(obj[j].get_no_student());
	    obj[j].student_no(k);
	  }
      }
}
void sort_by_dob(student obj[],int n)
{
  student temp;
  int i,j,k;
  for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++)
      {
	if(obj[j].getdob()<obj[i].getdob())
	  {
	    temp=obj[i];
	    obj[i]=obj[j];
	    obj[j]=temp;
	    k=obj[i].get_no_student();
	    obj[i].student_no(obj[j].get_no_student());
	    obj[j].student_no(k);
	  }
      }
}

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
    ob[i].show();
  cout<<"\n\nAFTER SORTING BY NAME:**********";
  sortbyname(ob,5);
  for(int i=0;i<5;i++)
    ob[i].show();
  cout<<"\n\nAFTER SORTING BY D.O.B.:**********";
  sort_by_dob(ob,5);
  for(int i=0;i<5;i++)
    ob[i].show();
  cout<<"\n";
}
