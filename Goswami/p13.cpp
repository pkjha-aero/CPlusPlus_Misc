// Virtual Class and Mutilple Inheritance
// Tips: 
#include<iostream>
using namespace std;

class base
{
public:
  int i;
};
class d1:virtual public base
{
public:
  int j;
};
class d2:virtual public base
{
public:
  int k;
};

class d3:public d1,public d2
{
public:
  int m;
};

main()
{
  d3 d;
  d.i=4; // simply d.i is ok when virtual public base is used
  d.j=7 ;
  d.k=9 ;
  d.m=11;
  cout<<"i:"<<d.i<<" j:"<<d.j<<" k:"<<d.k<<" m:"<<d.m<<"\n";
}//here also d.i is enuff
