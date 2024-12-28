// Returning a Reference parameter
// Tip: 

#include<iostream>
using namespace std;

int &f1()
{
  int i;
  cout<<endl<<"Give i:";
  cin>>i;
  return i;
}

main()
{
	
  int j,*p;
  j=f1();
  p=&f1();// p=f1() not acceptable
  cout<<endl<<"j:"<<j<<endl<<"p:"<<p<<endl;
}
