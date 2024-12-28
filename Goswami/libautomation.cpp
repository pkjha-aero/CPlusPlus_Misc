
/*NAME :PANKAJ K JHA
  ROLL :01MA2011
  
  PROJECT 1 : DEVELOPING A LIBRARY AUTOMATION SYSTEM
*/

#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max 10
#define maxb 100
#define maxj 100
#define maxp 15
#define umax 100
#define nmax 50
#define AvgLibuse 1
/*average library usage taken as 1 for output purpose */

/******************************************************************************************

                                        PHASE - I

******************************************************************************************/

int numb,numbook,numj;
enum Item{book,journal};

class books;
class journals;
class biblio
{
protected:
  char title[nmax];
  char publisher[nmax];
  float price;
public:
  void setTitle(char t[]){strcpy(title,t);}
  char *getTitle(){return title;}
  void setPublisher(char pub[]){strcpy(publisher,pub);}
  char *getPublisher(){return publisher;}
  void setPrice(float p){price=p;}
  float getPrice(){return price;}
  friend bool searchBookDatabase(books &);
  friend bool searchJournalDatabase(journals &);
};


class books:public biblio
{
  char author[nmax];
  char accno[nmax];
  int avail;
public:
  char idate[11];
  char rdate[11];
  books()
  {
    setTitle(""); setAuthor("");
    setPublisher(""); setAccNo("");
    setPrice(0);setAvail(1);
  }  
  void getBook();
  void setAuthor(char ath[]){strcpy(author,ath);}
  char *getAuthor(){return author;}
  void setAccNo(char code[]){strcpy(accno,code);}
  char *getAccNo(){return accno;}
  void setAvail(int a){avail=a;}
  int checkAvail(){return avail;}
  void issuedisplay()
  {
    cout << "\nTitle: " << title;
    cout << "\nAuthor: " << author;
    cout << "\nAcc. Number: " << accno;
    cout << "\n";
  }
  void procbdisplay()
  {
    cout << "\nTitle: " << title;
    cout << "\nAuthor: " << author;
    cout << "\nPublisher: " << publisher;
    cout << "\nPrice: " << price;
    cout << "\n";
  }  
  friend void biblioRequest();
  friend bool searchBookDatabase(books &);
};


class journals:public biblio
{
 public:
  void getJournal();
  void procjdisplay()
  {
    cout << "\nTitle: " << title;
    cout << "\nPublisher: " << publisher;
    cout << "\nPrice: " << price;
    cout << "\n";
  }
  friend void biblioRequest();
  friend bool searchJournalDatabase(journals &);
};


class vendors
{
protected:
  char name[nmax];
  char publisher[nmax];
public:
  void getVendor();
  void setVenName(char ch[]){strcpy(name,ch);}
  char* getVenName(){return name;}
  void setVenPublisher(char pub[]){strcpy(publisher,pub);}
  char* getVenPublisher(){return publisher;}
  void displayVen()
  {
    cout <<"\nVendor Name: " << name << endl;
    cout <<"dealing publisher: " << publisher;
    cout << "\n\n";
  }
  friend void createVendorDatabase();
  friend void makePurchaseOrder(vendors,Item,books ,int,journals ,int);
  friend void receiveOrder(vendors [],Item,books [],int [],journals [],int);
};


void input(char *ch)
{
  char c;
  for(int i=0;;i++)
    {
      c=getchar();
      if(c=='\n') {ch[i]='\0';break;}
      ch[i]=c;	
    }
}


void books::getBook()
{
  cout <<"\nEnter Book Title:";getchar();
  input(title); cout << title;
  cout <<"\nEnter Author Name:";
  input(author); cout << author;
  cout <<"\nEnter Publisher:";
  input(publisher); cout << publisher;
  cout <<"\nEnter Accession Number:";
  input(accno); cout << accno;
  cout <<"\nEnter price:";
  cin >>price; cout << price << endl;
}

void journals::getJournal()
{
  cout <<"\nEnter Journal Title:";getchar();
  input(title); cout << title;
  cout <<"\nEnter Publisher:";
  input(publisher); cout << publisher;
  cout <<"\nEnter price:";
  cin >>price; cout << price << endl;
}


void vendors::getVendor()
{
  cout <<"\nEnter Vendor Name:";getchar();
  input(name); cout <<name;
  cout <<"\nEnter the dealing publisher:";
  input(publisher); cout << publisher;
}


void createBooksDatabase()
{
  cout << "\n------------------- create BooksDatabase --------------------\n";
  int i=0;char c;books bk[maxb];
  ofstream bkfile("booksfile.dat",ios::out);
  do
    {
      bk[i].getBook();i++;
      cout <<"\nWant to Add more Books to the Database (y/n) ?:";
      cin >>c;cout << c <<endl;
    }while(c!='n');
  for(int j=0;j<=i;j++) { bkfile.write((char *)&bk[j],sizeof(bk[j]));}  
  bkfile.close();
}

void createJournalsDatabase()
{
  cout << "\n------------------- create JournalsDatabase --------------------\n";
  int i=0;char c; journals jrnl[maxj];
  ofstream jrnlfile("journalsfile.dat",ios::out);
  do
    {
      jrnl[i].getJournal();i++;
      cout <<"\nWant to Add more Journals to the Database (y/n) ?:";
      cin >>c;cout << c <<endl;
    }while(c!='n');
  for(int j=0;j<=i;j++) { jrnlfile.write((char *)&jrnl[j],sizeof(jrnl[j]));}
  jrnlfile.close();
}



void createVendorDatabase()
{
  cout << "\n------------------- createVendorList ---------------------\n";
  int i=0;char c;
  vendors v[maxp];
  do
    {
      v[i].getVendor();i++;
      cout <<"\nWant to Add  more Vendor to the Database (y/n) ?:";
      cin >> c;cout << c <<endl;
    }while(c!='n');

  ofstream vfile("vendorfile.dat",ios::out);
  if(!vfile)
    {
      cout << "\nCannot open the file 'vendorlist.dat' .\n";
      return;
    }
  for(int j=0;j<=i;j++)
    {
      vfile.write((char *)&(v[j]),sizeof(v[j]));
    }
  vfile.close();
}


