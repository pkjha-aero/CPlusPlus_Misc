//PANKAJ KUMAR JHA
//01 MA 2011
//ASSIGNMENT 6

#include<iostream.h>
#include<fstream.h>
#include<string.h>

class student
{
public:
  char name[15];
  int roll;
  void constinfo();
  void displayinfo();
  void checkroll(student obj[],int j);
};
void student::constinfo()
{
  cout<<"\nEnter Name: ";
  cin>>name;
  cout<<"\nEnter RollNo: ";
  cin>>roll;
  cout<<"\nThe Name of the student entered is: "<<name;
  cout<<" and the Roll No entered is: "<<roll<<endl;
}

void student::displayinfo()
{
  cout<<"\nThe Students Information:"<<"\nName: "<<name<<"\nRoll No :"<<roll<<endl;
}
void student::checkroll(student obj[],int j)
{
  int k;
  for(k=0;k<j;k++)
    if(obj[k].roll==this->roll)
      {
	cout<<"\nDuplication of Roll No is not allowed,plz enter again:";
	cin>>roll;
	obj[j].checkroll(obj,j);
	break;
      }
}
int readstuinfo(student st[])
{
  char ch='y';
  int j=0;
  cout<<"\nDo you want to read a student record? (y/n) ";
  cin>>ch;
  cout<<ch;
  while(ch=='y')
  {
    st[j].constinfo();
    st[j].checkroll(st,j);
    cout<<"\nDo you want to read a student record? (y/n) ";
    cin>>ch;
    cout<<ch;
    j++;
  }
 cout<<"\nTotal of "<<j<<" records have been read.\n";
 return j;
}
void savestuinfo(student st[],int j,fstream &file)
{
  file.open("test",ios::out|ios::in|ios::trunc);
  char ch;
  cout<<"\nDo you want to save the student record read? (y/n) ";
  cin>>ch;
  cout<<ch;
  if(ch=='y')
    {
      for(int i=0;i<j;i++)
	file.write((unsigned char *)&st[i],sizeof(st[i]));
      cout<<"\nRead info has been saved in a file.\n";
    }
}
void extract(student st[],fstream &file)
{
  file.open("test",ios::out|ios::in);
  file.seekg(0,ios::end);
  int n=file.tellg()/sizeof(st[0]);

  file.seekg(0,ios::beg);
  for(int i=0;i<n;i++)
    file.read((unsigned char*)&st[i],sizeof(st[i]));
}
void putintofile(student st[],int n,fstream &file)
{
  file.open("test",ios::out|ios::in|ios::trunc);
  file.seekp(0,ios::beg);
  for(int i=0;i<n;i++)
    file.write((unsigned char*)&st[i],sizeof(st[i]));
}

