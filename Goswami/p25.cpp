//OVERLOADING + & = FOR String
//NO NEED OF FRIEND FUNCTION
//wherever char *str is there we can write char[]

#include<iostream>
#include<string.h>
using namespace std;

class String
{
  char str[80];
public:
  String(char *str1="\0") // constructor
  {
    strcpy(str,str1);
  }
  String operator+(String ob1);
  //String operator+(char *str1);         //there is no need of this function 
  String operator=(String ob2);
  //String operator=(char *str2);
  void show();
};

String String::operator+(String ob1)
{
  String temp;
  strcpy(temp.str,str);
  strcat(temp.str,ob1.str);
  return temp;
}
/*
String String::operator+(char *str1)
{
  String temp;
  strcpy(temp.str,str);
  strcat(temp.str,str1);
  return temp;
}
*/
String String::operator=(String ob2)
{
  strcpy(str,ob2.str);
  return *this;
}
/*
String String::operator=(char *str2)
{
  strcpy(str,str2);
  return *this;
}
*/
void String::show()
{
  cout<<str<<"\n";
}
main()
{
  String a("Hello"),b("There"),c,d(" ");
  c=a+d+b;
  c.show();
  c=c+d+"How are you?";
  c.show();
  c=c+" What is your name?";
  c.show();
  b="It's fun";
  b.show();
  // b=" I "+b; //not acceptable, to do so we need friend function
}
