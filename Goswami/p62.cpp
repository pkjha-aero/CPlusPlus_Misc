#include<iostream.h>
#include<fstream.h>

class inventory
{
  char name[15];
  int code;
public:
  void getdata();
  void putdata();
};

void inventory::getdata()
{
  cout<<"\nEnter name: ";cin>>name;
  cout<<"\nEnter code: ";cin>>code;
}
void inventory::putdata()
{
  cout<<name<<" ";
  cout<<code<<" "<<endl;
}

main()
{
  int i;
  inventory item,items;
  fstream inoutfile("test",ios::in|ios::out);//both input & output mode
  inoutfile.seekg(0,ios::beg);
  cout<<"\n Content of the file:\n";
  while(inoutfile)
    {
      inoutfile.read((unsigned char *)&item,sizeof(item));
      item.putdata();
    }
  //inoutfile.clear();
  cout<<"\nAdd an item\n";
  item.getdata();
  char ch;

  cin.get(ch); // for what??

  inoutfile.seekp(0,ios::end);
  int fileptr=inoutfile.tellg();
  cout<<"\nCurrent Location of File Pointer= "<<fileptr; 
  inoutfile.write((unsigned char *)&item,sizeof(item));

  inoutfile.seekg(0,ios::beg);
  fileptr=inoutfile.tellg();
  cout<<"\nCurrent Location of file ptr= "<<fileptr;
  cout<<"\nContent of the appended file:\n";
  while(!inoutfile.eof())
    {
      inoutfile.read((unsigned char *)&item,sizeof(item));
      item.putdata();  //all read & displayed
    }

  int last=inoutfile.tellg();
  cout<<"\nlast="<<last;
  int n=last/sizeof(item);
  cout<<"\nNo of objects="<<n;

  cout<<"\nEnter the object no to be modified: ";
  int ob;
  cin>>ob;

  cin.get(ch); //for what??

  int location=(ob-1)*sizeof(item);
  cout<<"\nLocation="<<location;
  inoutfile.seekp(location,ios::beg);
  item.getdata();
  inoutfile.write((unsigned char *)&item,sizeof(item));
  
  cin.get(ch);

  location=location-sizeof(item);
  cout<<"\nLocation="<<location;
  inoutfile.seekg(0,ios::beg);
  fileptr=inoutfile.tellg();
  cout<<"\nCurrent Location of file ptr= "<<fileptr;
  while(!inoutfile.eof())
    {
      inoutfile.read((unsigned char *)&item,sizeof(item));
      item.putdata();  //all read & displayed
    }
}
