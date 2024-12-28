#include<iostream.h>
#include<strstream.h>

main()
{
  char s[]="One 2 3.55";
  istrstream ins(s);
  int i;
  float f;
  char str[80];
  ins>>str;
  ins>>i;
  ins>>f;
  cout<<str<<f<<i<<endl;
}
