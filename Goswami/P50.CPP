//FUNCTION TEMPLATE
#include<iostream>
using namespace std;

template<class T>
void print(T data)
{
  cout<<data<<endl;
}
template<class T>
void print(T data,int times)
{
  for(int i=0;i<times;i++)
    cout<<data<<" ";
  cout<<endl;
}

main()
{
  print(2);
  print(5.8);
  print(850,2);
  print("Hello",3);
  print('#',10);
}
