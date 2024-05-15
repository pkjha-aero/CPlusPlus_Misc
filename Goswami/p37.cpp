// Formatting I/0
#include<iostream>
using namespace std;

main()
{
  cout.setf(ios::showpos);
  cout.setf(ios::scientific);
  cout<<123<<","<<123.23<<endl;
  
  cout.precision(4); //concerned with floats
  cout.width(15);    //concerned with int
  cout<<123<<","<<123.23<<endl;
  
  cout.fill('$');
  cout.width(16);
  cout<<123<<","<<123.23<<endl;
}