bool searchBookDatabase(books &sbk)
{
  cout << "\n---------------------- searchBookDatabase ---------------------\n";
  ifstream bfile("booksfile.dat",ios::in);
  if(!bfile) { cout << "\nCannot open the file 'booksfile.dat' !\n";return false;}
  books curbk; numbook=0;
  while(bfile.read((char *)&curbk,sizeof(curbk)))
    {
      numbook++;
      if(strcmp(curbk.title,sbk.title)==0)
	{
	  cout << "\nA book with given Title has been found.\n";
	  if(strcmp(curbk.author,sbk.author)==0)
	    {
	      cout << "\nA book with given Title and Author has been found.\n"; 
	      if(strcmp(curbk.accno,sbk.accno)==0)
		{ 
		  if(curbk.avail==1)
		    {
		      cout << "\nA book with given Title , Author and Accession number has been found.\n"; 
		      sbk=curbk;;return true;
		    }
		  else
		    {
		      cout << "\nThe book with the given Accession number has been already issued by somebody.\n";
		    }
		}
	      else { cout << "\nThe Acession number did not match.\n"; }
	    }
 	}
    }
  bfile.close();
  return false;
}


bool searchJournalDatabase(journals &sjrnl)
{
  cout << "\n-------------------- searchJournalDatabase --------------------\n";
  ifstream jfile("journalsfile.dat",ios::in);
  journals curjrnl;
  if(!jfile) { cout << "\ncould not open 'journalsfile.dat' !\n";return false;}

  else
    while(jfile.read((char *)&curjrnl,sizeof(curjrnl)))
      {
	if(strcmp(curjrnl.title,sjrnl.title)==0) { return true;}
      }
  jfile.close();  
  return false;
}

char *bibitem[2]={"book","journal"};

void makePurchaseOrder(vendors ven,Item rItem,books bk,int nbk,journals jr,int njr)
{   
  cout << "\n---------------------- makePurchaseOrder ------------------------\n\n";
  cout << "A purchase order has been sent to the vendor '" << ven.name;
  cout << " ' for the following " << bibitem[rItem] << "(s)" <<endl;
  if(rItem==book)
    { 
      cout << "\nwith " <<  nbk << " copies :\n" ;
      bk.setPrice(0);bk.procbdisplay(); 
      cout <<"price not known yet\n";
      
    }
  else
    {
      cout << "totalling "<< njr ; 
      jr.setPrice(0);jr.procjdisplay();  
      cout <<"price not known yet\n";
    }
}


int bookGetpos(fstream &bfile,char acc[])
{
  int bno=0; books b;
  bfile.seekg(0,ios::beg);
  while(bfile.read((char *)&b,sizeof(b)))
    {
      bno++; if(strcmp(b.getAccNo(),acc)==0) { return bno;}
    }
  return -1;
}


void writeToBibDatabase(books bk)
{
  ofstream bibfile("booksfile.dat",ios::app);
  bibfile.write((char *)&bk,sizeof(bk));
}

void writeToBibDatabase(journals jrnl)
{
  ofstream bibfile("journalsfile.dat",ios::app);
  bibfile.write((char *)&jrnl,sizeof(jrnl));
}


void assignAccNo(Item requestItem,books bk[],int nbk[],journals jrnl[],int njr)
{
  cout <<"\n--------------------- assignAccNo --------------------\n\n";  
  char nc[max],nc1[max],cd[max],code[max];int n=0,asg=0;
  if(requestItem==book)
    {
      cout<< "\nWant to Assign Accession code  (M)anually or (A)utomatically: ";
      char c;cin >>c ;cout << c;
      if(c=='m'||c=='M')
	{
	  for(int j=0;j<numb;j++)
	    {
	      for(int i=0;i<nbk[j];i++)
		{
		  do
		    {
		      cout<<"\nEnter the Accession code for book " << j+1 << " copy " << i+1 << " :" ;
		      cin>>code;cout <<code;
		      fstream bfile("booksfile.dat",ios::in|ios::out);
		      if(bookGetpos(bfile,code)>0)
			{
			  cout <<"\nAccession code already exists !\n";asg=0;
			}
		      else 
			{
			   bk[j].setAccNo(code);
			   bk[j].issuedisplay();
			   writeToBibDatabase(bk[j]);
			   asg=1;
			}
		    }while(asg!=1);
		}
	    }
	}
      
      else if(c=='a'||c=='A')
	{
	  strcpy(code,"TB");
	  for(int j=0;j<numb;j++)
	    {
	      numbook++;
	      for(int i=0;i<nbk[j];i++)
	      {
		n++;
		sprintf(nc,"%d",numbook);
		sprintf(nc1,"0%d",n);
		strcpy(cd,nc);strcat(cd,nc1);
		strcat(code,cd);
		bk[j].setAccNo(code);
		strcpy(code,"TB");
		bk[j].issuedisplay();
		writeToBibDatabase(bk[j]);
	      }
	    }
	}
      cout << "\n\nThe books has been assigned Unique codes for issuing purpose\n";
      cout << "to the users\n\n";
    }
  else
    {
      cout <<"\nThe Journals will not be issued so no accession numbers is produced for them.\n";
      for(int i=0;i<=njr;i++) { writeToBibDatabase(jrnl[i]);}
    }
  remove("pendingorder.dat");
}


