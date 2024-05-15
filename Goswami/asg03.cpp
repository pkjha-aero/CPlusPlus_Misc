#include<iostream.h>

enum type{wood,steel,plastic,fibre};
char mat[4][10]={"wood","steel","plastic","fibre"};
enum ftype{chair,table,chairtable};

class furniture
{
public:
  int no_legs;
  char color[30];
  enum type mat_type;
  enum ftype fur_type;
  char brand[50];
  void setlegs();
  void setcolor();
  void setmaterial(enum type t);
  void setftype(enum ftype t);
  void setbrand();
  virtual void display();  //use of virtual func, access by base ptr
};
void furniture::setlegs()
{
  cout<<"\nHow many legs are there?";
  cin>>no_legs;
}
void furniture::setcolor()
{
  cout<<"\nWhat is the color of the furniture?";
  cin>>color;
}
void furniture::setmaterial(enum type t)
{
  mat_type=t;
}
void furniture::setftype(enum ftype t)
{
  fur_type=t;
}
void furniture::setbrand()
{
  cout<<"\nWhat is the brand name of the furniture?";
  cin>>brand;
}
void furniture::display()
{
  cout<<"\nThe furniture is a ";
  switch(fur_type)
    {
    case chair:cout<<"CHAIR";
      break;
    case table:cout<<"TABLE";
    }
  cout<<"\nIts made up of "<<mat[mat_type];
  cout<<"\nIts color is "<<color;
  cout<<"\nIt has "<<no_legs<<" legs";
  cout<<"\nIts brand is '"<<brand<<"'"<<endl;
}
class chairs:virtual public furniture
{
public:
  int arm;
  int cushion;
  void setftype();
  void setarm();
  void setcushion();
  void display();

};
void chairs::setftype()
{
  fur_type=chair;
}
void chairs::setarm()
{
  cout<<"\nDoes the chair have arms?(1 for yes ,0 for no)";
  cin>>arm;
}
void chairs::setcushion()
{
  cout<<"\nDoes the chair have cushion?(1 for yes & 0 for no)";
  cin>>cushion;
}
void chairs::display()
{
  cout<<"\nThe furniture is a ";
  switch(fur_type)
    {
    case chair:cout<<"CHAIR";
      break;
    case table:cout<<"TABLE";
    }
  cout<<"\nIts made up of "<<mat[mat_type];
  cout<<"\nIts color is "<<color;
  cout<<"\nIt has "<<no_legs<<" legs";
  cout<<"\nIts brand is '"<<brand<<"'";

    switch(cushion)
      {
      case 1:cout<<"\nThe chair has cushion";
	break;
      case 0:cout<<"\nThe chair doesnot have a cushion";
      }
    switch(arm)
      {
      case 1:cout<<"\nThe chair is armed";
	break;
      case 0:cout<<"\nThe chair is not armed";
      }
    cout<<endl;
}
class tables:virtual public furniture
{
public:
  int drawer;
  int tablecloth;
  int glasscover;
  void setftype();
  void setdrawer();
  void setcloth();
  void setglass();
  void display();
};
void tables::setftype()
{
  fur_type=table;
}
void tables::setdrawer()
{
  cout<<"\nDoes the table have drawer?(1 for yes,0 for no)";
  cin>>drawer;
}
void tables::setcloth()
{
  cout<<"\nDoes the table have tablecloth?(1=yes,0=no)";
  cin>>tablecloth;
}
void tables::setglass()
{
  cout<<"\nDoes the table have glasscover?(1=yes,0=no)";
  cin>>glasscover;
}
void tables::display()
{
  cout<<"\nThe furniture is a ";
  switch(fur_type)
    {
    case chair:cout<<"CHAIR";
      break;
    case table:cout<<"TABLE";
    }
  cout<<"\nIts made up of "<<mat[mat_type];
  cout<<"\nIts color is "<<color;
  cout<<"\nIt has "<<no_legs<<" legs";
  cout<<"\nIts brand is '"<<brand<<"'";
  if(drawer)
    cout<<"\nThe Table has a drawer";
  else
    cout<<"\nThe Table doesn't have a drawer";
  if(tablecloth)
    cout<<"\nThe Table has a table cloth";
  else
    cout<<"\nThe Table doesn't have a tablecloth";
  if(glasscover)
    cout<<"\nThe Table has a glasscover";
  else
    cout<<"\nThe Table doesn't have a glasscover";
  cout<<endl;
}

