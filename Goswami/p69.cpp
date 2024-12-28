#include<strstream.h>
#include<iostream.h>

main()
{
  char *p;
  ostrstream outs;
  outs<<"I like C++";
  outs<<-10;
  outs<<100;
  p=outs.str();
  cout<<p;
  delete p;
}
