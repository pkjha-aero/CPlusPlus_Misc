/*********************************************************
PANKAJ KUMAR JHA
01 MA 2011
ASSIGNMENT 4
**********************************************************/
#include<iostream.h>
using namespace std;

template<class T>
class node
{
public:
  T data;
  node *prev;     //poiter to its previous node
  node *next;     //poiter to its next node
};

template<class T>
class dll         //the class doubly linked list
{
private:
  node<T> *first;    //pointer to the first node of the dll
public:
  dll()           //constructor without argument
  {
    first=NULL;
  }
  ~dll()          //Destructor
  {
    cout<<"Destructing\n";
  }
  void addatend(); //function to add a data at the end of the dll
  void addatbeg(); //function to add a data at the beginning of the dll
  void addatloc(); //to add a data at specified location
  void del();      //function to delete a specified data
  void display();  //function to display the current list
};

template<class T>
void dll<T>::addatend()
{
  T num;
  node<T> *newnode,*p;
  p=first;
  cout<<"\nEnter the data to be inserted at the end: ";
  cin>>num;
  cout<<"The data to be inserted is :"<<num;
  if(first==NULL)      //if the dll is empty
    {
      first=new node<T>;  //allocate space for the new node
      first->prev=NULL;
      first->data=num;
      first->next=NULL;
    }
  else
    {
      while(p->next!=NULL)
	p=p->next;
      newnode=new node<T>;
      newnode->data=num;
      newnode->next=NULL;
      newnode->prev=p;
      p->next=newnode;
    }
}

template<class T>
void dll<T>::addatbeg()
{
  T num;
  node<T> *newnode=new node<T>;
  cout<<"\nEnter the data to be inserted at the beginning: ";
  cin>>num;
  cout<<"The data to be inserted is: "<<num;
  newnode->data=num;
  newnode->next=first;
  newnode->prev=NULL;
  first=newnode;
}

template<class T>
void dll<T>::addatloc()
{
  T num;
  int i,loc;
  node<T> *p=first;
  cout<<"\nEnter the data to be inserted: ";
  cin>>num;
  cout<<"The data to be inserted is: "<<num;
  cout<<"\nAfter how many nodes? ";
  cin>>loc;
  cout<<"The data has to be inserted after "<<loc<<" nodes";
  for(i=0;i<loc;i++)
    {
      p=p->next;
      if(p==NULL)
	{
	  cout<<"\nThere are less than "<<loc<<" nodes\n";
	  return;
	}
    }
  p=p->prev;
  node<T> *newnode=new node<T>;   //allocate memory space
  newnode->data=num;
  newnode->next=p->next;
  newnode->prev=p;
  p->next->prev=newnode;
  p->next=newnode;
}

template<class T>
void dll<T>::del()
{
  node<T> *p=first;
  T num;
  cout<<"\nWhich data node to be deleted? ";
  cin>>num;
  cout<<"The node to be deleted is: "<<num;
  while(p!=NULL)
    {
      if(p->data==num)
	{
	  if(p==first)   //if the first node is to be deleted
	    {
	      first=first->next;
	      first->prev=NULL;
	    }
	  else
	    {
	      if(p->next==NULL)  //if last node is to be deleted
		p->prev->next=NULL;
	      else
		{
		  p->next->prev=p->prev;
		  p->prev->next=p->next;
		}
	    }
	  delete p;   //to free memory space
	  return;
	}
      p=p->next;
    }
  cout<<endl<<num<<" not found";
}

template<class T>
void dll<T>::display()
{
  node<T> *p=first;
  cout<<"\nThe current doubly linked list is:\n";
  while(p!=NULL)
    {
      cout<<p->data<<" ";
      p=p->next;
    }
  cout<<endl;
} 

