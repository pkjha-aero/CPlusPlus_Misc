// Inline Function
// Tips: Inline function may have a return type unlike macro
// Tips: Wrting body within class makes the function inline
#include<iostream>
using namespace std;

class cl
{
  int i;
public:
  int get_i(){return i;} // writing the body here makes the function inline
  void put_i(int j){i=j;}
};

main()
{
  cl s;
  s.put_i(12);
  cout<<"i= "<<s.get_i()<<"\n";
}
