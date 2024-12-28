// iomanip
#include<iostream>
#include<iomanip>
using namespace std;

main()
{
  cout<<setprecision(10)<<1000.243<<endl;
  cout<<setw(15)<<setfill('#')<<"Hello"<<endl;
  cout.setf(ios::showpos);
  //cout<<setioflags(ios::showpos); //this line not working in linux
  cout<<123<<endl;
}