void del(student st[],fstream &file)
{
  int n,m=sizeof(st[0]),rl;
  int endpos=file.tellg();
  n=endpos/m;
 
  cout<<"\nEnter the roll no,the record for which has to be deleted:";
  cin>>rl;
  cout<<"\nEntered roll no= "<<rl;
  extract(st,file);

  int i=0;
  while(st[i].roll!=rl)
    i++;
  if(i>=n)
    cout<<"\nThe roll no "<<rl<<" doesn't exist.";
  else
    {
      for(int j=i+1;j<n;j++)
        st[j-1]=st[j];
    }
  putintofile(st,n-1,file);
  extract(st,file);
}
void modify(student st[],fstream &file)
{
  file.open("test",ios::out|ios::in);
  int i=0,rl,n;
  file.seekg(0,ios::end);
  n=file.tellg()/sizeof(st[0]);
  extract(st,file); //contents of the file extracted into st[]

  cout<<"\nEnter the roll no the record for which has to be modified:";
  cin>>rl;
  cout<<"\nThe roll no entered is: "<<rl;
  while(st[i].roll!=rl)
    i++;
  if(i>=n)
    cout<<"\nThe roll no "<<rl<<" doesn't exist.";
  else
    {
      cout<<"\nEnter the new name to be recorded agianst Roll No : "<<rl;
      cin>>st[i].name;
      cout<<"\nModified Name: "<<st[i].name;
    }
  putintofile(st,n,file);
  extract(st,file);
}
void displaytoroll(student st[],fstream &file)
{
  file.open("test",ios::out|ios::in);
  int i=0,rl,n;
  file.seekg(0,ios::end);
  n=file.tellg()/sizeof(st[0]);
  extract(st,file); //contents of the file extracted into st[]

  cout<<"\nEnter the roll no,the record for which is to be displayed: ";
  cin>>rl;
  cout<<"\nThe roll no entered is: "<<rl;
  while(st[i].roll!=rl)
    i++;
  if(i>=n)
    cout<<"\nThe roll no "<<rl<<" doesn't exist.";
  else
    st[i].displayinfo();
}
void displaybyname(student st[],fstream &file)
{
  file.open("test",ios::out|ios::in);
  student temp;
  int i,j,n;
  file.seekg(0,ios::end);
  n=file.tellg()/sizeof(st[0]);
  extract(st,file); //contents of the file extracted into st[]
  cout<<"\nTHE CONTENT OF THE FILE: \n";
  for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++)
      if(strcmp(st[i].name,st[j].name)>0)
	{
	  temp=st[i];
	  st[i]=st[j];
	  st[j]=temp;
	}
  putintofile(st,n,file);
  extract(st,file);
  for(i=0;i<n;i++)
    st[i].displayinfo();
  }
main()
{
  student st[100];
  int i,j;
  j=readstuinfo(st); //no of records

  fstream file;     //  ("test",ios::in|ios::out|ios::trunc);
  savestuinfo(st,j,file);
  displaybyname(st,file);
  displaytoroll(st,file);
  modify(st,file);
  displaybyname(st,file);
  del(st,file);
  displaybyname(st,file);
}



Do you want to read a student record? (y/n) y
Enter Name: 
Enter RollNo: 
The Name of the student entered is: pankaj and the Roll No entered is: 11

Do you want to read a student record? (y/n) y
Enter Name: 
Enter RollNo: 
The Name of the student entered is: joydeep and the Roll No entered is: 24

Do you want to read a student record? (y/n) y
Enter Name: 
Enter RollNo: 
The Name of the student entered is: ashish and the Roll No entered is: 2

Do you want to read a student record? (y/n) y
Enter Name: 
Enter RollNo: 
The Name of the student entered is: indrava and the Roll No entered is: 1

Do you want to read a student record? (y/n) y
Enter Name: 
Enter RollNo: 
The Name of the student entered is: sumit and the Roll No entered is: 12

Do you want to read a student record? (y/n) n
Total of 5 records have been read.

Do you want to save the student record read? (y/n) y
Read info has been saved in a file.

THE CONTENT OF THE FILE: 

The Students Information:
Name: ashish
Roll No :2

The Students Information:
Name: indrava
Roll No :1

The Students Information:
Name: joydeep
Roll No :24

The Students Information:
Name: pankaj
Roll No :11

The Students Information:
Name: sumit
Roll No :12

Enter the roll no,the record for which is to be displayed: 
The roll no entered is: 11
The Students Information:
Name: pankaj
Roll No :11

Enter the roll no the record for which has to be modified:
The roll no entered is: 12
Enter the new name to be recorded agianst Roll No : 
Modified Name: vihang

THE CONTENT OF THE FILE: 

The Students Information:
Name: ashish
Roll No :2

The Students Information:
Name: indrava
Roll No :1

The Students Information:
Name: joydeep
Roll No :24

The Students Information:
Name: pankaj
Roll No :11

The Students Information:
Name: vihang
Roll No :12

Enter the roll no,the record for which has to be deleted: 
Entered roll no= 24

THE CONTENT OF THE FILE: 

The Students Information:
Name: ashish
Roll No :2

The Students Information:
Name: indrava
Roll No :1

The Students Information:
Name: pankaj
Roll No :11

The Students Information:
Name: vihang
Roll No :12
