// Stream Class
#include<iostream>
using namespace std;

class cl
{
  int x,y,z; // private is fine since ostream/istream is a friend and can access these variables
public:
  cl(int a,int b,int c)
  {
    x=a;y=b;z=c;
  }
  friend istream &operator>>(istream &stream,cl &obj); //for input we are forced to use ref parameters
  friend ostream &operator<<(ostream & stream,cl &obj);
};
ostream &operator<<(ostream &var,cl &obj) // passing 'obj' by reference is NOT a must
{
  var<<obj.x<<",";  //'var' can be replaced by any variable name
  var<<obj.y<<",";
  var<<obj.z<<"\n";
  return var;
}
istream &operator>>(istream &var,cl &obj) //passing 'obj' by reference is a MUST
{
  cout<<"Enter x,y,z values:";
  var>>obj.x>>obj.y>>obj.z;
  return var;
}
main()
{
  cl a(1,2,3),b(0,0,0);// simply writing b gives error,doesn't compile
  cout<<a;             //says 'mismatch' as the declaration must match one of the defined constructors
  cin>>b;
  cout<<b;
}
