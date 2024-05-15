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
  p_example ob[2],*p;
  ob[0].set_num(10);
  ob[1].set_num(15);
  p=ob;  // p=&ob[0] is also ok
  p->show_num();
  p++;
  p->show_num();
  p->set_num(20); // change in the address itself
  p->show_num();
  p--;
  p->show_num();
  p->set_num(12);
  p->show_num();
  cout<<"\n";
}
