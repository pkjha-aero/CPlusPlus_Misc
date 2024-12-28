/***************************
PANKAJ KUMAR JHA
01 MA 2011
LIBRARY AUTOMATION ASSIGMENT
****************************/

#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

//enum status{in,out};

class book_journal
{
public:
  char title[30];
  char author[30];
  char type[15];
  char accno[15];
  char publisher[30];
  int copies;
  int copyno;
  void entertainrequest();
  void feedinfo();
  void feedaccno();
  void giveninfo();
  void display();
  void checkaccno();
};

void checkaccno(book_journal book,fstream &filem)
{
  book_journal obj;
  while(!filem.eof())
    {
      filem.read( reinterpret_cast<char*>(&obj),sizeof(obj));
      obj.display();
      cout<<endl<<obj.accno;
      if(strcmp(obj.accno,book.accno)==0)
	{
	  cout<<"\nThis accession no already exists,please enter another: ";
	  book.feedaccno();
	  fstream filen("bookdatabase",ios::in|ios::out);
	  checkaccno(book,filen);
	  filen.close();
	}
    }
 }

void book_journal::display()
{
  cout<<"\nType: "<<type<<"\nTitle: "<<title<<"\nAuthor: "<<author<<"\nPublisher: "<<publisher<<"\nCopies: "<<copies<<"\nCopy No.:"<<copyno<<"\nAccession No: "<<accno<<endl;
}
void book_journal::feedinfo()
{
  cout<<"\nIs the item a book or a journal? ";
  cin>>type;
  cout<<"\nWhat is its title? ";
  cin>>title;
  cout<<"\nWho is the author? ";
  cin>>author;
  cout<<"\nWhich Publisher? ";
  cin>>publisher;
  cout<<"\nHow many copies are there? ";
  cin>>copies;
}
void book_journal::feedaccno()
{
  cout<<"\nWhat is the accession no? ";
  cin>>accno;
}
void book_journal::giveninfo()
{
  cout<<"\nA "<<type<<" titled "<<title<<" is being put into database.";
  cout<<"\nThe author is "<<author<<" and its publisher is "<<publisher;
  cout<<"\nIts accession no is: "<<accno<<" No of copies: "<<copies<<" Copy No: "<<copyno<<endl;
}
void book_journal::entertainrequest()
{
  cout<<"\nIs the item requested a book or a journal? ";
  cin>>type;
  cout<<"\nWhat is it's title? ";
  cin>>title;
  cout<<"\nWho is the author? ";
  cin>>author;
  cout<<"\nWhich Publisher? ";
  cin>>publisher;
  cout<<"\nHow many copies are required? ";
  cin>>copies;
  strcpy(accno,"\0");
  cout<<"\n"<<copies<<" "<<type<<"(s) titled '"<<title<<"' is(are) being requested.";
  cout<<"\nThe author is '"<<author<<"' and its publisher is '"<<publisher<<"'\n";
}

int search(book_journal book,fstream &file)
{
  book_journal obj;
  while(!file.eof())
    {
      file.read( reinterpret_cast<char*>(&obj),sizeof(obj));
      if(strcmp(book.title,obj.title)==0)
	return 1;
    }
  return 0;
}
int searchvendor(book_journal book,fstream &file)
{
  char xyz[sizeof(book.publisher)];
  while(!file.eof())
    {
      file.read( reinterpret_cast<char*>(&xyz),sizeof(xyz));
      if(strcmp(book.publisher,xyz)==0)
	return 1;
    }
  return 0;
}

/************* CLASSES FOR PHASE II ************/
 class issuable:public book_journal
 {
 public:
   int issuability;
   char issuedate[15];
   char duedate[15];
   issuable()
   {
     issuability=-1;
     strcpy(issuedate,"\0");
     strcpy(duedate,"\0");
   }
   void show()
   {
     cout<<"\nTitle: "<<title<<"\nAuthor: "<<author<<"\nPublisher: "<<publisher<<"\nCopies: "<<copies<<"\nCopy No.:"<<copyno<<"\nAccession No: "<<accno<<" Issue Date "<<issuedate<<" Due Date : "<<duedate<<endl;
   }
 };
// enum membertype{ug,pg,rs,ms,staff,faculty,outsider};
 char mtype[7][10]={"ug","pg","rs","ms","staff","faculty","ousider"};
 class users
 {
 public:
   int t;
   char id[10];
   char name[30];
   int capacity;
   int onaccount;
   int fine;
   issuable details[10];
   void feedinfo();
   void showinfo();
   void issuebook();
   void returnbook();
   void computefine();
 };
