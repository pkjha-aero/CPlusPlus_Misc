//OVERLOADING THE UNARY OPERATOR ++

#include<iostream>
using namespace std;

class cl
{
  int x,y,z;
public:
  cl operator+(cl t);
  cl operator=(cl t);
  //cl operator++();  //prefix form
  friend cl operator++(cl &op); // with or without '&' the results are different
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

/*
cl cl::operator++()
{
  (this->x)++;
  (this->y)++;
  (this->z)++;
  return *this;
}*/
// If I use this operator as well,ambiguity & doesn't compile

cl operator++(cl &op)
{
  op.x++;
  op.y++;
  op.z++;
  return op;
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
  ++c;   // error when i wrote c++,only prefix form works
  c.show();
  c=b=a;
  c.show();
  ++c;  // postfix case not acceptable
  c.show();
  b.show();
  a.show();
}
