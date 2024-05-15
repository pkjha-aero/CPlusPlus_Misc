//FUNCTION TEMPLATE HAVE BEEN USED INSTEAD OF 3 FUNC TO MAKE TASK EASIER
#include<iostream>
using namespace std;

void swap(char &x,char &y)
{
  char t;
  t=x; x=y;y=t;
}
void swap(int &x,int &y)
{
  int t;
  t=x;x=y;y=t;
}
void swap(float &x,float &y)
{
  float t;
  t=x;x=y;y=t;
}

/*
// Not sure why not working
template<class T>
void swap(T &x, T &y)
{
  T t;
  t=x; x=y;y=t;
}*/
main()
{
  char c1='&',c2='#';
  swap(c1,c2);
  cout<<c1<<endl<<c2<<endl;
  
  int i1=10,i2=20;
  swap(i1,i2);
  cout<<i1<<endl<<i2<<endl;
  
  float f1=3.4,f2=6.8;
  swap(f1,f2);
  cout<<f1<<endl<<f2<<endl;
}
