// Properties.cpp : Defines the entry point for the application.
//

#include "Properties.h"
#include "Property.hpp"
#include <string>
#include <cassert>

using namespace std;


//Properties are declared as fields within other classes/structs.

struct Person
{
	// This is a property named "Name", in the struct Person, of type "std::string".
	Property<Person, std::string> Name;

	// This is a property named  "Age", in struct "Person", of type "int".
	// It is initialized the value 13.
	Property<Person, int> Age = 13;
};

// To use properties, access the property as if it were a member variable.
// This works most of the time.

void use_Person()
{
	Person p;
	p.Name = "Fred";
	std::cout << p.Age;

	// Sometimes, you need to use the * operator to read the property correctly.
	std::cout << *p.Name;
}

// To define the behaviour of the getters, you must implement the getter. For example

std::string Property<Person, std::string>::Get()
{
	return "Fred";
}

void Property<Person, std::string>::Set(std::string)
{
}

int Property<Person, int>::Get() { return 12; }

void Property<Person, int>::Set(int x) {}




DECLARE_PROPERTY(AddressTag, const char*)

class UsingProperty
{
public:

	std::string name = "Jo";
	int age = 0;

	Property<UsingProperty, std::string> Name;
	Property<UsingProperty, int> Age;

	void set_Address(const char * s) { address = s; }
	const char * get_Address() { return address.c_str(); }
	void set_Address2(const char * s) { address = s; }
	const char * get_Address2() const { return address.c_str(); }
private:
	std::string address;

public:
	// Note: backing field must be initialized first.
	Property<UsingProperty, const char *> Address = "12 The Road";

	Property2<AddressTag> Address2;
};

DEFINE_PROPERTY(UsingProperty, AddressTag, Address2, get_Address2, set_Address2)


//template<> class PropertyTraits<AddressTag> :
//	BaseTraits<
//		AddressTag,
//		UsingProperty,
//		&UsingProperty::get_Address2,
//		&UsingProperty::set_Address2, 
//		&UsingProperty::Address2
//	>
//{
//};


std::string Property<UsingProperty, std::string>::Get()
{
	return Object<&UsingProperty::Name>().name;
}

void Property<UsingProperty, const char*>::Set(const char *s)
{
	Object<&UsingProperty::Address>().set_Address(s);
}

const char * Property<UsingProperty, const char *>::Get()
{
	return Object<&UsingProperty::Address>().get_Address();
}


void Property<UsingProperty, std::string>::Set(std::string x)
{
	Object<&UsingProperty::Name>().name = x;
}

void Property<UsingProperty, int>::Set(int x)
{
}

int Property<UsingProperty, int>::Get()
{
	return 9;
}

int main()
{
	UsingProperty c;

	cout << c.Name.Get() << endl;

	c.Name.Set("Fred");
	auto x = c.Name.Get();
	c.Name = "Foo";
	cout << x << endl;

	c.Age = 90;
	int y = c.Age;
	cout << y << std::endl;

	assert(*c.Address == std::string("12 The Road"));
	c.Address = "123";
	assert(*c.Address == std::string("123"));

	auto c2 = c;
	assert(*c2.Address == string("123"));

	auto a2 = *c2.Address;
	auto a3 = *c2.Address2;

	cout << "Hello CMake." << endl;
	return 0;
}
