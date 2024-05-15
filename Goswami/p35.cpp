// Formatting I/0
#include<iostream>
using namespace std;

main()
{
  cout.setf(ios::showpos);
  cout.setf(ios::scientific);
  cout.setf(ios::left);
  cout.setf(ios::right);
  cout.setf(ios::showbase);
  cout.setf(ios::uppercase);
  cout.setf(ios::unitbuf);
  cout.setf(ios::internal);
  cout<<123<<", "<<123.23<<", Hum hain Yum"<<endl;
}
