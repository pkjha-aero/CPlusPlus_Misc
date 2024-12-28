#include <stdio.h>
#include<iostream>
using namespace std;

class Base
{
	public:
		//~Base()
		virtual ~Base()
		{
			cout<<"Base Destroyed\n";
		}
};
//////////////////////////////////////
class Derv : public Base
{
	public:
		~Derv()
		{
			cout<<"Derv Destroyed\n";
		}
};
//////////////////////////////////////
int main()
{
	Base *baseptr=new Derv;
	delete baseptr;
	return 0;
}
