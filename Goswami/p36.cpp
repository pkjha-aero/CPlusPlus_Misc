// Formatting I/0
#include<iostream>
using namespace std;

void showflags(long f);

main()
{
  long f;
  f=cout.flags();
  showflags(f);
  
  cout.setf(ios::showpos); // b'coz of this + is coming b4 0 or 1
  cout.setf(ios::scientific);
  f=cout.flags();
  showflags(f);
  
  cout.unsetf(ios::scientific);
  f=cout.flags();
  showflags(f);
  
  cout.unsetf(ios::dec);
  f=cout.flags();
  showflags(f);
}

void showflags(long f)
{
  int count=15;
  while(count!=0)
    {
      cout<<f%2<<" ";
      f=f/2;
      count--;
    }
  cout<<endl;
}
