// Pointers to derived types
// Tip: Only inherited members of derived class can be accessed by base pointer
#include<iostream>
#include<string.h>
using namespace std;

class B_class
{
  char name[80];
public:
  void putname(char s[])
  {
    strcpy(name,s);
  }
  void showname()
  {
    cout<<endl<<name;
  }
};

class D_class:public B_class
{
  char phone[15];
public:
  void putphone(char s[])
  {
    strcpy(phone,s);
  }
  void showphone()
  {
    cout<<endl<<phone;
  }
};

main()
{
  B_class B_ob,*p;
  D_class D_ob,*dp;
  p=&B_ob;
  p->putname("ABC");
  p->showname();
  p=&D_ob;
  p->putname("DEF");
  p->showname();
  B_ob.showname();
  D_ob.showname();
  p=&B_ob;
  p->showname();
  p=&D_ob;
  p->showname();
  // A pointer to base class can be used to point to an object of derived class
  // But using that pointer only inherited members can be accessed
  //p->putphone("123456");//no matching fun 4 call to B_class::putphone
  // Error in DevC++: 'class B_class' has no member named 'putphone'
  //p->showphone();
  dp=&D_ob;
  dp->putname("MNOP");
  dp->showname();
  dp->putphone("91-6531-235263");
  dp->showphone();
  cout<<endl;
}
