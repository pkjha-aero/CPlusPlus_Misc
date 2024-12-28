#include <stdio.h>
#include<iostream>
using namespace std;

class counter
{
	private:
		unsigned int count;
	public:
		counter():count(0)
		{
		}
		counter(int c):count(c)
		{
		}
	    unsigned int get_count()
		{
			return count;
		}
		counter operator++()
		{
			return counter(++count);
		}
        counter operator++(int)
		{
			return counter(count++);
		}
};
/////////////////////////////////////////////////
int main()
{
	counter c1,c2;
	cout<<"\nc1:"<<c1.get_count();   //display
	cout<<"\nc2:"<<c2.get_count();

	++c1;
	c2=++c1;

	cout<<"\nc1:"<<c1.get_count();   //display
	cout<<"\nc2:"<<c2.get_count()<<endl;

    c2=c1++;                   //postfix form
    cout<<"\nc1:"<<c1.get_count();   //display
	cout<<"\nc2:"<<c2.get_count()<<endl;
}
