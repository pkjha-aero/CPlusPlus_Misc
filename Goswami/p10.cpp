// Constructor overloading
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class timer
{
  int seconds;
public:
  timer(char *t){seconds=atoi(t);} //Constructor
  timer(int t){seconds=t;} //Overloaded Constructor
  timer(int min,int sec){seconds=min*60+sec;}
  void run();
};

void timer::run()
{
  clock_t t1,t2;  //returns the no of clock tick aft start of prog
  t1=t2=clock()/CLK_TCK;//return the clock ticks in seconds
  while(seconds)
    {
      if(t1/CLK_TCK+1<=(t2=clock())/CLK_TCK)
	{
	  seconds--;
	  t1=t2;
	  cout<<".";
	}
    }
  cout<<"\a\n";
}

main()
{
  timer a(20),b("20"),c(1,10);//if we write timer d,then error
  a.run();
  b.run();
  c.run();
}
