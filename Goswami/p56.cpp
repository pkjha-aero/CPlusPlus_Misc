#include<iostream.h>
#include<fstream.h>

main()
{
  ofstream out("test");//mode & access default,ios::noreplace causes
                       //cannot open the file
  if(!out) //even with filename dat, ouput is same as that with test
    {
      cout<<"Cannot open the file\n";
      return 1;
    }
  out<<10<<" "<<123.23<<'\n'; //" " is skipped,no need to worry
  out<<"This_is_a_short_text_file\n";
  out.close();         // file closed after writing into it
  
  //if we want to read the same file in which we have written
  //we have to open that file in read mode

  ifstream in("test");     //here also mode & access are default
  char ch;             // file can be read only thru variables
  int i;               // declared in the main
  float f;
  char str[80];
  in>>i;
  in>>f;
  in>>ch;
  in>>str;
  in.close(); //doesn't matter whether we close bef or aft printing

  cout<<i<<" "<<f<<" "<<ch<<str<<endl;
  //in.close();//we shud always close the file,closed after printing
}