void receiveOrder(vendors ven[],Item rItem,books bk[],int nbk[],journals jr[],int njr)
{ 
  float price;
  cout << "\n---------------------- receiveOrder -----------------------\n\n"; 
  if(rItem==book)
    {
      for(int i=0;i<numb;i++)
	{
	  cout << "\n" << ven[i].name << " has delivered the requested order ";
	  cout << "for the " << bibitem[rItem] <<"s\n"; 
	  cout <<"\nBook " << i+1;
	  cout << " with "<< nbk[i] << " copies .\n" ;
	  cout <<"Enter the price of the ordered book " << i+1 << " :";
	  cin >> price;cout << price;
	  bk[i].setPrice(price);
	  bk[i].procbdisplay();
	}
    }
  else
    {
      cout << "with "<< njr<< " journals .\n" ;
      for(int i=0;i<numj;i++)
	{
	  cout << "\n" << ven[i].name << " has delivered the requested order ";
	  cout << "for the " << bibitem[rItem] <<"s\n"; 
	  cout <<"Enter the price of the ordered journal " << i+1 << " :";
	  cin >> price;cout << price;
	  jr[i].setPrice(price);
	  jr[i].procjdisplay();
	}
    }
  cout << "\n\nAcquisition Section received the " << bibitem[rItem] <<endl;
  assignAccNo(rItem,bk,nbk,jr,njr);
}


bool pendingOrder()
{
  cout << "\n--------------------- pendingOrder ---------------------\n\n";
  int p;
  ifstream pfile("pendingorder.dat");
  pfile.seekg(0,ios::end);
  p=pfile.tellg();
  if(p==0)
    return false;
  cout << "\nThere are pending orders.";
  return true;
}


vendors seekVendor(Item requestItem,char *bibpub)
{ 
  cout << "\n-------------------- seekVendorList --------------------\n\n";
  vendors vendor;
  fstream venfile("vendorfile.dat",ios::in);
  if(!venfile)
    {
      cout << "\nCannot open the file 'vendorfile.dat' .\n";
    }
  while(venfile.read((char *)&vendor,sizeof(vendor)))
    {
      if(strcmp(vendor.getVenPublisher(),bibpub)==0)
	{
	  cout << "\nThe vendor for the "<< bibitem[requestItem] << "with publisher "<< bibpub << " has been found\n"; 
	  vendor.displayVen();
	  return vendor;
	}
    }
  venfile.close();
  vendor.setVenName("altvendor");
  vendor.setVenPublisher("allpublishers");
  cout << "\nAlternate vendor for the "<<bibitem[requestItem] << " has been found\n"; 
  cout << "\nPurchase request will be send to the alternate vendors .\n";
  return vendor;
}


void processItem(Item rItem,books bk[],int nbk[],journals jr[],int njr)
{
  cout << "\n--------------------- ProcessItem ---------------------\n";
  int i=0,num;
  vendors vendor[maxp];char *bibpub[2],*title[2];int numcp[maxb];
  cout << "\nAcquisition Section processing Requests !\n\n";
  if(pendingOrder())
    {
      if(rItem==book)
	{
	  num=numb;
	  for(i=0;i<numb;i++)
	    {
	      title[i]=bk[i].getTitle();
	      bibpub[i]=bk[i].getPublisher();
	      numcp[i]=nbk[i];
	    }
	}
      else
	{
	  num=numj;
	  for(i=0;i<numj;i++)
	    {
	      title[i]=jr[i].getTitle();
	      bibpub[i]=jr[i].getPublisher();
	    }
	}
      
      for(i=0;;i++)
	{
	  cout << "\n\n" << numcp[i] << " copies of the " << bibitem[rItem];
	  cout <<"\n'"  << title[i] <<  " ' will be ordered !\n";
	  cout << "The " << bibitem[rItem] << " has been processed ";
	  cout << "for purchase order\n\n";
	  if(rItem==book)
	    {
	      if(i==numb-1) break;
	    }
	  else 
	    if(i==numj-1) break;
	}
      char ch;
      for(int i=0;i<num;i++)
	{
	  vendor[i]=seekVendor(rItem,bibpub[i]);
	  if(strlen(vendor[i].getVenName())==0)
	    {
	      cout <<"\nSorry ! No vendor found\n";return; 
	    }
	  cout << "\nDoes the vendor has the requested " << bibitem[rItem] <<"(s) :(y/n)";
	  cin >> ch;cout <<ch;
	  if(ch=='y')
	    makePurchaseOrder(vendor[i],rItem,bk[i],nbk[i],jr[i],njr);
	  else 
	    {
	      cout << "\nSorry ! the vendor does not have the requested "<< bibitem[rItem] <<"(s)\n";
	      bk[i]=bk[i+1];numb--;
	    }
	}
    }
  receiveOrder(vendor,rItem,bk,nbk,jr,njr);
}


void OrderFile(char *bibtitle,char *bibauthor,char *bibpub,int num)
{
  fstream pfile("pendingorder.dat",ios::out);  
  pfile << bibtitle;
  pfile << bibauthor;
  pfile << bibpub;
  pfile << num;
  pfile.close();
}
 
 
void OrderFile(char *bibtitle,char *bibpub)
{
  fstream pfile("pendingorder.dat",ios::out);
  pfile << bibtitle;
  pfile << bibpub;
  pfile.close();
}


void processRequest(Item rItem,books bk[],int nbk[],journals jr[],int njr)
{
  cout << "\n\n------------------- ProcessRequest --------------------\n\n";
  int i=0;
  if(rItem==book)
    {
      for(i=0;i<numb;i++)
	{
	  if(searchBookDatabase(bk[i]))
	    {
	      cout << "\nRequested Book found in Database!\n";
	    }
	  else
	    {
	      cout << "\nRequested Book not found in Database, it will be ordered!\n";
	      OrderFile(bk[i].getTitle(),bk[i].getAuthor(),bk[i].getPublisher(),nbk[i]);
	    } 
	}
    }
  else if(rItem==journal)
    {
      for(i=0;i<numj;i++)
	{ 
	  if(searchJournalDatabase(jr[i]))
	    {
	      cout << "\nRequested Journal found in Database!\n";
	    }
	  else
	    {
	      cout << "\nRequested Journal not found in Database, it will be ordered!\n";
	      OrderFile(jr[i].getTitle(),jr[i].getPublisher());
	    } 
	}
    }
  processItem(rItem,bk,nbk,jr,njr);
}


