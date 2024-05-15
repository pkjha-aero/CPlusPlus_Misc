//OVERLOADING + & = FOR String

#include<iostream>
#include<string.h>
using namespace std;

class String
{
  char str[80];
public:
  String(char str1[]="\0") // constructor
  {
    strcpy(str,str1);
  }
  String operator+(String ob1);
  String operator=(String ob2);
  void show();
};

String String::operator+(String ob1)
{
  String temp;
  strcpy(temp.str,str);
  strcat(temp.str,ob1.str);
  return temp;
}

String String::operator=(String ob2)
{
  strcpy(str,ob2.str);
  return *this;
}

void String::show()
{
  cout<<str<<"\n";
}
main()
{
  String a("Hello"),b("there"),c,d(" ");
  c=a+d+b;
  c.show();
}
