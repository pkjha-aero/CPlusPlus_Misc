#include <stdio.h>
#include<iostream>
using namespace std;

class counter
{
	protected:
		unsigned int count;
	public:
		counter():count(0)
		{
		}
		counter(int c):count(c)
		{
		}
	    unsigned int get_count() const
		{
			return count;
		}
		counter operator++()
		{
			return counter(++count);
		}
};

class countDn : public counter
{
	public:
		countDn():counter()
		{
		   cout<<"\nAdditional features in the derived class no arg constructor";
		}
		countDn(int c):counter(c)
		{
			cout<<"\nAdditional features in the derived class one arg constructor";
		}
		countDn operator--()
		{
			return countDn(--count);
		}
};
/////////////////////////////////////////////////
int main()
{
	countDn c1;
	countDn c2(100);
	cout<<"\nc1:"<<c1.get_count()<<endl;   //display
	cout<<"\nc2:"<<c2.get_count()<<endl;

	++c1;
	++c1;
	++c1;

	cout<<"\nc1:"<<c1.get_count()<<endl;   //display

    --c2;
	--c2;
	cout<<"\nc2:"<<c2.get_count()<<endl;

	countDn c3=--c2;
	cout<<"\nc3:"<<c3.get_count()<<endl;

	
	return 0;
}
