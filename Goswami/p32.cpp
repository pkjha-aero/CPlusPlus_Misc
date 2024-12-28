// Virtual function
// Tip: 
#include<iostream>
using namespace std;

class base
{
public:
  virtual void who()
  {
    cout<<"Base \n";
  }
};
class fd:public base
{
public: 
  void who()
  {
    cout<<"First Derivative\n";
  }
};
class sd:public base
{
public:
  void who()
  {
    cout<<"Second Derivative\n";
  }
};

main()
{
  base base_obj,*p;
  fd fobj;
  sd sobj;
  p=&base_obj;
  p->who();
  p=&fobj;
  p->who();
  p=&sobj;
  p->who();
}
