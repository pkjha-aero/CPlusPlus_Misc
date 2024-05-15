
/***************************
PANKAJ KUMAR JHA
01 MA 2011
LIBRARY AUTOMATION ASSIGMENT
****************************/

#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

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
  int issuability;
  int availability;
  char issuedate[15];
  char duedate[15];
  int issued;
  int read;
  book_journal()
  {
    availability=1;
    issued=0;
    read=0;
  }
  void entertainrequest();
  void feedinfo();
  void feedaccno();
  void giveninfo();
  void display();
  void checkaccno();
};

void book_journal::checkaccno()
{
  book_journal obj;
  fstream filem("books",ios::in|ios::out);
  int pos=0;
  filem.read( reinterpret_cast<char*>(&obj),sizeof(obj));
  while(!filem.eof())
    {
      cout<<endl<<obj.accno;
      if(strcmp(obj.accno,accno)==0)
	{
	  cout<<"\nThis accession no already exists,please enter another: ";
	  this->feedaccno();
	  fstream filen("books",ios::in|ios::out);
	  this->checkaccno();
	  filen.close();
	  break;
	}
      pos+=sizeof(book_journal);
      filem.read( reinterpret_cast<char*>(&obj),sizeof(obj));
    }
 }

void book_journal::display()
{
  cout<<"\nType: "<<type<<"\nTitle: "<<title<<"\nAuthor: "<<author<<"\nPublisher: "<<publisher<<"\nCopies: "<<copies<<"\nCopy No.:"<<copyno<<"\nAccession No: "<<accno<<"\nIssue Date :"<<issuedate<<"\nDue Date : "<<duedate<<endl;
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
  cout<<accno;
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
   int issued;
   int usedjl;
   book_journal details[10];
   users()
   {
     onaccount=0;
     fine=0;
     issued=0;
     usedjl=0;
   }
   void feedinfo();
   void showinfo();
   void issuebook();
   void returnbook();
   void computefine();
 };
