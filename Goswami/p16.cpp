// Array of objects
// Tips: 
#include<iostream>
using namespace std;

enum disp_type{mono,cga,ega,vga};

class display
{
  int colors;
  enum disp_type dt;
public:
  void set_colors(int num){colors=num;}
  int get_colors(){return colors;}
  void set_type(enum disp_type t){dt=t;}
  enum disp_type get_type(){return dt;}
};

char names[4][5]={"mono","cga","ega","vga"};

main()
{
  display monitors[4];
  monitors[0].set_colors(1);
  monitors[0].set_type(mono);
  monitors[1].set_colors(2);
  monitors[1].set_type(cga);
  monitors[2].set_colors(4);
  monitors[2].set_type(ega);
  monitors[3].set_colors(16);
  monitors[3].set_type(vga);

  for(int i=0;i<4;i++)
    {
      cout<<names[monitors[i].get_type()]<<" has "<<monitors[i].get_colors()<<" colors \n";
    }
}
