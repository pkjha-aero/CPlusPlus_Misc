//user-defined template arguments
#include<iostream>
using namespace std;

struct sturec
{
  char name[30];
  int age;
};

template<class T>
void display(T &t)
{
  cout<<t<<endl;
}

ostream &operator<<(ostream &out,sturec &s)  // reference parameter needed if insertion operator used
{
  out<<s.name<<endl;
  out<<s.age<<endl;
  return out;
}

main()
{
  sturec s1;
  cin>>s1.name;
  s1.age=22;
  display(s1.name);
  display(s1.age);
  display(s1);
}
