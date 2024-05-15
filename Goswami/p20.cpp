// OPERATOR OVERLOADING

#include<iostream>
using namespace std;

class cl
{
  int x,y,z;
public:
  cl operator+(cl t);
  cl operator=(cl t);
  void show();
  void assign(int mx,int my,int mz);
};

main()
{
  cl a,b,c;
  a.assign(1,2,3);
  b.assign(4,5,6);
  a.show();
  b.show();
  c=a+b;
  c.show();
  c=a+b+c;
  c.show();
  b.show();
  c=b=a;
  a.show();
  b.show();
  c.show();
  cout<<"\n";
}

cl cl::operator+(cl t)
{
  cl temp; // we are able to access the private members of an object of the same class
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

void cl::show()
{
  cout<<"\nx: "<<x<<" y: "<<y<<" z: "<<z;
}
void cl::assign(int mx,int my,int mz)
{
  x=mx;
  y=my;
  z=mz;
}
