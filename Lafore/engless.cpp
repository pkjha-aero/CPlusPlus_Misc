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
		bool operator<(Distance d2) const;
};

bool Distance::operator<(Distance d2) const
{
	float bf1=feet+inches/12;
	float bf2=d2.feet+d2.inches/12;
	return(bf1<bf2)?true:false;
}

int main()
{
	Distance dist1;
	dist1.getdist();

	Distance dist2(11,6.25);

	cout<<"dist1 = ";dist1.showdist(); cout<<endl;
    cout<<"dist2 = ";dist2.showdist(); cout<<endl;

	if(dist1<dist2)
		cout<<"\n dist1 is less than dist2"<<endl;
	else
		cout<<"\n dist1 is greater than or equal to dist2"<<endl;

	return 0;
}
