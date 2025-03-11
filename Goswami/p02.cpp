// Class
#include <iostream>
using namespace std;

class queue
{
  int q[100];
  int rloc,sloc;
public:
  void init();
  void qput(int i);
  int qget();
};

void queue::init()
{
  rloc=sloc=0;
}

void queue::qput(int i)
{
  if(sloc==100)
    {
      cout<<"Queue is full \n";
      return;
    }
  sloc++;
  q[sloc]=i;
  cout<< "Added " << i << " to the queue at the location " << sloc << "\n";
}

int queue::qget()
{
  if(rloc==sloc)
    {
      cout<<"Queue UnderFlow \n";
      return 0;
    }
  rloc++;
  cout<< "Returning " << q[rloc] << " from the queue at the location " << rloc << "\n";
  return q[rloc];
}

main()
{
  queue a,b;
  a.init();
  b.init();
  a.qput(10);
  b.qput(19);
  a.qput(20);
  b.qput(1);
  /*
  cout<<a.qget()<<",";
  cout<<a.qget()<<",";
  cout<<b.qget()<<",";
  cout<<b.qget()<<"\n";
  */
}
