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
		String operator+(String ss) const
		{
			String temp;
			if(strlen(str)+strlen(ss.str)<SZ)
			{
				strcpy(temp.str,str);
				strcat(temp.str,ss.str);
				//return String(strcat(str,ss.str)); // this doesn't work
			}
			else
			{
				cout<<"\n String Overflow";
				exit(1);
			}
			return temp;
		}
};

int main()
{
	String s1="\nMerry Christmas! ";
	String s2="happy New Year!";
	String s3;

	s1.display();
	s2.display();
	s3.display();

	s3=s1+s2;
	s3.display();

	return 0;
}