void users::issuebook()
{
  char c;
  int flag=0; //right now, no book can be issued ..validation ,user's existence to be checked
  issuable book1,book2;
  users pers;
  pers.t=-1;
  cout<<"\nWhat is the member's ID ?";
  cin>>id;

  fstream f2("userlist",ios::in|ios::out);
  int pos=0;
  while(!f2.eof())
    {
      f2.seekg(pos,ios::beg);
      f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
      if(strcmp(pers.id,id)!=0)
	{
	  flag=1;
	  break;
	}
      pos=pos+sizeof(users);
    }
  f2.close();
  if(flag==0)
    cout<<"\nNo user with ID "<<id<<" exits.";
  if(flag==1 && pers.t==6)
    {
      cout<<"\nDoes the user have a valid aothorisation letter? (y/n) ";
      cin>>c;cout<<c;
      if(c=='n')
	flag=0;
    }
  if(flag==0)
    cout<<"\nBook cannot be issued to this user as not authorised.";
  else
    {
      if(onaccount==capacity)
	cout<<"\nAccount Full..no more book can be issued.";
      else
	{
	  cout<<"\nGive the title of the item to be issued: ";
	  cin>>book1.title;
	  fstream f3("books",ios::in|ios::out);
	  f3.read( reinterpret_cast<char*>(&book2),sizeof(book2));
	  while(!f3.eof())
	    {
	      if(strcmp(book1.title,book2.title)==0) // the requied book exists
		{
		  if(book2.issuability==1)
		    {
		      details[onaccount]=book2;
		      onaccount++;
		      break;
		    }
		  else
		    cout<<"\nThis is a journal ...so cannot be issued."
		}
	      f3.read( reinterpret_cast<char*>(&book2),sizeof(book2));
	    }
	  if(strcmp(book1.title,book2.title)!=0)
	    cout<<"\nThe book required doesn't exist.";
	}
    }
}
void users::feedinfo()
{
  cout<<"\nWhat is the type of the user?(ug=0,pg=1,rs=2,ms=3,staff=4,faculty=5,outsider=6)";
  cin>>t;
  cout<<"\nWhat is the name of the user? ";
  cin>>name;
  cout<<"\nWhat it the ID ? ";
  cin>>id;
  switch(t)
    {
    case 0:capacity=3;
      break;
    case 1:capacity=4;
      break;
    case 2:capacity=5;
      break;
    case 3:capacity=4;
      break;
    case 4:capacity=5;
      break;
    case 5:capacity=10;
      break;
    case 6:capacity=2;
    }
  onaccount=0;
  fine=0;
}
void users::showinfo()
{
  cout<<"\nMember ID : "<<id;
  cout<<"\nName: "<<name;
  cout<<"\nType: "<<mtype[t];
  cout<<"\nCapacity: "<<capacity;
  cout<<"\nFine: "<<fine;
  cout<<"\nBooks On Account : "<<onaccount;
  if(onaccount>0)
    {
      for(int i=1;i<=onaccount;i++)
	{
	  cout<<"\n  Book No "<<i<<"\n";
	  details[i].show();
	}
    }
  cout<<endl;
}

