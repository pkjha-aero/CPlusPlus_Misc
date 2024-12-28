// Constructors and Destructors
// Tips: A destructor is not required explicitly
#include<iostream>
using namespace std;

class queue
{
  int q[100],rloc,sloc;
public:
  queue();           // A Constructor
  queue(int a,int b);  //Constructor Overloading
  void qput(int num);
  int qget();
  ~queue();          //Destructor
};

queue::queue()
{
  rloc=sloc=0;
  cout<<"Queue Initialisation without any argument\n";
}
queue::queue(int a,int b)
{
  rloc=a;
  sloc=b;
  cout<<"Queue Initialisation with two arguments\n";
}

queue::~queue()
{
  cout<<"Queue Destroyed \n";
}

void queue::qput(int num)
{
  if(sloc==100)
    {
      cout<<"Queue is full\n";
      return;
    }
  sloc++;
  q[sloc]=num;
}

int queue::qget()
{
  if(rloc==sloc)
    {
      cout<<"Queue UnderFlow \n";
	return 0;
    }
  rloc++;
  return q[rloc];
}

main()
{
  queue a,b(4,4);
  a.qput(10);
  a.qput(20);
  b.qput(30);
  b.qput(40);
  cout<<a.qget()<<",";
  cout<<a.qget()<<",";
  cout<<b.qget()<<",";
  cout<<b.qget()<<",\n";
  a.qget();
}