class diningroom:public chairs,public tables
{
public:
  int no_table;
  int no_chair;
  int pan;
  int plates;
  int spoons;
  void setftype(enum ftype t){fur_type=t;}
  void settable()
  {
    cout<<"\nHow many tables does the dining room have?";
    cin>>no_table;
  }
  void setchair()
  {
    cout<<"\nHow many chairs does the dining room have?";
    cin>>no_chair;
  }
  void setpan()
  {
    cout<<"\nHow many pans does the dining room have?";
    cin>>pan;
  }
  void setplates()
  {
    cout<<"\nHow many plates does the dining room have?";
    cin>>plates;
  }
  void setspoons()
  {
    cout<<"\nHow many spoons does the dining room have?";
    cin>>spoons;
  }
  void display()
  {
    int a,b;
    cout<<"\nThe Dining Room has "<<pan<<" pans,"<<plates<<" plates,"<<spoons<<" spoons";
    cout<<"\nThe DINING ROOM has as furniture ";
    switch(fur_type)
    {
    case chair:no_table=0;cout<<"only "<<no_chair<<"CHAIR(S)";
      break;
    case table:no_chair=0;cout<<"only "<<no_table<<"TABLE(S)";
      break;
    case chairtable:cout<<no_table<<"TABLE(S) & "<<no_chair<<" CHAIR(S)";
    }
  cout<<"\nThe furnitture is made up of "<<mat[mat_type];
  cout<<"\nIts color is "<<color;
  cout<<"\nIt has total "<<no_legs<<" legs";
  cout<<"\nIts brand is '"<<brand<<"'";
  if(fur_type==chair || fur_type==chairtable)
    {
    switch(cushion)
      {
      case 1:cout<<"\nThe chair has cushion";
	break;
      case 0:cout<<"\nThe chair doesnot have a cushion";
      }
    switch(arm)
      {
      case 1:cout<<"\nThe chair is armed";
	break;
      case 0:cout<<"\nThe chair is not armed";
      }
    }
  if(fur_type==table || fur_type==chairtable)
    {
    if(drawer)
      cout<<"\nThe Table has a drawer";
    else
      cout<<"\nThe Table doesn't have a drawer";
    if(tablecloth)
      cout<<"\nThe Table has a table cloth";
    else
      cout<<"\nThe Table doesn't have a tablecloth";
    if(glasscover)
      cout<<"\nThe Table has a glasscover";
    else
      cout<<"\nThe Table doesn't have a glasscover";
    }
  cout<<endl;
  }
};

main()
{
  furniture a,*p;
  tables b;
  chairs c;
  diningroom g;

  a.setftype(chair);
  a.setlegs();
  a.setcolor();
  a.setbrand();
  a.setmaterial(fibre);
  p=&a;
  p->display();  // display function thru base poiter

  b.setftype();  //since it's an object of type table,fur_type=table
  b.setlegs();
  b.setcolor();
  b.setbrand();
  b.setmaterial(plastic);
  b.setglass();
  b.setcloth();
  b.setdrawer();
  p=&b;
  p->display();

  c.setftype();//bein an object of type chair,fur_type=table
  c.setlegs();
  c.setcolor();
  c.setbrand();
  c.setmaterial(steel);
  c.setarm();
  c.setcushion();
  p=&c;
  p->display(); //display fun of d_class thru base ptr

  g.setftype(chair);
  g.setlegs();
  g.setcolor();
  g.setbrand();
  g.setmaterial(wood);
  if(g.fur_type==chair || g.fur_type==chairtable)
    {
      g.setchair();
      g.setarm();
      g.setcushion();
    }
  if(g.fur_type==table ||g.fur_type==chairtable)
    {
      g.settable();
      g.setdrawer();
      g.setcloth();
      g.setglass();
    }
  g.setpan();
  g.setplates();
  g.setspoons();
  p=&g;
  p->display();  //use of base poiter
  cout<<endl;
}
