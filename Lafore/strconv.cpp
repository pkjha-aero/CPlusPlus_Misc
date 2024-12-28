#include <stdio.h>
#include<iostream>
using namespace std;
#include<string.h>
#include<stdlib.h>

class String
{
	private:
		enum {SZ=80};
	    char str[SZ];
	public:
		String()
		{
		   strcpy(str,"");
		}
		String(char s[])
		{
		   strcpy(str,s);
		}
		void display() const
	    {
			cout<<str<<endl;
		}
	    operator char*()
		{
			return str;
		}
};

int main()
{
	String s1;
	char xstr[]="Joyeux Noell ";
	s1=xstr;
	s1.display();

	String s2="Bonne Anne ";
	cout<<static_cast<char*>(s2)<<endl;

	return 0;
}