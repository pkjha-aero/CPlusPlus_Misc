#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>

main(int argc,char *argv[])
{
  if(argc!=3)
    {
      cout<<"\nUsage:Change File_name byte\n";
      return 1;
    }
  fstream out(argv[1],ios::in|ios::out);
  if(!out)
    {
      cout<<"Cannot open the file:"<<endl;
      return 1;
    }
  out.seekp(atoi(argv[2]),ios::beg);
  out.put('#');
  out.close();
}
