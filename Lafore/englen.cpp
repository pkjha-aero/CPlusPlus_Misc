#include <stdio.h>
#include<iostream>
using namespace std;
enum posneg {pos,neg};
/////////////////////////////////////////////////////////

class Distance
{
	protected:
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
};

class DistSign : public Distance
{
	private:
		posneg sign;
	public:
		DistSign() : Distance()
		{
			sign=pos;
		}
		DistSign(int ft,float in,posneg sg=pos) : Distance(ft,in)  // without sg=pos.....compilation error
		{
			sign=sg;
		}
		void getdist()
		{
			Distance::getdist();
			char ch;
			cout<<"Enter sign (+ or -) : ";
			cin>>ch;
			sign=(ch=='+')?pos:neg;
		}
		void showdist() const
		{
			cout<<((sign==pos)?"(+)":"(-)");
			Distance::showdist();
		}

};

int main()
{
	DistSign alpha;
	alpha.getdist();

	DistSign beta(11,6.25);

	DistSign gamma(100,5.5,neg);

	cout<<"alpha = ";alpha.showdist(); cout<<endl;
    cout<<"beta = ";beta.showdist(); cout<<endl;
	cout<<"gamma = ";gamma.showdist(); cout<<endl;

	return 0;
}
