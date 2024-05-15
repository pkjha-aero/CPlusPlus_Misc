// PANKAJ KUMAR JHA
// 01 MA 2011
// ASSIGNMENT 2

#include<iostream.h>
#include<string.h>

class string
{
private:
  char str[80];
  float fl;
  int in;
public:
  string();
  string(char s[],float f,int i);
  string operator+(string ob);
  string operator+(char s[]);
  friend string operator+(char s[],string ob);  
  string operator=(string ob);
  string operator=(char s[]);
  void operator==(char s[]);
  friend void operator==(char s[],string ob);
  void display();
  void tokenise(char c);
  ~string();
};
string::string()
{
  char s[]="\0";
  strcpy(str,s);
  fl=0;
  in=0;
}
string::string(char s[],float f,int i)
{
  strcpy(str,s);
  fl=f;
  in=i;
}
string::~string()
{
  cout<<"String Destroyed\n";
}
string string::operator+(string ob)
{
  string temp;
  strcpy(temp.str,str);
  strcat(temp.str,ob.str);
  temp.fl=fl+ob.fl;
  temp.in=in+ob.in;
  return temp;
}
string string::operator+(char s[])
{
  string temp;
  strcpy(temp.str,str);
  strcat(temp.str,s);
  temp.fl=fl;
  temp.in=in;
  return temp;
}
string operator+(char s[],string ob)
{
  string temp;
  strcpy(temp.str,s);
  strcat(temp.str,ob.str);
  temp.fl=ob.fl;
  temp.in=ob.in;
  return temp;
}

string string::operator=(string ob)
{
  strcpy(str,ob.str);
  fl=ob.fl;
  in=ob.in;
  return *this;
}
string string::operator=(char s[])
{
  strcpy(str,s);
  return *this;
}

void string::operator==(char s[])
{
  if(strcmp(str,s)==0)
    cout<<"The character arrays of the two objets are same\n";
  else
    cout<<"The character arrays of the two objects are different\n";
}
void operator==(char s[],string ob)
{
  if(strcmp(s,ob.str)==0)
    cout<<"The character arrays of the two objets are same\n";
  else
    cout<<"The character arrays of the two objects are different\n";
}
void string::display()
{
  cout<<"Character Array: "<<str<<" Floating Value:"<<fl<<" Integer Value:"<<in<<"\n";
}
void string::tokenise(char c)
{
  cout<<"TOKENISATION\n";
  int i=0;
  while(str[i]!='\0')
    {
      if(str[i]!=c)
	cout<<str[i];
      else
	cout<<"\n";
      i++;
    }
  cout<<"\n";
}

main()
{
  string a("In object a->",23.5,34),b("In object b->",56.7,13),c;
  a.display();
  b.display();
  c.display();
  c=a+b;       // demo of adding & assigning object to object
  c.display();
  a=a+" It's fun"; //demo of adding array to object
  a.display();
  b="In new b->";  //assigning array to object
  b.display();
  b="Nice Programming "+b; // demo of adding object to array
  b.display();
  c=b;
  // b==c;     //demo of comparing two objects
  //a==b;
  a="Back in a";
  a=="Back in a";//demo of comparing array of an object with another array
  a=="xyz";
  "Back in a"==a;//demo of comparing an array with array of an object
  "xyz"==a;
  a.tokenise(' ');
  b.tokenise(' ');
  c.tokenise(' ');
}
