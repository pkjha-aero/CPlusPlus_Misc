// Pure Virtual function and Abstract Class
// Tip: We can't declare any obj of abstract base class, but can declare a pointer to it
// Tip: virtual base func doesn't have any body
#include<iostream>
#include<string.h>
using namespace std;

class base
{
public:
  virtual void who()=0;
    /*{
    cout<<"Base \n";// virtual base func doesn't have any body
    }*/
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
  base *p;  // We can't declare any obj of abstract base class, but can declare pointer
  fd fobj;
  sd sobj;
  //p=&base_obj;
  //p->who();
  p=&fobj;
  p->who();
  p=&sobj;
  p->who();
}
