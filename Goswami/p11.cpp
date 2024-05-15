// Protected vs Private
// Tips: Protected members can be accessed in the immediately derived class 
//       as well as the subsequent ones
#include<iostream>
using namespace std;

class X
{
	protected:
		int i,j;
	public:
		int get_ij()
		{
			return i*j;
		}
		void make_ij(int a,int b)
		{
			i=a;
			j=b;
		}
};
///////////////////////////////////
class Y: public X
{
	    int k;
	public:
		int get_k()
		{
			return k;
		}
		void make_k()
		{
			k=i*j;
		}
};
////////////////////////////////////////
class Z:public Y
{
	public:
		void f()
		{
			cout<<"i= "<<i<<" j= "<<j<<" k= "<<get_k()<<endl;
		}
};
////////////////////////
int main()
{
	Z obj;
	obj.make_ij(5,6);
	obj.make_k();
	
	obj.f();
	
	return 0;
}
