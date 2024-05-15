#include<strstream.h>
#include<iostream.h>

main()
{
  char str[80];
  int a=10;
  ostrstream outs(str,sizeof(str));
  outs<<"Hello"<<123.23;
  outs<<a+44<<" ";
  outs.setf(ios::showbase);
  outs<<100<<ends;
  cout<<str;
}
