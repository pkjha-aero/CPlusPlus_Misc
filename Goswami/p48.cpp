//overloading new & delete in a class,can't be done in general
#include<iostream>
#include<stdlib.h>
using namespace std;

class cl
{
public:
  int x,y,z;
  cl(int a,int b,int c){x=a;y=b;z=c;}
  cl(){x=0;y=0;z=0;}
  ~cl(){cout<<"Destructing\n";}
  void *operator new(size_t size);  //overloading new
  void operator delete(void *p);
};

void *cl::operator new(size_t size)
{
  return malloc(size);
}
void cl::operator delete(void *p)
{
  free(p);
}

ostream &operator<<(ostream &stream,cl &obj)
{
  stream<<obj.x;
  stream<<obj.y;
  stream<<obj.z;
  return stream;
}

main()
{
  cl *p,*p1;
  p=new cl(1,2,3);  //this can be done without overloading new also
  p1=new cl(4,5,6); //where is this overloading useful then???
  cout<<*p<<endl<<*p1<<endl<<p<<endl<<p1<<endl;
  delete p;
  delete p1;
}
