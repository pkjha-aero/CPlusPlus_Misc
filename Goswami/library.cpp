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
  void entertainrequest();
  void feedinfo();
  void display();
};

void book_journal::display()
{
  cout<<"\nType: "<<type<<"\nTitle: "<<title<<"\nAuthor: "<<author<<"\nPublisher: "<<publisher<<"\nAccession No: "<<accno<<endl<<endl;
}
void book_journal::feedinfo()
{
  cout<<"\nIs the item a book or a journal? ";
  cin>>type;
  cout<<"\nWhat is it's title? ";
  cin>>title;
  cout<<"\nWho is the author? ";
  cin>>author;
  cout<<"\nWhich Publisher? ";
  cin>>publisher;
  cout<<"\nWhat is the accession number? ";
  cin>>accno;
  cout<<"\nA "<<type<<" titled "<<title<<" is being put into database.";
  cout<<"\nThe author is "<<author<<" and its publisher is "<<publisher;
  cout<<"\nIts accession no is: "<<accno;
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
  strcpy(accno,"\0");
  cout<<"\nA "<<type<<" titled '"<<title<<"' is being requested.";
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
  book_journal book;
  char vendorname[sizeof(book.publisher)];
  /*
   To incorporate: 1>ordered insertion into the file.
                   2>unique accession no
                   3>multiple copies
  */
  cout<<"\n***********************  PHASE I  *************************";
  cout<<"\nFEED INFO ABOUT THE EXISTING BOOKS/JOURNALS :\n";

  char ch='y';
  fstream file1("bookdatabase",ios::in|ios::out|ios::trunc);
  fstream file2("vendorlist",ios::in|ios::out|ios::trunc);
do
  {
    book.feedinfo();
    file1.write( reinterpret_cast<char*>(&book),sizeof(book));
    file2.write( reinterpret_cast<char*>(&book.publisher),sizeof(book.publisher));
    cout<<"\nIs there any more journal or book to be put into database ? (y/n) ";
    cin>>ch;
  }while(ch!='n');

 cout<<"\nARE MORE VENDORS AVAILABLE ? (y/n) ";
 cin>>ch;
 if(ch=='y')
   {
     while(ch=='y')
       {
	 cout<<"\nWhat is the name of the vendor? ";
	 cin>>vendorname;
	 file2.write( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
	 cout<<"\nIs any more vendor available ?(y/n) ";
	 cin>>ch;
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
 cin>>ch;
 while(ch=='y')
   {
     book.entertainrequest();
     fstream file3("bookdatabase",ios::in|ios::out);
     avail=-1;
     avail=search(book,file3);
     if(avail==1)
       cout<<"\nThe book/journal is already there in the library.";
     else
       {
	 fstream file4("vendorlist",ios::in|ios::out);
	 availv=-1;
	 availv=searchvendor(book,file4);
	 if(availv==0)
	   cout<<"\nThe Vendor for the requested book/journal is not available,so the item can't be procured.";
	 else
	   {
	     fstream file5("bookdatabase",ios::in|ios::out);
	     cout<<"\nThe Vendor is available,supplies the book & the book is now in thelibrary.\nGive a unique accession no to the book/journal: ";
	     cin>>book.accno;
	     file5.seekp(0,ios::end);
	     cout<<"\nFileptr: "<<file5.tellg();
	     file5.write( reinterpret_cast<char*>(&book),sizeof(book));
	     file5.close();
 	    }
	 file4.close();
       }
     file3.close();
     cout<<"\nIs there any more request? (y/n) ";
     cin>>ch;
   }
}
