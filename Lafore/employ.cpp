#include <stdio.h>
#include<iostream>
using namespace std;
const int LEN=80;   // maximum length of names
/////////////////////////////////////////////////
class employee
{
	private:
		char name[LEN];
		unsigned long number;
	public:
		void getdata()
		{
			cout<<"\nEnter last name: ";
			cin>>name;
			cout<<"\nEnter number : ";
			cin>>number;
		}
		void putdata() const
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Number: "<<number;
		}
};
////////////////////////////////////////////////
class manager : public employee
{
	private:
		char title[LEN];
		double dues;
	public:
		void getdata()
		{
			employee::getdata();
			cout<<"\nEnter title : ";
			cin>>title;
			cout<<"\nEnter golf club dues : ";
			cin>>dues;
		}
		void putdata() const
		{
			employee::putdata();
			cout<<"\n Title: "<<title;
			cout<<"\n Golf Club Dues : "<<dues;
		}
};
////////////////////////////////////////////////
class scientist : public employee
{
	private:
		int pubs;
	public:
		void getdata()
		{
			employee::getdata();
			cout<<"\nEnter the number of pubs : ";
			cin>>pubs;
		}
		void putdata() const
		{
			employee::putdata();
			cout<<"\n Number of publications: "<<pubs;
		}
};
///////////////////////////////////////////////
class laborer : public employee
{
};
//////////////////////////////////////////////
int main()
{
	manager m1,m2;
	scientist s1;
	laborer l1;
	cout<<"\nEnter data for manager 1 : ";
	m1.getdata();

	cout<<"\nEnter data for manager 2 : ";
	m2.getdata();

	cout<<"\nEnter data for scientist 1 : ";
	s1.getdata();

	cout<<"\nEnter data for laborer 1 : ";
	l1.getdata();

	cout<<"\nData ob manager 1: ";
	m1.putdata();

	cout<<"\nData ob manager 2: ";
	m2.putdata();

	cout<<"\nData ob scientist 1: ";
	s1.putdata();

	cout<<"\nData ob laborer 1: ";
	l1.putdata();

	return 0;
}
