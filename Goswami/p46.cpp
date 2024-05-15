// Dynamic Allocation
#include<iostream>
using namespace std;

main()
{
  int *p;
  p=new int;
  if(!p)
    {
      cout<<"Allocation Failure\n";
      return 1;
    }
  *p=20;
  cout<<*p; //20 o/p
  cout<<endl<<p<<endl;  //0x8049988 o/p
  delete p;
  float *q;
  q=new float[10];
  delete q;  //delete[10] q not working
}
