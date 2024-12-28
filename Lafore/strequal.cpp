#include <stdio.h>
#include<iostream>
using namespace std;
#include<string.h>

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
		void getstr()
		{
			cin.get(str,SZ);
		}
		bool operator==(String ss) const
		{
			return (strcmp(str,ss.str)==0)?true:false;		
		}
};

int main()
{
	String s1="yes";
	String s2="no";
	String s3;

	cout<<"\nEnter 'yes' or 'no' :";
	s3.getstr();

	s1.display();
	s2.display();
	s3.display();

	if(s3==s1)
		cout<<"\nYou typed 'yes'"<<endl;
	else if(s3==s2)
		cout<<"\nYou typed 'no'"<<endl;
	else
		cout<<"\nYou didn't follow instructions"<<endl;

	return 0;
}