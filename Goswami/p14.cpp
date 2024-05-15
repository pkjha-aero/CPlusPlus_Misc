// Mutilple Inheritance, Protected Member
// Tips: 
#include<iostream>
using namespace std;

class X
{
protected:
  int a;
public:
  X(int i){a=i;}
};
class Y
{
protected:
  int b;
public:
  Y(int i){b=i;}
};

class Z:public X,public Y
{
public:
  Z(int x,int y);// no need of writig as sir has done
  int get_ab(){return a*b;}
};
Z::Z(int x,int y):X(x),Y(y)
{
}
main()
{
  Z o(10,20);
  cout<<"ab: "<<o.get_ab()<<"\n";
 //cout<<"a :"<<o.a<<" b: "<<o.b<<" ab:"<<o.get_ab()<<"\n";
  // the second cout statement is not working,a & b not accessible since an object of the derived class can't access the protected members of the base class
}
