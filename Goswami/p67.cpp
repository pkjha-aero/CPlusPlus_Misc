#include<iostream.h>
#include<strstream.h>

main()
{
  char s[]="text and binary mixed\23\22\21\a\t\n";
  char ch;
  istrstream ins(s);
  while(!ins.eof())
    {
      ins.get(ch);
      cout<<ch;
    }
}
