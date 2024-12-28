// I/O with multiple objects using File Poiter

#include<iostream>
#include<fstream>

using namespace std;

class person
{
  char name[10];
  int age;
public:
  void constructdata()
  {
    cout<<"\nEnter name: ";
    cin>>name;
    cout<<"\nEnter age: ";
    cin>>age;
  }
  void displaydata()
  {
    cout<<"\nName: "<<name<<"\nAge: "<<age;
  }
};

main()
{
  char ch;
  person pers,pers2;
  fstream file("test",ios::in|ios::out|ios::trunc);
  do
    {
      cout<<"\nEnter person's data: ";
      pers.constructdata();   //get one person's data
      file.write( reinterpret_cast<char*>(&pers),sizeof(pers));
      cout<<"\nDo you want to add any other person's data?(y/n) ";
      cin>>ch;
    }while(ch=='y');  //read person's data until you want

  //this seekg working as eof not encountered
  file.seekg(0,ios::beg);   //move file poiter to beg of file
  
  file.read( reinterpret_cast<char*>(&pers),sizeof(pers));//read first person
  while(!file.eof())
    {
      cout<<"\nPerson:";
      pers.displaydata();
      file.read( reinterpret_cast<char*>(&pers),sizeof(pers));//read from file
    }
  file.close();
 
 //after reading file is closed....so that tellg() doesnot return -1
  //open with another name say file2

  fstream file2("test",ios::in|ios::out); 

  file2.seekg(0,ios::end);
  int fileptr=file2.tellg();
  cout<<"\nLocation of the file pointer is:"<<fileptr;

  //return 0; no need of this statement

  file2.seekg(0,ios::end); //go 0 bytes from the end of file
  int endpos=file2.tellg();// total no of bytes
  cout<<"\nsize of person="<<sizeof(person);
  cout<<"\nendposition="<<endpos;
  int n=endpos/sizeof(person); //no of persons
  cout<<"\nThere are "<<n<<" persons in file.";

  int m;
  cout<<"\nEnter person no whose data has to be changed:";
  cin>>m;
  cout<<endl<<"m="<<m;

  int pos=(m-1)*sizeof(person);
  cout<<"\npos="<<pos<<endl;

  cin.get(ch); //what is it's use??

  file2.seekp(pos);
  fileptr=file2.tellg();
  cout<<"\nCurrent Location of File Pointer="<<fileptr;
  pers.constructdata();
  file2.write( reinterpret_cast<char*>(&pers),sizeof(pers));

  pos=pos-sizeof(pers);
  cout<<"\npos="<<pos;

  cin.get(ch);

  file2.seekg(pos); //go pos no of bytes from beg
  fileptr=file2.tellg();
  cout<<"\nCurrent Location of File Poiter="<<fileptr;
  file2.read( reinterpret_cast<char*>(&pers2),sizeof(pers2));
  pers2.displaydata();
  cout<<endl;
  file2.close();
}
