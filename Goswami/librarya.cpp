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

main()
{
  int i=0;
  book_journal book;
  char vendorname[sizeof(book.publisher)];

  cout<<"\n***********************  PHASE I  *************************";
  cout<<"\nFEED INFO ABOUT THE EXISTING BOOKS/JOURNALS :\n";

  char ch='y';
  fstream file1("bookdatabase",ios::in|ios::out|ios::trunc);
  fstream file2("vendorlist",ios::in|ios::out|ios::trunc);
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
        file1.write( reinterpret_cast<char*>(&book),sizeof(book));
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
 file1.seekg(0);
 file1.read( reinterpret_cast<char*>(&book),sizeof(book));
 while(!file1.eof())
   {
     book.display();
     file1.read( reinterpret_cast<char*>(&book),sizeof(book));
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
	     file8.seekp(0,ios::end);
	     cout<<"\nThe Vendor is available,supplies the book & the book is now in the library.\nGive a unique accession no to each copy of the book/journal: ";
	     for(i=1;i<=book.copies;i++)
	       {
		 book.copyno=i;
		 book.feedaccno();
		 fstream file9("bookdatabase",ios::in|ios::out);
	         checkaccno(book,file9);
		 file9.close();
		 file8.write( reinterpret_cast<char*>(&book),sizeof(book));
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
 };
 enum membertype{ug,pg,rs,ms,staff,faculty,ousider};
 char mtype[7][10]={"ug","pg","rs","ms","staff","faculty","ousider"};
 class users
 {
 public:
   enum membertype t;
   char id[10];
   char name[30];
   int capacity;
   int onaccount;
   int fine;
   issuable details[10];
   void feedinfo();
   void giveinfo();
   void issuebook();
   void computefine();
 };
 void users::feedinfo()
   {
     cout<<"\nWhat is the type of the user? ";
     cin>>t;
     cout<<"\nWhat is the name of the user? ";
     cin>>name;
     cout<<"\nWhat it the ID ? ";
     cin>>id;
     switch(t)
       {
       case ug:capacity=3;
	 break;
       case pg:capacity=4;
	 break;
       case rs:capacity=5;
	 break;
       case ms:capacity=4;
	 break;
       case staff:capacity=5;
	 break;
       case faculty:capacity=10;
	 break;
       case outsider:capacity=2;
       }
     onaccount=0;
     fine=0;
   }
 void users::giveinfo()
   {
     cout<<"\nMember ID : "<<id;
     cout<<"\nName: "<<name;
     cout<<"\nType: "<<mtype[t];
     cout<<"\nCapacity: "<<capacity;
     cout<<"\nBooks On Account : "<<onaccount;
     cout<<"\nFine: "<<fine<<endl;
   }

}

