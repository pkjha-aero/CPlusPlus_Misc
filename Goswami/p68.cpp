#include<iostream.h>
#include<strstream.h>

main()
{
  char iostr[80];
  strstream ioss(iostr,sizeof(iostr),ios::in|ios::out);
  int a,b;
  char str[80];
  ioss<<"my name is pankaj jha";
  ioss>>str;
  cout<<str;
  ioss>>str;
  cout<<str;
  ioss>>str;
  cout<<str;
}
