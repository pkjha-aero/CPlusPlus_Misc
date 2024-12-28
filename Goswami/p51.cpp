// Overloaded function template
#include<iostream>
using namespace std;

struct A
{
  int x; int y;
};
struct B
{
  int x;
  double y;
};

template<class T>
void assign_A(T a,T b,A &s1)
{
  s1.x=a;
  s1.y=b;
}
template<class T,class U>
void assign_B(T a,U b,B &s2)
{
  s2.x=a;
  s2.y=b;
}

main()
{
  A s1;
  B s2;
  assign_A(3,4,s1);
  cout<<s1.x<<endl<<s1.y<<endl;
  assign_B(5,9.42,s2);
  cout<<s2.x<<endl<<s2.y<<endl;
}
