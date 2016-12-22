#include <iostream>
#include <map>
#include <cstring>

using namespace std;


class Box {
  public:
    double length; //Length of box
    double width;  //Width of box
    double height; //Height of box  
    double getVolume(void);
};




typedef int feet;
typedef int inch;
typedef struct ballin ball_t;

struct ballin {

  string ball_type;
  int num_balls;
};

// Variable declaration to make vars available when linking files
extern int a, b;
extern int g;
extern float f;

enum color{red='r', green=5, blue=3} c;

//map<color,string> Full;
//Full[red] = red;


int add(int x, int y);


int add(int x, int y) {
	return x+y;
}

double Box::getVolume(void) {
  return length * width * height;
}

int main() {
	feet f1 = 2;
	inch i1 = 3;
	cout << f1 << endl << endl;

	c = red;

	cout <<  char(c) << endl << endl;



  int d = 3, e = 4;
  char x = 'x';

  cout << x << endl;

  ball_t* B = new ball_t;

  B->ball_type = "Basketball";
  B->num_balls = 5;

  cout << B->ball_type << endl << endl;
  	//If not initialized, variables w/static storage
  	//automatically initialized with NULL --> all bytes have value 0

  	//Initial value of other vars is undefined

  	//lvalue - expressions that refer to a memory location
  		//i.e. variables
  	//rvalue - data value that is stored at some address in memory
  		//-cannot assign value to rvalue
  		//i.e. numeric literals

  //Object oriented
  //Class functions can be defined inside class or outside using "::" 
    //- scope resolution operator
  /*
    public, private, protected
    constructors, destructors
    copy constructor
    friend function, friend classes, etc
    inline functions
    "this" pointer
    pointers to classes
    static data members and functions
        data members only initialized outside class
        shared by all instances/objects of class
        static functions can only access outside functions or static data members
            don't have access to "this" pointer

    inheritance, base & derived classes, access control and inheritance
    class Derived: public Base1, public Base2, private Base3, protected Base4 {}

    overloading different operators:
        unary, binary, relational, input/output, ++ and --, assignment, function call
        subscripting, class member access ->

    polymorphism: when a function is called, the function that is executed depends
      on the type of object that it is being called with
      -so you can have different implementations of a function in different derived classes
      -virtual keyword in base class function (dynamic linkage / dynamic binding)
      -vs static linkage / static binding
      -if the base class doesn't need the function but derived classes do,
        use pure virtual function
        i.e. virtual int area() = 0
          tells compiler function has no body

    Abstraction: separation between interface and implementation
      accomplished using public, private, protected -- access keywords

    Data encapsulation -- mechanis of bundling data?
      data hiding
      using private is good data encapsulation
      only expose things that need to be exposed

    Interfaces/Abstract classes
      class is made abstract by determining at least one of its functions pure virtual
      abstract classes cannot be used to instantiate objects
      concrete classes - used to instantiate objects


    Compile with -DDEBUG to define debug
    

  */
  Box box1;
  Box box2;

  box1.length = 5.0;
  box1.width = 5.0;
  box1.height = 5.0;

  double volume = box1.length * box1.width * box1.height;

  cout << box1.getVolume() << endl << endl;

  int age;
  cout << "Please enter age:" << endl;
  cin >> age;
  cout << "You are " << age << " years old!" << endl << endl;

  return f1;
}