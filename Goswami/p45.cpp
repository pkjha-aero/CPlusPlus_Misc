// Tip: integer operation takes precence over class operation
#include<iostream>
using namespace std;

class cl
{
  int x,y,z;
public:
  cl(int a,int b,int c){x=a;y=b;z=c;}
  cl operator+(cl obj);
  friend ostream &operator<<(ostream &stream,cl &obj);
  operator int(){return x*y*z;}
};

ostream &operator<<(ostream & stream,cl &obj)
{
  stream<<obj.x;
  stream<<obj.y;
  stream<<obj.z;
  return stream;
}

cl cl::operator+(cl obj)
{
  cl temp(0,0,0);
  temp.x=x+obj.x;
  temp.y=y+obj.y;
  temp.z=z+obj.z;
  return temp;
}

main()
{
  cl a(1,2,3),b(3,5,2),c(0,0,0);
  cout<<a<<" "<<b<<endl;
  //cout.setf(ios::showpos);
  cout<<a+100;
  cout<<endl;
  cout<<(a+b)<<endl;//this gives 315 as o/p
  // The output from below expression is not very clear 
  c=a+b; // integer operation takes precence over class operation
  cout<<c<<endl;
}
