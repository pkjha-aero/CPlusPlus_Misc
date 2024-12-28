#include <stdio.h>
#include<iostream>
using namespace std;
//////////////////////////////
class Base
{
	public:
		virtual void show()=0;   // pure virtal function..no need of any body...however there is no harm if defined

};
/*
If virtual function is there, the compiler selects the function according to the contents of the pointer
and not on the type of the pointer as was the case with normal function
here we can skip the body of the definition of the ovreridden function in the derived class
but if pure virual function is there we must override it in all the derived classes..otherwise that class will
become abstract.....we can't instantiate a class having a pure virtual function..however a pointer can be
declared.
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
	//Base bad;
	Base* arr[2];
	Derv1 dv1;
	Derv2 dv2;

	arr[0]=&dv1;
	arr[0]->show();

	arr[1]=&dv2;
	arr[1]->show();

	return 0;
}
