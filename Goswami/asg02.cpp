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
  friend string operator+(string ob1,string ob2);
  friend string operator+(string ob,char s[]);
  friend string operator+(char s[],string ob);
  friend void operator==(string ob1,string ob2);  
  friend void operator==(string ob,char s[]);
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
string operator+(string ob1,string ob2)
{
  string temp;
  strcpy(temp.str,ob1.str);
  strcat(temp.str,ob2.str);
  temp.fl=ob1.fl+ob2.fl;
  temp.in=ob1.in+ob2.in;
  return temp;
}
string operator+(string ob,char s[])
{
  string temp;
  strcpy(temp.str,ob.str);
  strcat(temp.str,s);
  temp.fl=ob.fl;
  temp.in=ob.in;
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
void operator==(string ob1,string ob2)
{
  int p;
  if(strcpy(ob1.str,ob2.str)==0)
    p=0;
  else
    p=1;
  if(ob1.fl==ob2.fl)
    p=0;
  else
    p=1;
  if(ob1.in==ob2.in)
    p=0;
  else
    p=1;
  if(p==0)
    cout<<"The two objects are equal\n";
  else
    cout<<"The two objects are not equal\n"; 
}

void operator==(string ob,char s[])
{
  if(strcmp(ob.str,s)==0)
    cout<<"The character array & the array of the object are same\n";
  else
    cout<<"The character arrayof the array of the object are different\n";
}
void operator==(char s[],string ob)
{
  if(strcmp(s,ob.str)==0)
    cout<<"The character array & the array of the object are same\n";
  else
    cout<<"The character array & the array of the object are different\n";
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
  string a("In object a->",23.5,34),b("In object b->",56.7,13),c,d("Back in a",4.5,7);
  a.display();
  b.display();
  c.display();
  c=a+b;       // demo of adding object to object
  c.display();
  a=a+" It's fun"; //demo of adding array to object
  a.display();
  b="Nice Programming "+b; // demo of adding object to array
  b.display();
  c=b;
  b==c;     //demo of comparing two objects
  a==b;
  d=="Back in a";//demo of comparing array of an object with another array
  d=="xyz";
  "Back in a"==d;//demo of comparing an array with array of an object
  "xyz"==d;
  a.tokenise(' ');
  b.tokenise(' ');
  c.tokenise(' ');
}
