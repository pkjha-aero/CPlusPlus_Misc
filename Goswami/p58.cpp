#include<iostream.h>
#include<fstream.h>

main()
{
  char n[5]={'p','r','s','x','a'};
  int i;
  ofstream out("test");
  out.write((unsigned char *)&n,sizeof(n));
  out.close(); // writing in test whatever is there in n[5],close

  for(i=0;i<5;i++)
    n[i]=0; //the values read from test are stored in n[5]
  ifstream in("test");
  in.read((unsigned char *)&n,sizeof(n));
  in.close();
  for(i=0;i<5;i++)
    cout<<n[i]<<" ";
  cout<<endl;
}
