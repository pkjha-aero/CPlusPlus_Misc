// Inheritance
// Tips: In general, don't create object of the base class
#include<iostream>
using namespace std;

class road_vehicle
{
  int wheels;
  int passengers;
public:
  void set_wheels(int num);
  int get_wheels();
  void set_pass(int num);
  int get_pass();
};

class truck:public road_vehicle
{
  int cargo;
public:
  void set_cargo(int num);
  int get_cargo();
  void show();
};

enum type{car,van,wagon};

class automobile:public road_vehicle
{
  enum type car_type;
public:
  void set_type(enum type t);
  enum type get_type();
  void show();
};

void road_vehicle::set_wheels(int num)
{
  wheels=num;
}
int road_vehicle::get_wheels()
{
  return wheels;
}
void road_vehicle::set_pass(int num)
{
  passengers=num;
}
int road_vehicle::get_pass()
{
  return passengers;
}

void truck::set_cargo(int num)
{
  cargo=num;
}
int truck::get_cargo()
{
  return cargo;
}
void truck::show()
{
  cout<<"\nTruck---\nWheels:"<<get_wheels();
  cout<<"\nPassengers:"<<get_pass();
  cout<<"\nCargo Capacity:"<<cargo;
}

void automobile::set_type(enum type t)
{
  car_type=t;
}
enum type automobile::get_type()
{
  return car_type;
}
void automobile::show()
{
  cout<<"\nAutomobile---\nWheels:"<<get_wheels();
  cout<<"\nPassengers:"<<get_pass();
  cout<<"\nType :";
  switch(car_type)
    {
    case van:
		cout<<"Van";
      	break;
    case car:
		cout<<"Car";
      	break;
    case wagon:
		cout<<"Wagon";
    }
}

main()
{
  truck t;
  automobile a;
  t.set_wheels(8);
  t.set_pass(4);
  t.set_cargo(1500);
  t.show();
  a.set_wheels(4);
  a.set_pass(4);
  a.set_type(car);
  a.show();
  cout<<"\n";
}
