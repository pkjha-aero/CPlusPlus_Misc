// Virtual Class and Mutilple Inheritance
// Tips: 
#include<iostream>
using namespace std;

class base
{
public:
  int i;
};
class d1:public base
{
public:
  int j;
};
class d2:public base
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
  d.d1::i=10; // simply d.i gives error
  d.j=20;
  d.k=30;
  d.m=40;
  cout<<"i:"<<d.d1::i<<" j:"<<d.j<<" k:"<<d.k<<" m:"<<d.m<<"\n";
}//here also d.d2::i has to be mentioned otherwise ambiguity ocurs
