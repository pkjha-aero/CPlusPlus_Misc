//PANKAJ KUMAR JHA
//01 MA 2011
//ASSIGNMENT 6

#include<iostream.h>
#include<fstream.h>

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
  while(ch=='y')
  {
    st[j].constinfo();
    st[j].checkroll(st,j);
    cout<<"\nDo you want to read a student record? (y/n) ";
    cin>>ch;
    j++;
  }
 cout<<"\nTotal of "<<j<<" records have been read.\n";
 return j;
}
void savestuinfo(student st[],int j,fstream &file)
{
  char ch;
  cout<<"\nDo you want to save the student record read? (y/n) ";
  cin>>ch;
  if(ch=='y')
    for(int i=0;i<j;i++)
      file.write((unsigned char *)&st[i],sizeof(st[i]));
}
main()
{
  student st[100];
  int i,j;
  j=readstuinfo(st); //no of records

  fstream file("test",ios::in|ios::out|ios::trunc);
  savestuinfo(st,j,file);
//   for(i=0;i<j;i++)
//     {
//       file.write((unsigned char *)&st[i],sizeof(st[i]));
//     }
}