void users::issuebook()
{
  char c;
  int flag=0,fl=0; //right now, no book can be issued ..validation ,user's existence to be checked
  book_journal book1,book2;
  users pers;
  pers.t=-1;
  cout<<"\nWhat is the member's ID ?";
  cin>>id;
  cout<<id;

  fstream f2("userlist",ios::in|ios::out);
  int pos=0;
  f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
  while(!f2.eof())
    {
      if(strcmp(pers.id,id)==0)
	{
	  flag=1;
	  *this=pers;
	  break;
	}
      pos=pos+sizeof(users); 
      f2.seekg(pos,ios::beg);
      f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
    }
  f2.close();
  if(flag==0)
    {
      cout<<"\nNo user with ID "<<id<<" exits\n";
    }
  if(flag==1 && pers.t==6)
    {
      cout<<"\nDoes the user have a valid authorisation letter? (y/n) ";
      cin>>c;cout<<c;      
      if(c=='n')
	{
	  cout<<"\nBook cannot be issued to this user as not authorised.";
	  flag=0;
	}
    }
  if(flag==1)
      {
	if(onaccount==capacity)
	  cout<<"\nAccount Full......No more book can be issued.";
	else
	  {
	    cout<<"\nGive the title of the item to be issued: ";
	    cin>>book1.title;
	    cout<<book1.title;
	    fstream f3("books",ios::in|ios::out);
	    int bookpos=f3.tellg();
	    f3.read( reinterpret_cast<char*>(&book2),sizeof(book2));
	    while(!f3.eof())
	      {
		if(strcmp(book1.title,book2.title)==0) // the requied book exists
		  {
		    if(book2.availability==1)
		      {
			if(book2.issuability==1)
			  {
			    cout<<"\nWhat is today's date (dd/mm/yyyy)? ";
			    cin>>book2.issuedate;
			    cout<<book2.issuedate;
			    char a[15];
			    strcpy(a,book2.issuedate);
			    int dd,mm,yyyy,days;
			    dd=(a[0]-48)*10+(a[1]-48);
			    mm=(a[3]-48)*10+(a[4]-48);
			    yyyy=(a[6]-48)*1000+(a[7]-48)*100+(a[8]-48)*10+(a[9]-48);
			    days=yyyy*365+mm*30+dd;
			    switch(t)   //issued for different periods to different ppl
			      {
			      case 0:mm+=2;
				break;
			      case 1:mm+=3;
				break;
			      case 2:mm+=6;
				break;
			      case 3:mm+=3;
				break;
			      case 4:mm+=1;
				break;
			      case 5:mm+=6;
				break;
			      case 6:mm+=1;
			      }
			    if(mm>12)
			      {
				mm=mm%12;
				z=mm/12;
			      }
			    yyyy+=z;
			    a[0]=dd/10+48;
			    a[1]=dd%10+48;
			    a[2]='/';
			    a[3]=mm/10+48;
			    a[4]=mm%10+48;
			    a[5]='/';
			    a[6]=yyyy/1000+48;
			    a[7]=(yyyy%1000)/100+48;
			    a[8]=((yyyy%1000)%100)/10+48;
			    a[9]=(((yyyy%1000)%100)%10)+48;
			    a[10]='\0';
			    strcpy(book2.duedate,a);
			    cout<<"\nDueDate"<<book2.duedate;
			    book2.availability=0; //book2 info modified
			    book2.issued++;
			    f3.seekp(bookpos);
			    f3.write( reinterpret_cast<char*>(&book2),sizeof(book2));
			    details[onaccount]=book2;
			    onaccount++;
			    issued++;
			    fstream f0("userlist",ios::in|ios::out);
			    f0.seekp(pos,ios::beg);
			    pers=*this;
			    f0.write( reinterpret_cast<char*>(&pers),sizeof(pers));//ok
			    f0.close();
			    break;
			  }
			else
			  { 
			    cout<<"\nThis is a journal ...cannot be issued..but read it here only";
                            book2.read++;
			    usedjl++; 
			    f3.seekp(bookpos);
			    f3.write( reinterpret_cast<char*>(&book2),sizeof(book2));
			    fstream f0("userlist",ios::in|ios::out);
			    f0.seekp(pos,ios::beg);
			    pers=*this;
			    f0.write( reinterpret_cast<char*>(&pers),sizeof(pers));//ok
			    f0.close();
			    break;
			  }
		      }
		    else
		      fl=1;
		  }
		bookpos=f3.tellg();
		cout<<"\nFile pointer is at : "<<bookpos;
		f3.read( reinterpret_cast<char*>(&book2),sizeof(book2));
	      }
	    if(strcmp(book1.title,book2.title)!=0)
	      cout<<"\nThe book required doesn't exist\n";
	    if(fl==1)
	      cout<<"\nThe required book is issued to someone else.....SORRY...\n";
	  }
      }
}
void users::computefine()
{
  int flag=0;
  users pers;
  cout<<"\nWhat is the member's ID ?";
  cin>>id;
  cout<<id;

  fstream f2("userlist",ios::in|ios::out);
  int pos=0;
  f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
  while(!f2.eof())
    {
      if(strcmp(pers.id,id)==0)
	{
	  flag=1;
	  *this=pers;
	  break;
	}
      pos=pos+sizeof(users); 
      f2.seekg(pos,ios::beg);
      f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
    }
  f2.close();
  if(flag==0)
    {
      cout<<"\nNo user with ID "<<id<<" exits\n";
    }
  char a[15];
  int dd,mm,yyyy,days,due;
  if(flag==1)
    {
      cout<<"\nWhat is today's date (dd/mm/yyyy) ? ";
      cin>>a;
      cout<<a;
      dd=(a[0]-48)*10+(a[1]-48);
      mm=(a[3]-48)*10+(a[4]-48);
      yyyy=(a[6]-48)*1000+(a[7]-48)*100+(a[8]-48)*10+(a[9]-48);
      days=yyyy*365+mm*30+dd;
      for(int i=0;i<onaccount;i++)
	{
	  strcpy(a,details[i].duedate);
	  dd=(a[0]-48)*10+(a[1]-48);
	  mm=(a[3]-48)*10+(a[4]-48);
	  yyyy=(a[6]-48)*1000+(a[7]-48)*100+(a[8]-48)*10+(a[9]-48);
	  due=yyyy*365+mm*30+dd;
	  if(days>due)
	    fine=fine+(days-due);
	}
      cout<<"\nFine : "<<fine<<endl;
      pers=*this;
      fstream a0("userlist",ios::in|ios::out);
      a0.seekp(pos,ios::beg);
      a0.write( reinterpret_cast<char*>(&pers),sizeof(pers));
      a0.close();
    }
}
void users::returnbook()
{
  int flag=0,i,j;
  char s[15];
  book_journal book;
  users pers;
  cout<<"\nWhat is the member's ID ?";
  cin>>id;
  cout<<id;

  fstream f2("userlist",ios::in|ios::out);
  int pos=0;
  f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
  while(!f2.eof())
    {
      if(strcmp(pers.id,id)==0)
	{
	  flag=1;
	  *this=pers;
	  break;
	}
      pos=pos+sizeof(users); 
      f2.seekg(pos,ios::beg);
      f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
    }
  f2.close();
  if(flag==0)
    {
      cout<<"\nNo user with ID "<<id<<" exits\n";
    }
  if(flag==1)
    {
      cout<<"\nWhat is the accession no of the book to be returned? ";
      cin>>s; 
      cout<<s;
      for(i=0;i<onaccount;i++)
	{
	  if(strcmp(details[i].accno,s)==0)
	    break;
	}
      if(i==onaccount)
	cout<<"\nThe book with Acc No "<<s<<" is not on this member's account\n";
      else
	{
	  for(j=i+1;j<onaccount;j++)
	    details[j-1]=details[j];
	  onaccount--;  // removed from user's account

	  fstream k("books",ios::in|ios::out);
	  int posit=k.tellg();
	  k.read( reinterpret_cast<char*>(&book),sizeof(book));
	  while(!k.eof())
	    {
	      if(strcmp(book.accno,details[i].accno)==0)
		break;
	      posit=k.tellg();
	      cout<<"\nFile Ptr Location : "<<posit;
	      k.read( reinterpret_cast<char*>(&book),sizeof(book));
	    }   // last val of posit gives the pos from where last book is read
	  book.availability=1;
	  strcpy(book.issuedate,"\0");
	  strcpy(book.duedate,"\0");
	  fstream j("books",ios::in|ios::out);
	  j.seekp(posit,ios::beg);
	  j.write( reinterpret_cast<char*>(&book),sizeof(book));
	}
    }
}
void users::feedinfo()
{
  cout<<"\nWhat is the type of the user?(ug=0,pg=1,rs=2,ms=3,staff=4,faculty=5,outsider=6)";
  cin>>t;
  cout<<t;
  cout<<"\nWhat is the name of the user? ";
  cin>>name;
  cout<<name;
  cout<<"\nWhat it the ID ? ";
  cin>>id;
  cout<<id;
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
}
void users::showinfo()
{
  cout<<"\nMember ID : "<<id;
  cout<<"\nName: "<<name;
  cout<<"\nType: "<<mtype[t];
  cout<<"\nCapacity: "<<capacity;
  cout<<"\nFine: "<<fine;
  cout<<"\nNo of times issued a book: "<<issued;
  cout<<"\nNo of times accessed a journal: "<<usedjl;
  cout<<"\nBooks On Account : "<<onaccount;
  if(onaccount>0)
    {
      for(int i=0;i<onaccount;i++)
	{
	  cout<<"\n---------Book No "<<i+1<<"----------\n";
	  details[i].display();
	}
    }
  cout<<endl;
}


