// Call by value, not by reference
// Tips: 
#include<iostream>
using namespace std;

class obj
{
  int i;
public:
  void set_i(int x){i=x;}
  void out_i(){cout<<"\ni: "<<i;}
};

void f(obj a);

main()
{
  obj b;
  b.set_i(10);
  f(b);
  cout<<"\nIn main i: ";
  b.out_i();
  cout<<"\n";
}

void f(obj a)  // only a copy of the object a is passed
{
  cout<<"\nIn func f, i :";
  a.out_i();
  a.set_i(100);
  cout<<"\nAfter changing in func,i :";
  a.out_i();
}
