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
		void showdist() 
	    {
			cout<<feet<<"\'-"<<inches<<'\"';
		}
		friend float square(Distance);
};

float square(Distance d)
{
	float fltfeet=d.feet+d.inches/12;
	float feetsqrd=fltfeet*fltfeet;
	return feetsqrd;
}
/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Distance dist(3,6.0);
	float sqft;
	
	sqft=square(dist);
	
	cout<<"\nDistance=";dist.showdist();
	cout<<"\nSquare="<<sqft<<" square feet"<<endl;
	
	return 0;
}
