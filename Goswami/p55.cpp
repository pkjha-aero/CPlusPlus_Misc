// Class template
#include<iostream>
using namespace std;

template<class T>
class complex
{
  T real;
  T imag;
public:
  complex(){real=imag=0;}
  void getdata()
  {
    cout<<"Enter the data: ";
    cin>>real>>imag;
  }
  complex operator+(complex c);
  void outdata()
  {
    cout<<real<<" + "<<imag<<" i"<<endl;
  }
};
template<class T>
complex<T> complex<T>::operator+(complex<T> c)
 {
    complex<T> temp;
    temp.real=real+c.real;
    temp.imag=imag+c.imag;
    return temp;
  }
main()
{
  complex<int> c1,c2,c3;
  c1.getdata();
  c1.outdata();
  c2.getdata();
  c2.outdata();
  c3=c1+c2;
  c3.outdata();
  complex<float> c4,c5,c6;
  c4.getdata();
  c4.outdata();
  c5.getdata();
  c5.outdata();
  c6=c4+c5;
  c6.outdata();
}