void biblioRequest()
{
  cout << "\n\n--------------------- biblioRequest --------------------\n\n";
  int numcopy[maxb];char ch;
  books bk[maxb];journals jrnl[maxj];
  char bibtitle[nmax],bibauthor[nmax],bibpub[nmax];
  char facname[nmax],depcode[5];
  
  cout << "\n\nBook/Journals Request Form for Faculty\n\n";
  getchar();
  cout << "\nPlease Enter your name:";
  input(facname);cout << facname;
  cout << "\nPlease Enter your department code:";
  input(depcode); cout << depcode << "\n";
  cout <<"want 1.(b)ook or 2.(j)ournal ?";
  cin >> ch;cout << ch <<endl;
  
  Item requestItem;
  if(ch=='b' || ch=='1')
    {
      requestItem=book;   
      cout << "\nHow many  books do you want:";
      cin >> numb;cout << numb <<endl;
      for(int i=0;i<numb;i++)
	{
	  getchar();
	  cout << "\nPlease Enter the title of the book " << i+1 <<" :\n";
	  input(bibtitle);
	  bk[i].setTitle(bibtitle);
	  cout << bk[i].title <<endl;
	  
	  cout << "\nPlease Enter the Name of the Author:\n";
	  input(bibauthor);
	  bk[i].setAuthor(bibauthor);
	  cout << bk[i].author <<endl;
	  
	  cout << "\nPlease Enter the Name of Publisher:\n";
	  input(bibpub);
	  bk[i].setPublisher(bibpub);
	  cout << bk[i].publisher << endl;
	  
	  cout << "\nHow many copies do you want:";
	  cin >> numcopy[i];cout << numcopy[i] <<endl;
	  
	  cout << "\nYour request has been saved and will be processed !\n\n";
	}
      processRequest(requestItem,bk,numcopy,jrnl,numj);
    }  
  else if(ch=='j' || ch=='2')
    { 
      requestItem=journal;    
      cout << "\nHow many journals do you want:";
      cin >> numj;cout << numj <<endl;  
      for(int i=0;i<numj;i++)
	{
	  cout << "\nPlease Enter the title of the Journal:\n";
	  input(jrnl[i].title);
	  cout << jrnl[i].title << endl; 
	  cout << "\nPlease Enter the Name of Publisher:";
	  input(jrnl[i].publisher);
	  cout << jrnl[i].publisher << endl;	  
	  cout << "\nYour request has been saved and will be processed !\n\n";
	}
      processRequest(requestItem,bk,numcopy,jrnl,numj);
    }
  else { cout << "\nInvalid entry !"; }
}



/******************************************************************************************

                                        PHASE - II

******************************************************************************************/

int numoutsider=0;
enum usertype{faculty,staff,UG,PG,RS,MS,outsider};
char *usrtype[7]={"faculty","staff","UG","PG","RS","MS","outsider"};

class user
{
protected:
  char name[nmax];
  char ID[max];
  usertype usr;
  char dept[max];
  int maxbooks;
  int numbooks;
  int maxretperiod;
  books issuedbook[max];
  float fine;
  int libuse;
public:
  user(){numbooks=0;fine=0;libuse=0;}
  void getUser();
  void setName(char nm[]){strcpy(name,nm);}
  char *getName(){return name;}
  void setID(char c[]){strcpy(ID,c);}
  char *getID(){return ID;}
  void setUserType(usertype ut){usr=ut;}
  usertype getUserType(){return usr;}
  void setDept(char d[]){strcpy(dept,d);}
  void setMaxbooks(int n){maxbooks=n;}
  int getMaxbooks(){return maxbooks;}
  void setNumbooks(int n){numbooks=n;}
  int getNumbooks(){return numbooks;}
  void setMaxRetPeriod(int n){maxretperiod=n;}
  void issueBook();
  void returnBook();
  void calcFine(char []);  
  float getFine(){return fine;}
  void calcRetDate(books &);
  void userInfoDisplay()
  {
    cout << "\nName  : " << name;
    cout << "\nID    : " << ID;
    cout << "\nUser  : " << usrtype[usr];
    cout << "\nDept. : " << dept << endl;
  }  
  void checkouts();
  void checkAccount();
  int getLibuse(){return libuse;}
  friend void createUserDatabase();
  friend bool searchUserDatabase(fstream &,char [],user &);
  friend int bookGetpos(fstream &,char []);
  friend void updateBookDatabase(fstream &,user );
  friend int userGetpos(fstream &,char []);
  friend void updateUserDatabase(fstream &,user );
  friend void deleteUserRecord(char []);
  ~user(){};
};


void user::getUser()
{
  int ut;
  cout <<"\nEnter User Name:";getchar();
  input(name); cout <<name;
  cout <<"\nEnter User ID :";
  input(ID); cout << ID;
  cout << "\nEnter User Type\n";
  cout <<"(0) faculty ,(1) staff ,(2) UG ,(3) PG ,(4) RS ,(5) MS ,(6) outsider :";
  cin >> ut;cout <<ut<<endl;
  cout << usrtype[ut];usr=usertype(ut);
  cout <<"\nEnter User Deptartment ('N/A' for outsider):";
  cin >> dept ;cout << dept <<endl;
  switch(usr)
    {
    case faculty:
      maxbooks=10;break;
    case staff:
      maxbooks=5;break;
    case UG:
      maxbooks=3;break;
    case PG:
      maxbooks=4;break;
    case RS:
      maxbooks=8;break;
    case MS:
      maxbooks=6;break;
    case outsider:
      maxbooks=1;break;
    }
}


void createUserDatabase()
{
  cout << "\n---------------------- create Users Database --------------------\n";
  ofstream ufile("userfile.dat");
  if(!ufile) { cout << "\nCannot open 'userfile.dat' \n";return;}
  user u[umax];int i=0;char c;
  do
    {
      u[i].getUser();i++;
      cout <<"\nWant to Add more User to the Database (y/n)?:";
      cin >>c; cout <<c; 
    }while(c!='n');

  for(int j=0;j<=i;j++){ ufile.write((char *)&u[j],sizeof(u[j])); }
  ufile.close();  
}


