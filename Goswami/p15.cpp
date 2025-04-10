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

void f1(obj a); // Pass by value
void f2(obj &a); // Pass by reference

main()
{
  obj b;
  b.set_i(10);

  f1(b);
  cout<<"\nIn main i: ";
  b.out_i();
  cout<<"\n";

  f2(b);
  cout<<"\nIn main i: ";
  b.out_i();
  cout<<"\n";
}
void f1(obj a) // Pass by value, only a copy of the object a is passed
{
  cout<<"\nIn func f1, i :";
  a.out_i();
  a.set_i(100);
  cout<<"\nAfter changing in func,i :";
  a.out_i();

}
void f2(obj &a)  // Pass by reference
{
  cout<<"\nIn func f2, i :";
  a.out_i();
  a.set_i(100);
  cout<<"\nAfter changing in func,i :";
  a.out_i();
}
