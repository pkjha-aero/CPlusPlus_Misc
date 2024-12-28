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
  node<T> *prev;     //poiter to its previous node
  node<T> *next;     //poiter to its next node
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
    cout<<"Destructing the doubly linked list\n";
  }
  void addatend(); //function to add a data at the end of the dll
  void addatbeg(); //function to add a data at the beginning of the dll
  void addatloc(); //to add a data at correct location,i.e,in order
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
  node<T> *p=first;
  node<T> *q;
  node<T> *newnode=new node<T>;
  cout<<"\nEnter the data to be inserted: ";
  cin>>num;
  cout<<"The data to be inserted is: "<<num;
  if(p==NULL)             // if the list is empty
    {
      first=new node<T>;  //allocate space for the new node
      first->prev=NULL;
      first->data=num;
      first->next=NULL;
    }
  else
    {
      while(p->data<num)
	{
	  q=p;
	  p=p->next;
	  if(p==NULL)
	    break;
	}
      if(p==first)      //insertion to be done at the beginning
	{               //datum to be inserted is less than all other data
	  newnode->data=num;
	  newnode->next=first;
	  newnode->prev=NULL;
	  first=newnode;
	}
      else
	{
	  if(p==NULL)    //insertion to be made at the end 
	    {            //datum to be added is greater than all other data 
	      newnode->data=num;
	      newnode->next=NULL;
	      newnode->prev=q;
	      q->next=newnode;        
	    }
	  else          //insertion to be done in-between
	    {
	      newnode->data=num;
	      newnode->next=p;
	      newnode->prev=q;
	      p->prev=newnode;
	      q->next=newnode;
	    }
	}
   }
}
//all the case considered..del from end,beginning or at a midway position
template<class T>
void dll<T>::del()
{
  node<T> *p=first;
  node<T> *q;
  node<T> *r;
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
	      else          //other than first or last node to be deleted
		{
		  q=p->prev;
		  r=p->next;
		  r->prev=q;
		  q->next=r;
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
  int_dll.addatend();
  int_dll.display();
  int_dll.addatbeg();
  int_dll.display();
  int_dll.addatloc();
  int_dll.display();
  int_dll.addatloc();
  int_dll.display();
  int_dll.addatloc();
  int_dll.display();
  int_dll.addatloc();
  int_dll.display();
  int_dll.del();
  int_dll.display();
  int_dll.del();
  int_dll.display();
 
  cout<<"\nTHE CHARACTER DOUBLY LINKED LIST BEGINS HERE--->>>\n";
  dll<char> char_dll;
  char_dll.addatend();
  char_dll.display();
  char_dll.addatbeg();
  char_dll.display();
  char_dll.addatloc();
  char_dll.display();
  char_dll.addatloc();
  char_dll.display();
  char_dll.addatloc();
  char_dll.display();
  char_dll.addatloc();
  char_dll.display();
  char_dll.del();
  char_dll.display();
  char_dll.del();
  char_dll.display();

  cout<<"\nTHE DOUBLE TYPE DOUBLY LINKED LIST BEGINS HERE--->>>";
  dll<double> dbl_dll;
  dbl_dll.addatend();
  dbl_dll.display();
  dbl_dll.addatbeg();
  dbl_dll.display();
  dbl_dll.addatloc();
  dbl_dll.display();
  dbl_dll.addatloc();
  dbl_dll.display();
  dbl_dll.addatloc();
  dbl_dll.display();
  dbl_dll.addatloc();
  dbl_dll.display();
  dbl_dll.del();
  dbl_dll.display();
  dbl_dll.del();
  dbl_dll.display();
}
THE INTEGER DOUBLY LINKED LIST BEGINS HERE--->>>

Enter the data to be inserted at the end: The data to be inserted is :89
The current doubly linked list is:
89 

Enter the data to be inserted at the beginning: The data to be inserted is: 12
The current doubly linked list is:
12 89 

Enter the data to be inserted: The data to be inserted is: 45
The current doubly linked list is:
12 45 89 

Enter the data to be inserted: The data to be inserted is: 67
The current doubly linked list is:
12 45 67 89 

Enter the data to be inserted: The data to be inserted is: 23
The current doubly linked list is:
12 23 45 67 89 

Enter the data to be inserted: The data to be inserted is: 78
The current doubly linked list is:
12 23 45 67 78 89 

Which data node to be deleted? The node to be deleted is: 89
The current doubly linked list is:
12 23 45 67 78 

Which data node to be deleted? The node to be deleted is: 12
The current doubly linked list is:
23 45 67 78 

THE CHARACTER DOUBLY LINKED LIST BEGINS HERE--->>>

Enter the data to be inserted at the end: The data to be inserted is :a
The current doubly linked list is:
a 

Enter the data to be inserted at the beginning: The data to be inserted is: P
The current doubly linked list is:
P a 

Enter the data to be inserted: The data to be inserted is: #
The current doubly linked list is:
# P a 

Enter the data to be inserted: The data to be inserted is: @
The current doubly linked list is:
# @ P a 

Enter the data to be inserted: The data to be inserted is: t
The current doubly linked list is:
# @ P a t 

Enter the data to be inserted: The data to be inserted is: *
The current doubly linked list is:
# * @ P a t 

Which data node to be deleted? The node to be deleted is: *
The current doubly linked list is:
# @ P a t 

Which data node to be deleted? The node to be deleted is: &
& not found
The current doubly linked list is:
# @ P a t 

THE DOUBLE TYPE DOUBLY LINKED LIST BEGINS HERE--->>>
Enter the data to be inserted at the end: The data to be inserted is :90.56
The current doubly linked list is:
90.56 

Enter the data to be inserted at the beginning: The data to be inserted is: 0.098
The current doubly linked list is:
0.098 90.56 

Enter the data to be inserted: The data to be inserted is: 567.2
The current doubly linked list is:
0.098 90.56 567.2 

Enter the data to be inserted: The data to be inserted is: 45.56
The current doubly linked list is:
0.098 45.56 90.56 567.2 

Enter the data to be inserted: The data to be inserted is: 10.92
The current doubly linked list is:
0.098 10.92 45.56 90.56 567.2 

Enter the data to be inserted: The data to be inserted is: 50.2
The current doubly linked list is:
0.098 10.92 45.56 50.2 90.56 567.2 

Which data node to be deleted? The node to be deleted is: 45.56
The current doubly linked list is:
0.098 10.92 50.2 90.56 567.2 

Which data node to be deleted? The node to be deleted is: 90.56
The current doubly linked list is:
0.098 10.92 50.2 567.2 
Destructing the doubly linked list
Destructing the doubly linked list
Destructing the doubly linked list
