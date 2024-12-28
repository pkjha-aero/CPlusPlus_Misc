// Friend Function
// Tips: Need for a forward reference
#include<iostream>
using namespace std;

class triangle; //Forward Reference

class rectangle
{
  int length,breadth;
  double area;
public:
  friend void compare_area(triangle t,rectangle r);
  void setdim(int l,int b);
  void showdim();
};

class triangle
{
  int base,height;
  double area;
public:
  friend void compare_area(triangle t,rectangle r);
  void setdim(int b,int h);
  void showdim();
};

void compare_area(triangle t,rectangle r)
{
  if(t.area==r.area)
    cout<<"\nAreas of the Triangle and Rectangle are same.\n\n";
  else
    cout<<"\nAreas of the Triangle and Retangle are different.\n\n";
}

void rectangle::setdim(int l,int b)
{
  length=l;
  breadth=b;
  area=l*b;
}
void rectangle::showdim()
{
  cout<<"\n The dimensions of Rectangle:---";
  cout<<"\n Length:"<<length<<" Breadth: "<<breadth<<" Area: "<<area;
}

void triangle::setdim(int b,int h)
{
  base=b;
  height=h;
  area=.5*b*h;
}
void triangle::showdim()
{
  cout<<"\n The dimensions of Triangle:---";
  cout<<"\n Base: "<<base<<" Height: "<<height<<" Area: "<<area;
}
main()
{
  triangle t;
  rectangle r;
  t.setdim(10,20);
  r.setdim(10,20);
  t.showdim();
  r.showdim();
  compare_area(t,r);
  
}
