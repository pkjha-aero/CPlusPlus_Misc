#include<iostream.h>
#include<fstream.h>

main(int argc,char *argv[])
{
  char ch;
  if(argc!=3)
    {
      cout<<"Bad command or file name\n";
      return 1;
    }
  ifstream in(argv[1]);  //argv[1] contains the file name to be opened
  if(!in)              //read mode
    {
      cout<<"Cannot open the  source file\n";
      return 1;
    }
  ofstream out(argv[2]);
  if(!out)              //read mode
    {
      cout<<"Cannot open the destination file\n";
      return 1;
    }
	
  while(in.get(ch))   //while file is open
    out.put(ch);
  in.close();  //close the file after readingg
  out.close();
}               