main()
{
  cout<<"THE INTEGER DOUBLY LINKED LIST BEGINS HERE--->>>\n";
  dll<int> int_dll;
  int_dll.addatbeg();
  int_dll.display();
  int_dll.addatend();
  int_dll.display();
  int_dll.addatbeg();
  int_dll.display();
  int_dll.addatbeg();
  int_dll.display();
  int_dll.addatend();
  int_dll.display();
  int_dll.addatloc();
  int_dll.display();
  int_dll.del();
  int_dll.display();
  int_dll.del();
  int_dll.display();
  
  cout<<"\nTHE CHARACTER DOUBLY LINKED LIST BEGINS HERE--->>>\n";
  dll<char> char_dll;
  char_dll.addatbeg();
  char_dll.display();
  char_dll.addatend();
  char_dll.display();
  char_dll.addatbeg();
  char_dll.display();
  char_dll.addatbeg();
  char_dll.display();
  char_dll.addatend();
  char_dll.display();
  char_dll.addatloc();
  char_dll.display();
  char_dll.del();
  char_dll.display();
  char_dll.del();
  char_dll.display();

  cout<<"\nTHE DOUBLE TYPE DOUBLY LINKED LIST BEGINS HERE--->>>";
  dll<double> dbl_dll;
  dbl_dll.addatbeg();
  dbl_dll.display();
  dbl_dll.addatend();
  dbl_dll.display();
  dbl_dll.addatbeg();
  dbl_dll.display();
  dbl_dll.addatbeg();
  dbl_dll.display();
  dbl_dll.addatend();
  dbl_dll.display();
  dbl_dll.addatloc();
  dbl_dll.display();
  dbl_dll.del();
  dbl_dll.display();
  dbl_dll.del();
  dbl_dll.display();
}
//*********************OUTPUT************************ 

THE INTEGER DOUBLY LINKED LIST BEGINS HERE--->>>

Enter the data to be inserted at the beginning: The data to be inserted is: 34
The current doubly linked list is:
34 

Enter the data to be inserted at the end: The data to be inserted is :45
The current doubly linked list is:
34 45 

Enter the data to be inserted at the beginning: The data to be inserted is: 12
The current doubly linked list is:
12 34 45 

Enter the data to be inserted at the beginning: The data to be inserted is: 57
The current doubly linked list is:
57 12 34 45 

Enter the data to be inserted at the end: The data to be inserted is :68
The current doubly linked list is:
57 12 34 45 68 

Enter the data to be inserted: The data to be inserted is: 69
After how many nodes? The data has to be inserted after 3 nodes
The current doubly linked list is:
57 12 34 69 45 68 

Which data node to be deleted? The node to be deleted is: 45
The current doubly linked list is:
57 12 34 69 68 

Which data node to be deleted? The node to be deleted is: 57
The current doubly linked list is:
12 34 69 68 

THE CHARACTER DOUBLY LINKED LIST BEGINS HERE--->>>

Enter the data to be inserted at the beginning: The data to be inserted is: A
The current doubly linked list is:
A 

Enter the data to be inserted at the end: The data to be inserted is :h
The current doubly linked list is:
A h 

Enter the data to be inserted at the beginning: The data to be inserted is: p
The current doubly linked list is:
p A h 

Enter the data to be inserted at the beginning: The data to be inserted is: &
The current doubly linked list is:
& p A h 

Enter the data to be inserted at the end: The data to be inserted is :d
The current doubly linked list is:
& p A h d 

Enter the data to be inserted: The data to be inserted is: G
After how many nodes? The data has to be inserted after 3 nodes
The current doubly linked list is:
& p A G h d 

Which data node to be deleted? The node to be deleted is: h
The current doubly linked list is:
& p A G d 

Which data node to be deleted? The node to be deleted is: #
# not found
The current doubly linked list is:
& p A G d 

THE DOUBLE TYPE DOUBLY LINKED LIST BEGINS HERE--->>>
Enter the data to be inserted at the beginning: The data to be inserted is: 3.45
The current doubly linked list is:
3.45 

Enter the data to be inserted at the end: The data to be inserted is :5.67
The current doubly linked list is:
3.45 5.67 

Enter the data to be inserted at the beginning: The data to be inserted is: 7.89
The current doubly linked list is:
7.89 3.45 5.67 

Enter the data to be inserted at the beginning: The data to be inserted is: 0.098
The current doubly linked list is:
0.098 7.89 3.45 5.67 

Enter the data to be inserted at the end: The data to be inserted is :86.67
The current doubly linked list is:
0.098 7.89 3.45 5.67 86.67 

Enter the data to be inserted: The data to be inserted is: 5.59
After how many nodes? The data has to be inserted after 4 nodes
The current doubly linked list is:
0.098 7.89 3.45 5.67 5.59 86.67 

Which data node to be deleted? The node to be deleted is: 5.59
The current doubly linked list is:
0.098 7.89 3.45 5.67 86.67 

Which data node to be deleted? The node to be deleted is: 86.67
The current doubly linked list is:
0.098 7.89 3.45 5.67 
Destructing
Destructing
Destructing
