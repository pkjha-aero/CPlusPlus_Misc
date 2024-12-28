// Class template
#include<iostream>
using namespace std;

template<class T>
class vector
{
  T *v;
  int size;
public:
  vector(int v_size){size=v_size;v=new T[size];}
  ~vector(){delete v;}
  void putelem()
  {
    for(int i=0;i<size;i++)
      v[i]=10*i;
  }
  T &elem(int i)
  {
    if(i>=size)
      cout<<"Out of Range\n";
    return v[i];
  }
  void show();
};

template<class T>
void vector<T>::show()
{
  for(int i=0;i<size;i++)
    cout<<elem(i)<<",";
}

main()
{
  int i;
  vector<int> int_vector(11);
  int_vector.putelem();
  int_vector.show();
  cout<<endl;
}
