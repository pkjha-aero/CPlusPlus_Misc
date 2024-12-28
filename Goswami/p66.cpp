#include<iostream.h>
#include<strstream.h>

main()
{
  char s[]="One 2 3.55";
  istrstream ins(s);
  char ch;
  while(ins)
    {
      ins>>ch;
      cout<<ch;
    }
}
