// Function Overloading
#include<iostream>
using namespace std;

int sqr_it(int i)
{
  return i*i;
}

double sqr_it(double d)
{
  return d*d;
}

long sqr_it(long l)
{
  return l*l;
}

main()
{
  cout<<"Square of 10:"<<sqr_it(10)<<"\n";
  cout<<"Square of 11.5:"<<sqr_it(11.5)<<"\n";
  cout<<"Square of 9000L :"<<sqr_it(9000L)<<"\n";
}