bool searchUserDatabase(fstream &ufile,char id[],user &libuser)
{
  cout << "\n---------------------- searchUserDatabase -----------------------\n";
  user u;
  numoutsider=0;
  ufile.seekg(0,ios::beg);
  while(ufile.read((char*)&u,sizeof(u)))
    {
      if(u.usr==outsider) { numoutsider++;}
      if(strcmp(u.ID,id)==0) { libuser=u;return true; }
    }
  return false;
}


int userGetpos(fstream &ufile,char id[])
{
  int uno=0; user u;
  ufile.seekg(0,ios::beg);
  while(ufile.read((char *)&u,sizeof(u)))
    {
      uno++;if(strcmp(u.ID,id)==0) { return uno;}
    }
  return -1;
}


void updateBookDatabase(fstream &bfile,books b)
{
  cout << "\n-------------------- updateBookDatabase -----------------------\n";
  int pos =bookGetpos(bfile,b.getAccNo());
  cout << "\nBook Record No :"<< pos <<endl;
  int position=(pos-1)*sizeof(books);
  bfile.seekp(position);//pointing to the position to be updated
  bfile.write((char *) &b,sizeof(b));//writing the record
  cout << "\nBook Record with the the Accession No.  " << b.getAccNo() <<" has been updated\n";
}


void updateUserDatabase(fstream &ufile,user u)
{
  cout << "\n------------------ updateUserDatabase ----------------------\n";
  int pos =userGetpos(ufile,u.ID);
  cout << "\nUser Record No :"<< pos <<endl;
  int position=(pos-1)*sizeof(user);
  ufile.seekp(position);//pointing to the position to be updated
  ufile.write((char *) &u,sizeof(u));//writing the record
  cout << "\nUser Record with the the ID " << u.getID() <<" has been updated\n";
}


void arrayfree(char pdt[],int n)
{
  for(int i=n;i<n+3;i++) pdt[i]=' ';
}


void user::calcFine(char pdt[])
{
  cout << "\n---------------------  userFine -----------------------\n";
  cout << "\nPresent Date :"<<pdt <<endl;  
  fstream ufile("userfile.dat",ios::in|ios::out);
  float bfine=0;
  int fp,ret,dd,mm,yy,dd1,mm1,yy1;
  int d,m,y;char idt[10];
  
  dd1=atoi(pdt);arrayfree(pdt,0);
  mm1=atoi(pdt);arrayfree(pdt,3);
  yy1=atoi(pdt);
  fine=0;
  for(int n=0;n<numbooks;n++)
    {
      strcpy(idt,issuedbook[n].idate);
      dd=atoi(idt);arrayfree(idt,0);
      mm=atoi(idt);arrayfree(idt,3);
      yy=atoi(idt);
      y = yy1-yy; m = mm1-mm; d = dd1-dd;
      ret = (12*y + m)*30 + d;
      if(ret > 30*maxretperiod) { fp = ret- 30*maxretperiod; bfine = 1*fp;}
      else { bfine=0;}
      cout  << "\nFine on the book titled '" << issuedbook[n].getTitle() << "' is Rs. " << bfine;
      fine=fine+bfine;
    }
  
  if(numbooks>0)
    {
      cout  << "\nTotal Fine on " << numbooks << " book(s) still in your account \n";
      cout << "and the returned book(s),if any, is Rs. " << fine <<"\n\n";
    }
  else
    { 
      if(fine>0) cout  << "\nTotal Fine on the returned book(s) is Rs. " << fine <<"\n\n"; 
      else  cout  << "\nYour account is empty .\n"; 
    }
  updateUserDatabase(ufile,*this);
  ufile.close();
}


void user::calcRetDate(books &ibook)
{
  int dd,mm,yy,dd1,mm1,yy1;
  char idt[10],rdt[10];
  strcpy(idt,ibook.idate);
  dd=atoi(idt);arrayfree(idt,0);
  mm=atoi(idt);arrayfree(idt,3);
  yy=atoi(idt);
  mm1=mm+maxretperiod ; dd1=dd;
  if(mm1>12) { mm1-=12; yy1=yy+1; }
  else yy1=yy;
  
  rdt[0]=(dd1/10)+48;rdt[1]=(dd1%10)+48;rdt[2]='/';
  rdt[3]=(mm1/10)+48;rdt[4]=(mm1%10)+48;rdt[5]='/';
  rdt[6]=(yy1/1000)+48;rdt[7]=((yy1%1000)/100)+48;
  rdt[8]=(((yy1%1000)%100)/10)+48;rdt[9]=(((yy1%1000)%100)%10)+48;
  rdt[10]='\0';
  strcpy(ibook.rdate,rdt);
}


void user::checkouts()
{
  cout << "\n------------------------ Checkouts -----------------------\n"; 
  int i;
  if(numbooks >0)
    {
      for(i=0;i<numbooks;i++)
	{
	  issuedbook[i].issuedisplay();
	  cout << "Issue Date :" << issuedbook[i].idate;
	  cout << "\nDue Return Date :" << issuedbook[i].rdate; cout <<"\n";
	}      
    }
  else
    cout << "\nCurrently Your Book Account is Empty\n";
}


void writeToUserDatabase(fstream &ufile,user &libuser)
{
  cout << "\n--------------------- writeToUserDatabase  ---------------------\n"; 
  ufile.seekp(0,ios::end);
  ufile.clear();
  if(!ufile) { cout <<"\nCould not open 'userfile.dat' for writing.\n"; return; }
  ufile.write((char *)&libuser,sizeof(libuser));
}


