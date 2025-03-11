//OVERLOADING + & = FOR String
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
  //String operator+(String ob1);  // we don't need even this
  //String operator+(char *str1);   // no need
  friend String operator+(String t,String s);
  String operator=(String ob2);
 // String operator=(char *str2);   // no need
  void show();
};

// String String::operator+(String ob1)
// {
  // String temp;
  // strcpy(temp.str,str);
  // strcat(temp.str,ob1.str);
  // return temp;
// }
// String String::operator+(char *str1)
// {
  // String temp;
  // strcpy(temp.str,str);
  // strcat(temp.str,str1);
  // return temp;
// }

String operator+(String t,String s)
{
  String temp;
  strcpy(temp.str,t.str);
  strcat(temp.str,s.str);
  return temp;
}

String String::operator=(String ob2)
{
  strcpy(str,ob2.str);
  return *this;
}
// String String::operator=(char *str2)
// {
  // strcpy(str,str2);
  // return *this;
// }

void String::show()
{
  cout<<str<<"\n";
}
main()
{
  String a("Hello"),b("There"),c,d(" ");
  c=a+d+b;
  c.show();
  c=c + d + "How are you?";
  c.show();
  c=c + d + "What is your name?";
  c.show();
  b="It's fun";
  b.show();
  b="It's ok "+b; //not acceptable without friend function
  b.show();
}
