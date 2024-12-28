// overloaded + operator
#include <stdio.h>
#include<iostream>
using namespace std;
////////////////////////////////////////
class Distance
{
	private:
		int feet;
	    float inches;
	public:
		Distance():feet(0),inches(0.0)
		{
		}
		Distance(int ft,float in):feet(ft),inches(in)
		{
		}
		Distance(float fltfeet)
		{
			feet=static_cast<int>(fltfeet);
			inches=12*(fltfeet-feet);
		}
		void showdist() 
	    {
			cout<<feet<<"\'-"<<inches<<'\"';
		}
		friend Distance operator+(Distance d1,Distance d2);
};

Distance Distance::operator+(Distance d1,Distance d2)
{
	int f=d1.feet+d2.feet;
	float i=d1.inches+d2.inches;
	if(i>=12.0)
	{
		i-=12.0;
		f++;
	}
	return Distance(f,i);
}
/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Distance d1=2.5;
	Distance d2=1.25;
	Distance d3;
	
	cout<<"\nd1=";d1.showdist();
	cout<<"\nd2=";d2.showdist();
	
	d3=d1+10.0;
	cout<<"\nd3=";d3.showdist();
	
	d3=10.0+d1;
	cout<<"\nd3=";d3.showdist();

	cout<<endl;
	
	return 0;
}