void user::issueBook()
{
  cout << "\n----------------------- issueBook -------------------------\n";
  int i=0;
  char btitle[max],bauthor[max],baccno[max],id[max],c;
  enum usertype utype;
  user libuser,u;books temp;
  fstream ufile("userfile.dat",ios::in|ios::out);
  fstream bfile("booksfile.dat",ios::in|ios::out);
  bool clearissue=true;
  
  cout << "\nEnter your ID (In case of a new outsider enter 'no'):";
  cin >> id;cout << id << endl;
  libuser=u;
  if(!ufile) { cout << "\nCould not open 'userfile.dat' !\n"; return; }
  if(searchUserDatabase(ufile,id,libuser))
    {
      cout << "\nUser with this ID found in the User Database .\n";
      libuser.userInfoDisplay();
      utype=libuser.usr; 
    }
  else if(strcmp(id,"no")==0)
    {
      utype=outsider;libuser.usr=outsider;
    }
  else 
    {
      cout << "\nNo User with this ID found in the User Database.\n";
      cout << "\nAre you an outsider (y/n):";
      char c; cin >> c;cout << c <<endl;
      if(c!='y'){return;}
      else utype=outsider;
    }
  switch(utype)
    {
    case faculty:
      libuser.setMaxbooks(10);
      libuser.setMaxRetPeriod(6);
      cout << "\nUser is a " << usrtype[utype] ;
      break;
    case staff:
      libuser.setMaxbooks(5);
      libuser.setMaxRetPeriod(1);
      cout << "\nUser is a " <<  usrtype[utype] ;
      break;
    case UG:
      libuser.setMaxbooks(3);
      libuser.setMaxRetPeriod(2);
      cout << "\nUser is a " <<  usrtype[utype] << " student \n" ;
      break;
    case PG: 
      libuser.setMaxbooks(4);
      libuser.setMaxRetPeriod(3);
      cout << "\nUser is a " <<  usrtype[utype] << " student \n" ;
      break;
    case RS:
      libuser.setMaxbooks(8);
      libuser.setMaxRetPeriod(6);
      cout << "\nUser is a " <<  usrtype[utype] ;
      break;
    case MS:
      libuser.setMaxbooks(4);
      libuser.setMaxRetPeriod(3);
      cout << "\nUser is a " <<  usrtype[utype] << " student \n" ;
      break;      
    case outsider:  
      libuser.setMaxbooks(1);
      libuser.setMaxRetPeriod(1);
      
      if(strcmp(id,"no")==0)	cout << "\nUser is a new " <<  usrtype[utype] ;
      else
	cout << "\nUser is a " <<  usrtype[utype] ;
      cout << "\nDo you have proper authorization letter ?(y/n)";
      cin >> c;cout << c <<endl;
      if(c!='y')
	{
	  cout << " \nSorry you are not authorized to issue books !\n";
	  cout << "contact proper authorized user to issue books !\n";
	  clearissue=false; return;
	}
      else if(libuser.ID[0]=='o') { cout <<"\noutsider exists.\n"; break;}
      else
	{
	  cout << "\nDo you want to create a account ? (y/n) :";
	  char ac;cin >>ac;cout <<ac <<endl;
	  if(ac=='y')
	    {
	      getchar();
	      cout << "\nEnter your name :";
	      input(libuser.name); cout << libuser.name;
 	      char outid[3],oid[max];
	      strcpy(outid,"out");
	      sprintf(oid,"%d",numoutsider+1);
	      strcat(outid,oid);
	      libuser.setID(outid);
	      libuser.setDept("N/A");
	      libuser.setMaxRetPeriod(1);
	      cout << "\nFor further communication please use the following ID :" << outid;
	      cout << "\nYour profile information is as follows:\n";
	      libuser.userInfoDisplay();
	      writeToUserDatabase(ufile,libuser);
	    }
	}
      break;
    default:
      cout << "\nwrong entry\n";
      clearissue=false;
      break;
    }
  
  *this=libuser;//assigning the record of found user to current user records
  int pos =userGetpos(ufile,ID);
  if(pos >0)
    {
      cout << "\nRecord No :"<< pos <<endl;
      cout << "You have currently " << numbooks << " books in your account\n";
    }
  else{ cout << "\nNo User with this Record found in the database.\n";  return;}
  if(numbooks< maxbooks)
    {
      int curmaxissue,numissue;
      do
	{
	  cout << "\nEnter the number of books you want to issue:";
	  cin >> numissue; cout << numissue <<endl;
	  curmaxissue= maxbooks-numbooks;
	  
	  if(numissue > curmaxissue)                //checking the quota of books of the user
	    { 
	      cout << "You have currently " << numbooks << " books in your account ";
	      cout << "You cannot issue more than  " << curmaxissue << " books  at this time\n\n";
	      clearissue=false;
	    }
	}	while(numissue > curmaxissue);
      
      int n=numissue; //no of books the user is currently issuing (after checking the quota constraint)
      int num=numbooks;
      cout << "\nCurrent no. of books in account :" << numbooks << endl;
      
      for(int j=0;j<numissue;j++)
	{
	  cout << "\n* Book " << num+1 << " *" <<endl;
	  n++;	  
	  cout << "\nEnter the Title of the book:";getchar();
	  input(btitle);cout << btitle;
	  temp.setTitle(btitle); i=0;
	  
	  cout << "\nEnter the Author of the book:"; 
	  input(bauthor);cout << bauthor;
	  temp.setAuthor(bauthor);
	  
	  cout << "\nEnter the Accession number of the book:";
	  input(baccno);cout << baccno;
	  temp.setAccNo(baccno);
	  temp.issuedisplay();
	  
	  if(!searchBookDatabase(temp)) { clearissue=false; }
	  if(clearissue)
	    {
	      cout << "\nA book with the given Title,Author & Accession number has been found\n"; 
	      issuedbook[num]=temp;
	      issuedbook[num].issuedisplay();
	      issuedbook[num].setAvail(0);
	      updateBookDatabase(bfile,issuedbook[num]);
	      
	      cout << "\nEnter the issue date (dd/mm/yyyy) :";
	      cin >> issuedbook[num].idate ; cout << issuedbook[num].idate << endl;
	      calcRetDate(issuedbook[num]);//calculating the due date of the book;
	      num++;
	      numbooks++;//updating total no. of books in the users account
	      cout << "\nBook issued ...\n";
	      cout << "\nCurrent no. of books in the account :" << numbooks << endl;
	      
	      libuse++;
	      updateUserDatabase(ufile,*this);
	      cout << "\nRecord with the ID " << ID << " has been updated.\n"; 
	    }      
	  else
	    {
	      cout << "\nThe book you requested cannot be issued .";
	      cout << "\nThis is because either you have entered wrong data or,\n";
	      cout << "the book doesn't exist in the library or, the copy is already issued.\n";
	    }
	}
      
      cout << "\nYou have currently the following books in your account :\n";
      checkouts(); cout <<endl;
    }
  else
    {
      cout << "\nYour account is already full .\n";
      cout << "You cannot issue any further books .\n";
    }
  ufile.close();
  bfile.close();
}


