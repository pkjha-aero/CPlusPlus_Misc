// Default function argument
// Tips: Default func args can only be from the right
// char * is deprecated
#include<iostream>
#include<conio.h>
#include<cstring>
using namespace std;

//void xyout(char *str,int x=-1,int y=-1); // char * is deprecated
void xyout(std::string str,int x=-1,int y=-1);

main()
{
  xyout("Hello",10,10);
  xyout("There");
  xyout("I Like",40);
}

//void xyout(char *str,int x,int y)
void xyout(std::string str,int x,int y)
{
  cout<<str<<", x= "<<x<<", y= "<<y<<endl;
}
