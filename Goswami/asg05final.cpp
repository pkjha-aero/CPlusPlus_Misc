//PANKAJ KUMAR JHA
//01 MA 2011
//ASSIGNMENT 5

#include<iostream.h>
#include<string.h>

template<class T>
class node
{
public:
  T data;
  node<T> *next;
  node<T> *prev;
};

template<class T>
class set
{
public:
  node<T> *first;
  set()
  {
    first=NULL;
  }
  void addelem();    // to add an element to the set in order
  //friend void del(T t,set<T> X);
  void constructset();//new element to be added at the proper place
  void display();
  set<T> operator=(set<T> Y);
  //friend int search(T t,set<T> X);
  //friend set<T> unionof(set<T> A,set<T> B);
  //friend set<T> intsect(set<T> A,set<T> B);
};
template<class T>
void set<T>::addelem()
{
  node<T> *newnode=new node<T>;
  node<T> *p=first;
  node<T> *q;
  T num;
  cout<<"\nEnter the element you want to put into the set: ";
  cin>>num;
  cout<<"\nThe element to be added to the set is :"<<num;
  if(first==NULL) // to add an element when the set is empty
    {
      first=new node<T>;
      first->next=NULL;
      first->prev=NULL;
      first->data=num;
    }
  else
    {
      while(p->data<num) // traverse the list until correct pos is got
	{
	  q=p;
	  p=p->next;
	  if(p==NULL)
	    break;
	}
      if(p==first)     // if the new element is to be added at beg
	{              //i.e, the new element is smallest
	  newnode->data=num;
	  newnode->next=first;
	  newnode->prev=NULL;
	  first=newnode;
	}
      else
	{
	  if(p==NULL)      // new element is the largest
	    {              // i.e. to be added at the end 
	      newnode->data=num;
	      newnode->next=NULL;
	      newnode->prev=q;
	      q->next=newnode;
	    }
	  else        //if the new element lies in-between 
	    {         // i.e, to be added in-between
	      newnode->data=num;
	      newnode->next=p;
	      newnode->prev=q;
	      p->prev=newnode;
	      q->next=newnode;
	    }
	}
    }
}

template<class T>
void del(T num,set<T> X)    // delete t from X
{
  node<T> *p=X.first;
  while(p!=NULL)
    {
      if(p->data==num)
	{
	  if(p==X.first)   //if the first element is to be deleted
	    {
	      X.first=X.first->next;
	      X.first->prev=NULL;
	    }
	  else
	    {
	      if(p->next==NULL)  //if last element is to be deleted
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
    }
}
template<class T>
void set<T>::constructset()
{
  char a[5]="yes";
  while(strcmp(a,"yes")==0)
    {
      addelem();
      cout<<"\nDo you want to add more elements to the set? ";
      cin>>a;
      cout<<a;
    }
}

template<class T>
void set<T>::display()
{
  node<T> *p=first;
  if(first==NULL)
    cout<<"\nThe set is empty.";
  else
    {
      cout<<"\nThe elements of the set are:\n";
      while(p!=NULL)
	{
	  cout<<p->data<<" ";
	  p=p->next;
	}
      cout<<endl;
    }
} 
template<class T>
set<T> set<T>::operator=(set<T> Y)
{
  this->first=Y.first;
  return *this;
}

template<class T>
int search(T t,set<T> X)    //find t in X
{
  node<T> *p=X.first;
  while(p->data!=t)
    p=p->next;
  if(p==NULL)
    return 0;
  else
    return 1;
}
template<class T>
set<T> unionof(set<T> A,set<T> B)
{
  set<T> C,D;
  D.first=A.first;
  node<T> *p=D.first;
  C.first=D.first;
  node<T> *q;
  while(p!=NULL)
    {
      if(search(p->data,B)==1)
	del(p->data,D);
      q=p;
      p=p->next;
    }
  q->next=B.first;
  B.first->prev=q;
  return C;
}
template<class T>
set<T> intsect(set<T> A,set<T> B)
{
  set<T> C,D;
  D.first=A.first;
  node<T> *p=D.first;
  C.first=D.first;
  while(p!=NULL)
    {
      if(search(p->data,B)==0)
	del(p->data,D);
      p=p->next;
    }
  return C;
}

main()
{
  set<int> P,Q,R,S;
  cout<<"\nCONSTRUCTING THE FIRST SET\n";
  P.constructset();
  P.display();
  cout<<"\nCONSTRUCTING THE SECOND SET\n";
  Q.constructset();
  Q.display();
  cout<<"\nTHE UNION \n";
  R=unionof(P,Q);
  R.display();
  cout<<"\nTHE INTERSECTION\n";
  S=intsect(P,Q);
  S.display();
}
/*********************OUTPUT*************/

CONSTRUCTING THE FIRST SET

Enter the element you want to put into the set: 
The element to be added to the set is :56
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :67
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :23
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :99
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :12
Do you want to add more elements to the set? no
The elements of the set are:
12 23 56 67 99 

CONSTRUCTING THE SECOND SET

Enter the element you want to put into the set: 
The element to be added to the set is :67
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :99
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :48
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :62
Do you want to add more elements to the set? yes
Enter the element you want to put into the set: 
The element to be added to the set is :78
Do you want to add more elements to the set? no
The elements of the set are:
48 62 67 78 99 

THE UNION 

The elements of the set are:
12 23 48 56 62 67 78 99

THE INTERSECTION

The elements of the set are:
67 99
 
             **********THE END*********
