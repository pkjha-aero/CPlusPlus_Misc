// Reference parameter

#include<iostream>
using namespace std;

void swap(int *a,int *b);

main()
{
  int i,j;
  i=10;
  j=20;
  cout<<endl<<i<<" "<<j<<endl;
  swap(&i,&j);
  cout<<endl<<i<<" "<<j<<endl;
}

void swap(int *a,int *b)
{
  int t;
  t=*a;
  *a=*b;
  *b=t;
}