main()
{
  int i=0;
  book_journal book;
  issuable object;
  char vendorname[sizeof(book.publisher)];

  cout<<"\n***********************  PHASE I  *************************";
  cout<<"\nFEED INFO ABOUT THE EXISTING BOOKS/JOURNALS :\n";

  char ch='y';
  fstream file1("bookdatabase",ios::in|ios::out|ios::trunc);
  fstream file2("vendorlist",ios::in|ios::out|ios::trunc);
  fstream mfile("books",ios::in|ios::out|ios::trunc);
do
  {
    book.feedinfo();
    for(i=1;i<=book.copies;i++)
      {
	book.copyno=i;
	book.feedaccno();
	fstream file10("bookdatabase",ios::in|ios::out);
	checkaccno(book,file10);
	file10.close();
	strcpy(object.type,book.type);
        strcpy(object.title,book.title);
        strcpy(object.author,book.author);
        strcpy(object.publisher,book.publisher);
        strcpy(object.accno,book.accno);
	object.copies=book.copies;
	object.copyno=book.copyno;
	strcpy(object.issuedate,"\0");
	strcpy(object.duedate,"\0");
	if(strcmp(object.type,book)==0)
	  object.issuability=1;
	else
	  object.isuability=0;
        file1.write( reinterpret_cast<char*>(&book),sizeof(book));
	mfile.write( reinterpret_cast<char*>(&object),sizeof(object));
      }
    file2.write( reinterpret_cast<char*>(&book.publisher),sizeof(book.publisher));
    cout<<"\nIs there any more journal or book to be put into database ? (y/n) ";
    cin>>ch;cout<<ch;
  }while(ch!='n');

 cout<<"\nARE MORE VENDORS AVAILABLE ? (y/n) ";
 cin>>ch;cout<<ch;
 if(ch=='y')
   {
     while(ch=='y')
       {
	 cout<<"\nWhat is the name of the vendor? ";
	 cin>>vendorname;
	 file2.write( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
	 cout<<"\nIs any more vendor available ?(y/n) ";
	 cin>>ch;cout<<ch;
       }
   }
 cout<<"\n*********THE CURRENT BOOKS & JOURNALS*************\n";
 mfile.seekg(0);
 mfile.read( reinterpret_cast<char*>(&book),sizeof(book));
 while(!mfile.eof())
   {
     book.show();
     mfile.read( reinterpret_cast<char*>(&book),sizeof(book));
   }

 cout<<"\n********THE CURRENT VENDORLIST************\n";
 file2.seekg(0);
 file2.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
 while(!file2.eof())
   {
     cout<<endl<<vendorname;
     file2.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
   }

 //both file1 & file2 have ended...tellg will return -1 only if not opened afresh

 cout<<endl;

 cout<<"\n**********ENTERTAIN REQUEST****************\n";
 int avail;                   //initial status of availability
 int availv;
 cout<<"\nIs There any request from a Faculty? (y/n) ";
 cin>>ch;cout<<ch;
 while(ch=='y')
   {
     book.entertainrequest();
     fstream file3("bookdatabase",ios::in|ios::out);
     avail=-1;
     avail=search(book,file3);
     if(avail==1)
       cout<<"\nThe book/journal is already there in the library.\n";
     else
       {
	 fstream file4("vendorlist",ios::in|ios::out);
	 availv=-1;
	 availv=searchvendor(book,file4);
	 if(availv==0)
	   cout<<"\nThe Vendor for the requested book/journal is not available,so the item can't be procured.";
	 else
	   { 
	     fstream file8("bookdatabase",ios::in|ios::out);
	     fstream nfile("books",ios::in|ios::out);
	     file8.seekp(0,ios::end);
	     nfile.seekp(0,ios::end);
	     cout<<"\nThe Vendor is available,supplies the book & the book is now in the library.\nGive a unique accession no to each copy of the book/journal: ";
	     for(i=1;i<=book.copies;i++)
	       {
		 book.copyno=i;
		 book.feedaccno();
		 fstream file9("bookdatabase",ios::in|ios::out);
	         checkaccno(book,file9);
		 file9.close();
                 strcpy(object.type,book.type);
		 strcpy(object.title,book.title);
		 strcpy(object.author,book.author);
		 strcpy(object.publisher,book.publisher);
		 strcpy(object.accno,book.accno);
		 object.copies=book.copies;
		 object.copyno=book.copyno;
		 strcpy(object.issuedate,"\0");
		 strcpy(object.duedate,"\0");
		 if(strcmp(object.type,book)==0)
		   object.issuability=1;
		 else
		   object.isuability=0;
		 file8.write( reinterpret_cast<char*>(&book),sizeof(book));
		 nfile.write( reinterpret_cast<char*>(&object),sizeof(object));
 	       }
	     file8.close();
	   }
	 file4.close();
       }
     file3.close();
     cout<<"\nIs there any more request? (y/n) ";
     cin>>ch;cout<<ch;
   }

 cout<<"\n*********THE CURRENT BOOKS & JOURNALS*************\n";
 fstream file6("bookdatabase",ios::in|ios::out);
 file6.read( reinterpret_cast<char*>(&book),sizeof(book));
 while(!file6.eof())
   {
     book.display();
     file6.read( reinterpret_cast<char*>(&book),sizeof(book));
   }

 cout<<"\n********THE CURRENT VENDORLIST************\n";
 fstream file7("vendorlist",ios::in|ios::out);
 file7.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
 while(!file7.eof())
   {
     cout<<endl<<vendorname;
     file7.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
   }
 cout<<endl;

 cout<<"\n********************* PHASE II ***********************\n";

 users member;
 cout<<"\n*************GIVE THE DETAILS OF USERS*******************\n";

 fstream f1("userlist",ios::in|ios::out|ios::trunc);
do
  {
    member.feedinfo();
    f1.write( reinterpret_cast<char*>(&member),sizeof(member));
    cout<<"\nIs there any more member to be put into dataase? (y/n) ";
    cin>>ch;cout<<ch;
  }while(ch!='n');

 cout<<"\n************* THE CURRENT USER LIST ****************\n";
 f1.seekg(0);
 f1.read( reinterpret_cast<char*>(&member),sizeof(member));
 while(!f1.eof())
   {
     member.showinfo();
     f1.read( reinterpret_cast<char*>(&member),sizeof(member));
   }
 cout<<"\n************ ISSUE A BOOK TO AN USER ***********\n";
do
  {
    member.issuebook();
    cout<<"\nAny more book to be issued? ";
    cin>>ch;
  }while(ch!='n');
}

