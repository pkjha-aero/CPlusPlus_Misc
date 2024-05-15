#include<iostream.h>
#include<fstream.h>

class inventory
{
  char name[20];
  int code;
  float cost;
public:
  void readdata();
  void writedata();
};

void inventory::readdata()
{
  cout<<"\nEnter name: ";cin>>name;
  cout<<"\nEnter code: ";cin>>code;
  cout<<"\nEnter cost: ";cin>>cost;
}
void inventory::writedata()
{
  cout<<name<<" ";
  cout<<code<<" ";
  cout<<cost<<endl;
}

main()
{
  int i;
  inventory item[3];

  ofstream file("test");//output mode

  for(i=0;i<3;i++)
    {
      item[i].readdata();
      file.write((unsigned char *)&item[i],sizeof(item[i]));
    }
  file.close();
  //file.seekg(----)to move ptr to the beginning

  ifstream files("test");

  for(i=0;i<3;i++)
   {
     files.read((unsigned char *)&item[i],sizeof(item[i]));
     item[i].writedata();
   }
  files.close();  //if both are file conflicting types
}
