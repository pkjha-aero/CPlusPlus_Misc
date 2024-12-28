#include <stdio.h>
#include<iostream>
using namespace std;

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
		void getdist()
		{
			cout<<"\nEnter feet: ";
			cin>>feet;
			cout<<"\nEnter Inches: ";
			cin>>inches;
		}
		void showdist() const // made constant so that it can't modify any variable
	    {
			cout<<feet<<"\'-"<<inches<<'\"';
		}
		void operator+=(Distance d2);  // this can't be constant..i committed a mistake earlier
};

void Distance::operator+=(Distance d2)
{
	feet+=d2.feet;
	inches+=d2.inches;
	if(inches>=12.0)
	{
		inches-=12.0;
		feet++;
	}
}

int main()
{
	Distance dist1;
	dist1.getdist();

	Distance dist2(11,6.25);

	cout<<"dist1 = ";dist1.showdist(); cout<<endl;
    cout<<"dist2 = ";dist2.showdist(); cout<<endl;

	dist1+=dist2;
	cout<<"\nAfter addition:\n";
	cout<<"\ndist1= ";
	dist1.showdist();
	cout<<endl;

	return 0;
}
