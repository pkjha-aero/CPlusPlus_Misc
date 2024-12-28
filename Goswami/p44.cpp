/*
 var          function      compiler response
static        static        compiles well
static        non-static      "
non-static    static        static func can access only static var
non-static    non-static    no problem if main written well
*/
#include<iostream>
using namespace std;

enum access_t{shared,in_use,locked,unlocked};
char types[4][10]={"shared","in_use","locked","unlocked"};

class access
{
  static enum access_t acs;
public:
  static void set_access(enum access_t a){acs=a;}
  static enum access_t get_access(){return acs;}
};
enum access_t access::acs; //globally defined whenever static

main()
{
  access obj1,obj2;
  obj1.set_access(locked);
  obj2.set_access(shared);
  cout<<types[obj1.get_access()]<<endl;
  cout<<types[obj2.get_access()]<<endl;
  obj2.set_access(in_use);
  cout<<types[access::get_access()]<<endl;
  //cout<<types[obj2.get_access()]<<endl;
}
