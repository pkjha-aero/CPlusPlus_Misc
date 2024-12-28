// Stream Class
#include<iostream>
using namespace std;

class cl
{
  int x,y,z; // private is fine since ostream is a friend and can access these variables
public:
  cl(int a,int b,int c)
  {
    x=a;y=b;z=c;
  }
  friend ostream &operator<<(ostream & stream,cl obj);
};
ostream &operator<<(ostream &var,cl obj)  // passing 'obj' by reference is not  a must
{
  var<<obj.x<<",";  //'var' can be replaced by any variable name
  var<<obj.y<<",";
  var<<obj.z<<"\n";
  return var;
}
main()
{
  cl a(1,2,3),b(4,5,6),c(7,8,9);
  cout<<a<<b<<c;
}
