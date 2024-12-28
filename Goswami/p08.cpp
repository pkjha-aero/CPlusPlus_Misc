// Inline Function
// Tips: Inline function may have a return type unlike macro
// Tips: Wrting body within class makes the function inline
// Tips: Compiler may ignore to treat a function as inline
#include<iostream>
using namespace std;

class cl
{
  int i;
public:
  int get_i();
  void put_i(int j);
};

inline int cl::get_i()
{
  return i;
}

inline void cl::put_i(int j)
{
  i=j;
}

main()
{
  cl s;
  s.put_i(14);
  cout<<"i= "<<s.get_i()<<"\n";
}
