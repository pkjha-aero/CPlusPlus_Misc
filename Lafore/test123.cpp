// I/O with multiple objects using File Poiter

#include<iostream.h>
#include<fstream.h>
#include<cassert>

using namespace std;

class person
{
  char name[15];
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
  fstream file;
  file.open("test",ios::out|ios::in|ios::trunc);
  do
    {
      cout<<"\nEnter person's data: ";
      pers.constructdata();   //get one person's data
      file.write((unsigned char *)&pers,sizeof(pers));
      assert(0);
      cout<<"\nDo you want to add any other person's data?(y/n) ";
      cin>>ch;
    }while(ch=='y');  //read person's data until you want


  file.seekg(0,ios::beg);   //move file poiter to beg of file
  
  file.read((unsigned char *)&pers,sizeof(pers));//read first person
  while(!file.eof())
    {
      cout<<"\nPerson:";
      pers.displaydata();
      file.read((unsigned char *)&pers,sizeof(pers));//read from file
    }
  cout<<endl;

  //return 0; no need of this statement

  file.seekg(0,ios::end); //go 0 bytes from the end of file
  int endpos=file.tellg();// total no of bytes
  cout<<"\nsize of person="<<sizeof(person);
  cout<<"\nendpos="<<endpos;
  int n=endpos/sizeof(person); //no of persons
  cout<<"\nThere are "<<n<<" persons in file.";

  cout<<"\nEnter person no whose data has to be changed:";
  cin>>n;
  cout<<"\nn="<<n;

  int pos=(n-1)*sizeof(person);
  cout<<"\npos="<<pos<<endl;

  cin.get(ch);

  file.seekp(pos);
  int fileptr=file.tellg();
  cout<<"\nCurrent Location of File Pointer="<<fileptr;
  pers.constructdata();
  file<<"pankaj";
  file.write( reinterpret_cast<char*>(&pers),sizeof(pers));

  pos=pos-sizeof(pers);
  cout<<"pos="<<pos;

  cin.get(ch);

  file.seekg(pos); //go pos no of bytes from beg
  fileptr=file.tellg();
  cout<<"\nCurrent Location of File Poiter="<<fileptr;
  file.read( reinterpret_cast<char*>(&pers2),sizeof(pers2));
  pers2.displaydata();
  cout<<endl;
  file.close();
}
