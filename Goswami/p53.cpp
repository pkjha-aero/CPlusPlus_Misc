// Class template
#include<iostream>
using namespace std;

template<class T,int size>
class datastack
{
  T arr[size];
  int top;
public:
  datastack(){top=0;}
  void push(const T &element)
  {
    if(top>=size)
      cout<<"stack is full\n";
    else
    {
      arr[top]=element;
      top++;
    }
  }
  T pop()
  {
    top--;
    return arr[top];
  }
};

main()
{
  datastack<int,20> stack_int;
  datastack<float,20> stack_float;
  
  stack_int.push(4);
  stack_int.push(8);
  // Execution happens from right, so the rightmost pop() yields 8 and leftmsot 4
  // When printed this gives 4 and 8
  //cout<<stack_int.pop()<<endl<<stack_int.pop()<<endl;
  cout<<stack_int.pop()<<endl;
  cout<<stack_int.pop()<<endl;
  
  stack_float.push(5.67);
  stack_float.push(9.43);
  cout<<stack_float.pop()<<endl<<stack_float.pop()<<endl;
}