/******************************************************************************************

                                        PHASE - III

******************************************************************************************/


void user::returnBook()
{
  cout << "\n-------------------------- returnBook ----------------------------\n";
  fstream bfile("booksfile.dat",ios::in|ios::out);
  fstream ufile("userfile.dat",ios::in|ios::out);
  books b;char acc[max];
  int i;char ch;user  u;
  cout << "\nEnter your ID :";
  cin >> ID;cout << ID;
  if(searchUserDatabase(ufile,ID,*this))
    {
      userInfoDisplay(); checkouts();
    }
  else{ cout << "\nUser with this ID not found in the database.\n"; return; }
  int j=0,numretbk=0,numb=numbooks;char rdate[10];float fn=0;
  do
    {
      if(numbooks >0)
	{
	  cout << "\nEnter the Accession number of the book you want to return:";
	  cin >> acc;cout << acc << endl;
	  for(i=0;i<numb;i++)
	    {
	      if(strcmp(issuedbook[i].getAccNo(),acc)==0)
		{
		  issuedbook[i].setAvail(1);
		  cout << "\nYou are returning the following book :";
		  issuedbook[i].issuedisplay();
		  updateBookDatabase(bfile,issuedbook[i]);
		  
		  cout << "\nEnter the return date (dd/mm/yyyy) :";
		  cin >> rdate;cout << rdate;
		  
		  cout << "\nBook with Accesion no. " << issuedbook[i].getAccNo() << " has been returned\n";
		  numretbk++;
		  calcFine(rdate);
		  if(fine >0)
		    cout <<"\nPlease pay the fine for the book you returned before you leave.\n"; 
		  fine=0; numbooks-=1;
		  updateUserDatabase(ufile,*this);
		  issuedbook[i]=b;
		  fn=fine;cout << "fine: " <<fn;
		  fine=0;
		}
	    }
	  
	  for(i=0;i<numb;i++)
	    {
	      if(issuedbook[i].checkAvail()!=1)
		{
		  u.issuedbook[j]=issuedbook[i];
		  j++;
		}
	    }
	  
	  if(numretbk==0){ cout << "\nNo books with this Accession number found in your account.\n";return;}
	  cout << "\nDo you want to return more books (y/n):";
	  cin  >>ch ; cout << ch;
	}
      else { cout << "\nYou have no Books in your account \n";return; }
    }while(ch!='n');
  
  delete [] issuedbook;
  for(i=0;i<numb;i++) { issuedbook[i]=u.issuedbook[i];}
  updateUserDatabase(ufile,*this);
  ufile.close();
  bfile.close();
}


void user::checkAccount()
{
  char pdt[10]; 
  fstream ufile("userfile.dat",ios::in);
  cout << "\nEnter your ID :";
  cin >> ID;cout << ID <<endl;
  if(searchUserDatabase(ufile,ID,*this))
    {
      libuse++;
      updateUserDatabase(ufile,*this);	
      userInfoDisplay();
      checkouts();
      cout<<"\nEnter present date (dd/mm/yyyy):";
      cin >> pdt;cout << pdt <<endl;
      calcFine(pdt);
    }
  else
    {
      cout <<"\nNo User with this ID found in the database.\n";
    } 
  ufile.close();
}


void deleteUserRecord(char id[])
{
  user u;
  fstream ftemp("temp",ios::out);
  fstream ufile("userfile.dat",ios::in|ios::out);  
  int pos=userGetpos(ufile,id);
  if(pos>0)//if the record exists
    {
      cout << "\nRecord No :"<< pos <<endl;
      int position=(pos-1)*sizeof(user);
      ufile.seekg(position);//pointing to the position of record to be deleted
      ufile.read((char *)&u,sizeof(u));
      u.userInfoDisplay();
      if(u.getFine()>0)
	{
	  cout << "\nUser has still a fine of Rs. " << u.getFine() << " due.\n";
	  cout << "\nUser record cannot be deleted unless all dues are cleared.\n"; return;
	}
      else
	{
	  int i=1;
	  ufile.seekg(0);//start of file
	  if(pos>1)//if first record is not to be deleted
	    do
	      {
		ufile.read((char *)&u,sizeof(u));
		ftemp.write((char *)&u,sizeof(u));i++;
	      }while(i<pos);
	  
	  //skipping the record to be deleted
	  ufile.read((char *)&u,sizeof(u));
	  while(ufile.read((char *)&u,sizeof(u)))//from current location to end of file
	    {
	      ftemp.write((char *)&u,sizeof(u));
	    }
	  
	  ftemp.close();//closing the temp file
	  ufile.close();//closing the original file
	  
	  remove("userfile.dat");//removing the original file
	  rename("temp","userfile.dat");//renaming temp file to original file
	  
	  cout << "\nRecord with ID " << id << " has been deleted\n";
	}
    }
  else
    cout << "\nRecord with the ID " << id <<" not found\n";
}


/******************************************************************************************

                                        PHASE - IV

******************************************************************************************/

