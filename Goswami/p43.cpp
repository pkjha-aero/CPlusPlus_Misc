// Static class members
// Tip: Static variable must be declared globally
#include<iostream>
using namespace std;

class counter
{
  static int count;
public:
  counter()
  {
    count=0;
  }
  void setcount(int i)
  {
    count=i;
  }
  void showcount()
  {
    cout<<count<<endl;
  }
};
int counter::count;  //int var count of class counter declared globally// when by mistake i wrote couter.....messg:--syntax error b4 ::

main()
{
  counter a,b;
  a.showcount();
  b.showcount();
  a.setcount(10);
  a.showcount();
  b.showcount();
}
