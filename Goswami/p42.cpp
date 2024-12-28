// USE YOUR OWN MANIPULATOR
#include<iostream>
#include<iomanip>
using namespace std;

ostream &setup(ostream &stream)
{
  stream.setf(ios::left);
  stream<<setw(10)<<setfill('#');
  return stream;
}
main()
{
  cout<<10<<endl;
  cout<<setup<<10;
}
//not working properly