void LibStatReport()
{
  cout << "\n------------------ LibStatReport --------------------\n\n";
  ifstream ufile("userfile.dat");
  ifstream bfile("booksfile.dat");
  ifstream jfile("journalsfile.dat");
  
  int totaluser=0,lumax,tbooks=0,tjrnls=0;
  user u,u1,stu1[umax],stu2[umax],stu3[umax];
  books bk;journals jrnl;
  lumax=0;usertype ut;
  int i,j=0,k=0,m=0,numout=0;float pb=0,pj=0;

  while(ufile.read((char *)&u,sizeof(u)))
    {
      totaluser++;
      if(lumax <u.getLibuse())
	{
	  lumax=u.getLibuse();
	  u1=u;
	}
      ut=u.getUserType();
      if(ut==UG ||ut==PG ||ut==RS ||ut==MS)
	{
	  if(u.getLibuse() > AvgLibuse) { stu1[j]=u;j++;}
	  if(u.getMaxbooks()==u.getNumbooks()) { stu2[k]=u;k++;}
	  if(u.getNumbooks()==0) { stu3[m]=u;m++;}
	}
      if(ut==outsider) numout++;
    }
  while(bfile.read((char *)&bk,sizeof(bk))) { pb = pb+bk.getPrice(); tbooks++; }
  while(jfile.read((char *)&jrnl,sizeof(jrnl))) { pj=pj+jrnl.getPrice(); tjrnls++; }
  if(totaluser>0) totaluser--; if(tbooks>0) tbooks--;  if(tjrnls>0) tjrnls--; 
  cout << "\nThere are " << tbooks << " Books in the library\n";
  cout << "Total Price of the Books is Rs. :" << pb <<endl;
  cout << "\nThere are " << tjrnls << " Journals in the library\n";
  cout << "Total Price of the Journals is Rs. :" << pj <<endl;
  cout << "\nThere are " << totaluser << " users of the library\n";  
  cout << "\nThere are " << numout << " outsiders using the library\n"; 
  cout << "\nThe Students who uses the library more frequently :\n";
  for(i=0;i<j;i++){ cout << stu1[i].getID() << endl;}
  cout << "\nThe User who used the library most frequently : " << u1.getID() <<endl;
  
  cout << "\nThe Students whose account is currently full:\n";
  for(i=0;i<k;i++){ cout << stu2[i].getID() << endl;}
  
  cout << "\nThe Students whose account is currently empty:\n";
  for(i=0;i<m;i++){ cout << stu3[i].getID() << endl;}
  ufile.close();
}


/******************************************************************************************

                                           MAIN

******************************************************************************************/

int main()
{
  cout << "\n\n*************** Welcome To The Library Automation System ***************\n\n";
  user usr; char cmain;
  do
    {
      cout << "\n************* MAIN MENU ***************\n\n";
      cout << "0.(Q)uit The Library Automation System\n";
      cout << "1.(A)dministrator Mode" << endl;
      cout << "2.(U)ser Mode" << endl;
      cout << "\nMode:";
      char cadmin,cuser;
      cin >> cmain;cout << cmain<<endl;
      switch(cmain)
	{
	case '0':case 'q':case 'Q':
	  cout << "\nQuiting Main program ...\n";
	  exit(0);
	case '1':case 'a':case 'A':
	  do
	    {
	      cout << "\n***************** Administrator mode ***************** \n";
	      cout << "0.(Q)uit Administrative Mode"<<endl;
	      cout << "1.Create (B)ooks Database" << endl;
	      cout << "2.Create (J)ournals Database" << endl;
	      cout << "3.Create (U)sers Database" << endl;
	      cout << "4.Create (V)endors Database"<<endl;
	      cout << "5.(D)elete User Record" << endl;
	      cout << "\nchoice:";
	      cin >> cadmin;cout << cadmin <<endl;
	      switch(cadmin)
		{
		case '0':case 'q':case 'Q':
		  cout << "Returning to Main Menu ...\n"; 
		  break;
		case '1':case 'b':case 'B':
		  createBooksDatabase();
		  cout << "\nBooks Database created ...\n";
		  break;
		case '2':case 'j':case 'J':
		  createJournalsDatabase();
		  cout << "\nJournals Database created ...\n";
		  break;
		case '3':case 'u':case 'U':
		  createUserDatabase();
		  cout << "\nUsers Database created ...\n";
		  break;
		case '4':case 'v':case 'V':
		  createVendorDatabase();
		  cout << "\nVendors Database created ...\n";
		  break;
		case '5':case 'd':case 'D':
		  cout << "\nEnter User's ID to delete from database: ";
		  char id[max];
		  cin >> id;cout << id;
		  deleteUserRecord(id);
		  break;
		default:
	 	  cout << "\nWrong entry ,enter any choice from 0-5\n";
		  break;
		}
	    }while(cadmin!='0' && cadmin!='q');
	  break;
	case '2':case 'u':case 'U':
	  do
	    {
	      cout << "\n********************* User mode *********************\n";
	      cout << " 0.(Q)uit User Mode" << endl;
	      cout << " 1.Book/Journal Requisition (F)orm " << endl;
	      cout << " 2.Book (I)ssue" << endl;
	      cout << " 3.Book (R)eturn" << endl;
	      cout << " 4.Check Your (A)ccount " <<endl;
	      cout << " 5.Some (S)tatistical Reports of the Library." <<endl;
	      cout << "\nchoice:";	      
	      cin >> cuser;cout << cuser<<endl;
	      switch(cuser)
		{
		case '0':case 'q':case 'Q':
		  cout << "Returning to Main Menu ...\n"; 
		  break;  
		case '1':case 'f':case 'F':
		  biblioRequest();
		  break;
		case '2':case 'i':case 'I':
		  usr.issueBook();
		  break;
		case '3':case 'r':case 'R':
		  usr.returnBook();
		  break;
		case '4':case 'a':case 'A':
		  usr.checkAccount();
		  break;
		case '5':case 's':case 'S':
		  LibStatReport();
		  break;
		default:
		  cout << "Wrong entry,enter any choice from 0-5\n";
		  break;
		}	
	    }while(cuser!='0' && cuser!='q');
	  break;
	default:
	  cout << "\nWrong entry ,enter any choice from 0-2 \n";
	  break;
	}
    }while(cmain!='0' && cmain!='q');
}
