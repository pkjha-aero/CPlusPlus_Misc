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
class foremen : public laborer
{
	private:
		float quotas;
	public:
		void getdata()
		{
		laborer::getdata();
		cout<<"\nEnter Quotas: ";
		cin>>quotas;
		}
		void putdata() const
		{
			laborer::putdata();
			cout<<"\nQuotas: "<<quotas;
		}
};
//////////////////////////////////////////////
int main()
{
	laborer l1;
	foremen f1;
	cout<<"\nEnter data for laborer 1 : ";
	l1.getdata();

	cout<<"\nEnter data for foreman 1 : ";
	f1.getdata();

	cout<<"\nData ob laborer 1: ";
	l1.putdata();

	cout<<"\nData ob foreman 1: ";
	f1.putdata();

	return 0;
}
