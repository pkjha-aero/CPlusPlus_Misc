// Virtual function
// Tip: 
#include<iostream>
#include<cstring>
using namespace std;

class media
{
protected:
  char title[80];
  double price;
public:
  void set_price(double d);
  void set_title(char s[]);
  virtual void display();
};
class books:public media
{
  int pages;
public:
  void set_pages(int i);
  void display();
};
class caset:public media
{
  int playtime;
public:
  void set_pt(int i);
  void display();
};

void media::set_title(char s[])
{
  strcpy(title,s);
}
void media::set_price(double d)
{
  price=d;
}
void media::display()
{
  cout<<"Title: "<<title<<"  Price: "<<price<<endl;
}
void books::set_pages(int i)
{
  pages=i;
}
void books::display()
{
  cout<<"Title: "<<title<<"  Price: "<<price<<"  Pages :"<<pages<<endl;
}
void caset::set_pt(int t)
{
  playtime=t;
}
void caset::display()
{
  cout<<"Title: "<<title<<"  Price: "<<price<<"  Playtime :"<<playtime<<endl;
}

main()
{
  media a,*p;
  books b;
  caset c;
  p=&a;
  p->set_title("Functional Analysis");
  p->set_price(235.68);
  p->display();
  p=&b;
  p->set_title("Kreyszig");
  p->set_price(472.5);
  b.set_pages(1143); // only derived members cab be accessed by base pointer, so using object
  p->display();
  p=&c;
  p->set_title("Mind Power Music");
  p->set_price(127.5); 
  c.set_pt(75); // only derived members cab be accessed by base pointer, so using object
  p->display();
}
