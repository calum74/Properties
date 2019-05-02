
// #include "Properties.h"
#include "Property.hpp"
#include <string>
#include <cassert>
#include <iostream>

class Person2
{
public:
	int value;

	PROPERTY(Person2, Foo, int);
	PROPERTY(Person2, Name, const std::string&);
	GETTER(Person2, IsAdult, bool);
	PROPERTY(Person2, Age, int);

private:
	void set_Foo(int x) { value = x; }
	int get_Foo() const { return value; }
	std::string name;
	void set_Name(const std::string &s) { name = s; }
	const std::string & get_Name() const { return name; }

	int age;
	int get_Age() const { return age; }
	void set_Age(int a) { age = a; }
	virtual bool get_IsAdult() const { return age >= 18; }
};

struct Foo1
{
	int p;
};

struct Foo2
{
	int p;
	PROPERTY(Foo2, P, int);
	int get_P() const {
		return p;
	}

	void set_P(int v) { p = v; }

	GETTER(Foo2, P2, int);
	int get_P2() const {
		return p;
	}
	GETTER(Foo2, P3, int);
	int get_P3() const {
		return p;
	}

};


int main()
{
	std::cout << sizeof(Foo1) << " " << sizeof(Foo2) << std::endl;
	Person2 p2;
	p2.Foo.Set(8);
	auto x = p2.Foo.Get();
	p2.Foo = 5;
	assert(p2.Foo == 5);
	std::cout << p2.Foo;
	p2.Name = "Fred";
	// auto name = p2.Name;
	auto & name = p2.Name;
	name = "Bread";

	for (int i = 0; i < 1000; ++i)
	{
		p2.Foo = p2.Foo + i;
	}

	p2.Age = 19;
	assert(p2.IsAdult);
	bool a = p2.IsAdult;

	std::cout << p2.Foo << std::endl;

	auto p3 = p2;

	return 0;
}
