#include<iostream.h>
#include<fstream.h>

class cl
{
public:
  char name[30];
  int code;
  float cost;
  void putdata()
  {
    cout<<"\nEnter name: ";cin>>name;
    cout<<"\nEnter code: ";cin>>code;
    cout<<"\nEnter cost: ";cin>>cost;
  }
  //ostream &operator<<(ostream &stream,cl obj);//no need of friend
};
ostream &operator<<(ostream &stream,cl obj)
{
  stream<<obj.name<<" ";
  stream<<obj.code<<" ";
  stream<<obj.cost<<endl;
  return stream;
}

main()
{
  cl obj[3];
  int i;
  for(i=0;i<3;i++)
    obj[i].putdata();

  ofstream out("test");
  out.write((unsigned char *) &obj,sizeof(obj));
  out.close();

  ifstream in("test");
  in.read((unsigned char *)&obj,sizeof(obj));
  in.close();

  for(i=0;i<3;i++)
    cout<<obj[i];
}