void showbooklist()
{
  book_journal book;
  fstream fil("books",ios::in|ios::out);
  fil.read( reinterpret_cast<char*>(&book),sizeof(book));
  while(!fil.eof())
    {
      book.display();
      fil.read( reinterpret_cast<char*>(&book),sizeof(book));
    }
}
void showuserlist()
{
  users member;
  fstream f1("userlist",ios::in|ios::out);
  f1.read( reinterpret_cast<char*>(&member),sizeof(member));
  while(!f1.eof())
    {
      member.showinfo();
      f1.read( reinterpret_cast<char*>(&member),sizeof(member));
    }
}
void showvendorlist()
{
  char s[30];
  fstream fill("vendorlist",ios::in|ios::out);
  fill.read( reinterpret_cast<char*>(&s),sizeof(s));
  while(!fill.eof())
    {
      cout<<endl<<s;
      fill.read( reinterpret_cast<char*>(&s),sizeof(s));
    }
}

void deleteaccount()
{
  int flag=0;
  users pers;
  char s[10];
  cout<<"\nWhat is the member's ID whose account is to be deleted ? ";   
  cin>>s;
  cout<<s;

  fstream f2("userlist",ios::in|ios::out);
  int pos=0;
  f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
  while(!f2.eof())
    {
      if(strcmp(pers.id,s)==0)
	{
	  flag=1;
	  break;
	}
      pos=pos+sizeof(users); 
      f2.seekg(pos,ios::beg);
      f2.read( reinterpret_cast<char*>(&pers),sizeof(pers));
    }
  f2.close();
  if(flag==0)
    {
      cout<<"\nNo user with ID "<<s<<" exits\n";
    }
  if(flag==1) //if this user exists and is located at position pos in file userlist
    {
      fstream fla("userlist",ios::in|ios::out);
      fstream flb("userlist2",ios::in|ios::out|ios::trunc);
      int i=0;
      cout<<"\ni= "<<i;
      fla.read( reinterpret_cast<char*>(&pers),sizeof(pers));
      while(!fla.eof())
	{
	  if(i!=pos)
	    flb.write( reinterpret_cast<char*>(&pers),sizeof(pers));
	  i=i+sizeof(pers);
	  cout<<"\ni= "<<i;
          fla.read( reinterpret_cast<char*>(&pers),sizeof(pers));
	}
      remove("userlist");
      fla.close();
      rename("userlist2","userlist");
      flb.close();
    }
}
main()
{
  int i=0;
  book_journal book;
  char vendorname[sizeof(book.publisher)];

  cout<<"\n***********************  PHASE I  *************************";
  cout<<"\nFEED INFO ABOUT THE EXISTING BOOKS/JOURNALS :\n";

  char ch='y';
  fstream file1("books",ios::in|ios::out|ios::trunc);
  fstream file2("vendorlist",ios::in|ios::out|ios::trunc);
do
  {
    book.feedinfo();
    for(i=1;i<=book.copies;i++)
      {
	book.copyno=i;
	book.feedaccno();
	book.checkaccno();
	strcpy(book.issuedate,"\0");
	strcpy(book.duedate,"\0");
	if(strcmp(book.type,"journal")==0)
	  book.issuability=0;
	else
	  book.issuability=1;
	book.giveninfo();
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
	 cout<<vendorname;
	 file2.write( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
	 cout<<"\nIs any more vendor available ?(y/n) ";
	 cin>>ch;cout<<ch;
       }
   }
 cout<<"\n*********THE CURRENT BOOKS & JOURNALS*************\n";
 // showbooklist();
 file1.seekg(0);
 file1.read( reinterpret_cast<char*>(&book),sizeof(book));
 while(!file1.eof())
   {
     book.display();
     file1.read( reinterpret_cast<char*>(&book),sizeof(book));
   }

 cout<<"\n********THE CURRENT VENDORLIST************\n";
 //showvendorlist();
 file2.seekg(0);
 file2.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
 while(!file2.eof())
   {
     cout<<endl<<vendorname;
     file2.read( reinterpret_cast<char*>(&vendorname),sizeof(vendorname));
   }

 cout<<endl;

 cout<<"\n**********ENTERTAIN REQUEST****************\n";
 int avail;                 
 int availv;
 cout<<"\nIs there any request from a Faculty? (y/n) ";
 cin>>ch;cout<<ch;
 while(ch=='y')
   {
     book.entertainrequest();
     fstream file3("books",ios::in|ios::out);
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
	     fstream file8("books",ios::in|ios::out);
	     file8.seekp(0,ios::end);
	     cout<<"\nThe Vendor is available,supplies the book & the book is now in the library.\nGive a unique accession no to each copy of the book/journal: ";
	     for(i=1;i<=book.copies;i++)
	       {
		 book.copyno=i;
		 book.feedaccno();
	         book.checkaccno();
                 strcpy(book.issuedate,"\0");
		 strcpy(book.duedate,"\0");
		 if(strcmp(book.type,"journal")==0)
		   book.issuability=0;
		 else
		   book.issuability=1;
		 book.giveninfo();
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
 //showbooklist();
 fstream file6("books",ios::in|ios::out);
 file6.read( reinterpret_cast<char*>(&book),sizeof(book));
 while(!file6.eof())
   {
     book.display();
     file6.read( reinterpret_cast<char*>(&book),sizeof(book));
   }

 cout<<"\n********THE CURRENT VENDORLIST************\n";
 //showvendorlist();
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
 //showuserlist();
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
    cout<<ch;
  }while(ch!='n');

 cout<<"\n************* THE CURRENT USER LIST ****************\n";
 //showuserlist();
 fstream fon("userlist",ios::in|ios::out);
 fon.seekg(0);
 fon.read( reinterpret_cast<char*>(&member),sizeof(member));
 while(!fon.eof())
   {
     member.showinfo();
     fon.read( reinterpret_cast<char*>(&member),sizeof(member));
   }

 cout<<"\n*************COMPUTE FINE*************\n";
 do
   {
     member.computefine();
     cout<<"\nAny more user's fine to be computed? ";
     cin>>ch;
  }while(ch!='n');

 cout<<"\n************* THE CURRENT USER LIST ****************\n";
 // showuserlist();

 fstream fom("userlist",ios::in|ios::out);
 fom.read( reinterpret_cast<char*>(&member),sizeof(member));
 while(!fom.eof())
   {
     member.showinfo();
     fom.read( reinterpret_cast<char*>(&member),sizeof(member));
   }

 cout<<"\n*************RETURN BOOK*************\n";
 do
   {
     member.returnbook();
     cout<<"\nAny more book to be returned? ";
     cin>>ch;
   }while(ch!='n');

 cout<<"\n************* THE CURRENT USER LIST ****************\n";
 //showuserlist();

 fstream fol("userlist",ios::in|ios::out);
 fol.read( reinterpret_cast<char*>(&member),sizeof(member));
 while(!fol.eof())
   {
     member.showinfo();
     fol.read( reinterpret_cast<char*>(&member),sizeof(member));
   }
 /***************************PHASE III********************/

 cout<<"\n********************DELETE ACCOUNT**********************\n";
//  ch='y';
//  while(ch=='y')
//    {
//      deleteaccount();
//      cout<<"\nIs there any more account to be deleted? (y/n) ";
//      cin>>ch;
//      cout<<ch;
//    }
//  //showuserlist();
//  fstream fok("userlist",ios::in|ios::out);
//  fok.read( reinterpret_cast<char*>(&member),sizeof(member));
//  while(!fok.eof())
//    {
//      member.showinfo();
//      fok.read( reinterpret_cast<char*>(&member),sizeof(member));
//    }

 /******************************PHASE IV****************************/

 cout<<"\n***************GENERATING STATISTICS*************\n";
 int a1=0,a2=0,a3=0,a4=0,b1=0,b2=0,b3=0,b4=0;
 fstream t1("userlist",ios::in|ios::out);
 fstream t2("books",ios::in|ios::out);
 int pos=0;

 cout<<"\npos= "<<pos;
 t1.read( reinterpret_cast<char*>(&member),sizeof(member));
 member.showinfo();
 while(!t1.eof())
   {
     if(member.issued>a1)
       {
	 a1=member.issued;
	 b1=pos; //b1 is the position of the user who has issued the books max no of times
       }
     if(member.usedjl>a2)
       {
	 a2=member.usedjl;
	 b2=pos;//b2 is the pos of the user who has accessed the journal max no of times
       }
     pos+=sizeof(users);
     cout<<"\npos= "<<pos;
     t1.seekg(pos);
     t1.read( reinterpret_cast<char*>(&member),sizeof(member));
     member.showinfo();
   }

 pos=0;
 cout<<"\npos= "<<pos;
 t2.read( reinterpret_cast<char*>(&book),sizeof(book));
 book.display();
 while(!t2.eof())
   {
     if(book.issued>a3)
       {
	 a3=book.issued;
	 b3=pos; //b3 is the position of the book issued max no of times
       }
     if(book.read>a4)
       {
	 a4=book.read;
	 b4=pos;//b4 is the pos the journal accessed max no of times
       }
     pos+=sizeof(users);
     cout<<"\npos= "<<pos;
     t1.seekg(pos);
     t1.read( reinterpret_cast<char*>(&member),sizeof(member));
     member.showinfo();
   }

 fstream t3("userlist",ios::in|ios::out);
 fstream t4("books",ios::in|ios::out);
 cout<<"\nThe user who has got max no of books issued is :\n";
 t3.seekg(b1);
 t3.read( reinterpret_cast<char*>(&member),sizeof(member));
 member.showinfo();

 cout<<"\nThe user who has accessed journals max no of times is :\n";
 t3.seekg(b2);
 t3.read( reinterpret_cast<char*>(&member),sizeof(member));
 member.showinfo();

 cout<<"\nThe book issued max no of times is:\n";
 t4.seekg(b3);
 t4.read( reinterpret_cast<char*>(&book),sizeof(book));
 book.display();

 cout<<"\nThe journal accessed max no of times is:\n";
 t4.seekg(b4);
 t4.read( reinterpret_cast<char*>(&book),sizeof(book));
 book.display();
}
