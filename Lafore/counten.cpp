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
		counter operator--()
		{
			return counter(--count);
		}
};
/////////////////////////////////////////////////
int main()
{
	countDn c1;
	cout<<"\nc1:"<<c1.get_count()<<endl;   //display

	++c1;
	++c1;
	++c1;

	cout<<"\nc1:"<<c1.get_count()<<endl;   //display

    --c1;
	--c1;
	cout<<"\nc1:"<<c1.get_count()<<endl;
	
	return 0;
}
