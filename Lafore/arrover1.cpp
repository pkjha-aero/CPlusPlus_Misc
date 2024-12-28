#include <stdio.h>
#include<iostream>
using namespace std;
#include<process.h>
const int LIMIT=100;
class safearray
{
	private:
		int arr[LIMIT];
	public:
		void putel(int n,int evalue)
		{
		    if(n<0 || n>=LIMIT)
			{
				cout<<"\n Index out of Bounds";
				exit(1);
			}
			arr[n]=evalue;
		}
		int getel(int n) const
		{
			if(n<0 || n>=LIMIT)
			{
				cout<<"\n Index out of Bounds";
				exit(1);
			}
			return arr[n];
		}
};
int main()
{	
	safearray sa;
	int j;
	for(j=0;j<LIMIT;j++)
		sa.putel(j,j*10);
	for(j=0;j<LIMIT;j++)
	{ 
		int temp=sa.getel(j);
		cout<<"Element "<<j<<" is "<<temp<<endl;
	}
	return 0;
}
