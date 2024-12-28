#include <stdio.h>
#include<iostream>
using namespace std;
//////////////////////////////
class Base
{
	public:
		virtual void show()   // virtal function
		{
			cout<<"Base\n";
		}
};
/*
If virtual function is there, the compiler selects the function according to the contents of the pointer
and not on the type of the pointer as was the case with normal function
here we can skip the body of the definition of the ovreridden function in the derived class
*/
class Derv1:public Base    // derived class 1
{
	public:
		void show()
		{
			cout<<"Derived Class 1\n";
		}
};
class Derv2:public Base    // derived class 2
{
	public:
		void show()
		{
			cout<<"Derived Class 2\n";
		}
};

int main()
{
	Derv1 dv1;
	Derv2 dv2;
	Base* ptr;

	ptr=&dv1;
	ptr->show();

	ptr=&dv2;
	ptr->show();

	return 0;
}
