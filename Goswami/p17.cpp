// Pointers to objects
// Tips: 
#include<iostream>
using namespace std;

class p_example
{
  int num;
public:
  void set_num(int val){num=val;}
  void show_num(){cout<<"\n The number is :"<<num;}
};

main()
{
  p_example ob,*p;
  ob.set_num(10);
  ob.show_num();
  p=&ob;
  p->show_num();
  p->set_num(20); // change in the address itself
  p->show_num();
  cout<<"\n";
}
