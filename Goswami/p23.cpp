//OVERLOADING THE UNARY OPERATOR ++
// Tip : For prefix form of unary operator no argument needed
// 	     For postfix form, a dummy argument is needed, though not used
#include<iostream>
using namespace std;

class cl
{
  int x,y,z;
public:
  cl operator+(cl t);
  cl operator=(cl t);
  cl operator++();  //prefix form
  cl operator++(int i);  //postfix form ,dummy argument
  void assign(int mx,int my,int mz);
  void show();
};

cl cl::operator+(cl t)
{
  cl temp;
  temp.x=this->x+t.x;
  temp.y=this->y+t.y;
  temp.z=this->z+t.z;
  return temp;
}
cl cl::operator=(cl t)
{
  this->x=t.x;
  this->y=t.y;
  this->z=t.z;
  return *this;
}
cl cl::operator++()
{
  (this->x)++;
  (this->y)++;
  (this->z)++;
  return *this;
}
cl cl::operator++(int i)
{
  cl temp;
  temp=*this;
  x++;
  y++;
  z++;
  return temp;
}

void cl::assign(int mx,int my,int mz)
{
  x=mx;
  y=my;
  z=mz;
}
void cl::show()
{
  cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<"\n";
}
main()
{
  cl a,b,c;
  a.assign(1,3,5);
  b.assign(6,4,2);
  a.show();
  b.show();
  c=a+b;
  c.show();
  c=a+b+c;
  c.show();
  ++c;
  c.show();
  b=c++;
  b.show();
  c.show();
  c=b=a;
  c.show();
  b.show();
  a.show();
}
