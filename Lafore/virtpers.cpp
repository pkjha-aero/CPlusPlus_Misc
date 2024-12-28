//virtual functions with person class
#include <stdio.h>
#include<iostream>
#define MAX 40
using namespace std;
///////////////////////////////////////////
class person
{
	private:   // no need of protected as not used in derived class
		char name[MAX];
	public:
		void getName()
		{
			cout<<"Enter Name: ";
			cin>>name;   // there was some problem with cin.get(name,MAX)
		}
		void putName()
		{
			cout<<"Name is: "<<name<<endl;
		}
		virtual void getData()=0;             // pure virtual function
		virtual bool isOutstanding()=0;
};
//////////////////////////////////////////////
class student:public person
{
	private:
		float gpa;
	public:
		void getData()
		{
			person::getName();
			cout<<"Enter Student's GPA: ";
			cin>>gpa;
		}
		bool isOutstanding()
		{
			return (gpa>3.5)?true:false;
		}
};
//////////////////////////////////////////////
class professor:public person
{
	private:
		int numPubs;
	public:
		void getData()
		{
			person::getName();
			cout<<"Enter number of Professor's Publications: ";
			cin>>numPubs;
		}
		bool isOutstanding()
		{
			return (numPubs>100)?true:false;
		}
};
/////////////////////////////////////////////
int main()
{
	person *persPtr[100];
	int n=0;
	char choice;
	
	do
	{
		cout<<"Enter student or professor (s/p): ";
		cin>>choice;
		if(choice=='s')
			persPtr[n]=new student;
		else
			persPtr[n]=new professor;
		persPtr[n++]->getData();
		cout<<"Enter another (y/n)? ";
		cin>>choice;
	}
	while (choice=='y');

	for (int j=0;j<n;j++ )
	{
		persPtr[j]->putName();
		if(persPtr[j]->isOutstanding())
			cout<<"This person is outstanding\n";
	}

	return 0;
}
