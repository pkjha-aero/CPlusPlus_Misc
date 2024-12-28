// Dynamic Allocation
//initialising object thru new
#include<iostream>
using namespace std;

class cl
{
public:
  int x,y,z;
  cl(int a,int b,int c){x=a;y=b;z=c;}
  cl(){x=0;y=0;z=0;}
  ~cl(){cout<<"Destructing\n";}
};

ostream &operator<<(ostream &stream,cl obj)
{
  stream<<obj.x;
  stream<<obj.y;
  stream<<obj.z;
  return stream;
}

main()
{
  cl *p;
  p=new cl(1,2,3);  // values must
  cout<<*p<<endl;  //123 o/p
  cout<<p<<endl;   //0x8049c40 0/p
  delete p;
}
