
#include "Property.hpp"
#include <string>
#include <cassert>

// This is a class that contains properties.
class Person
{
public:

	// This is a property named  "Age", in struct "Person", of type "int".
	PROPERTY(Person, Age, int);

	// These are readonly properties.
	GETTER(Person, Adult, bool);
	GETTER(Person, YearsToRetirement, int);

protected:
	// This is a protected property just because.
	PROPERTY(Person, Name, const char *);

private:
	// This is the backing field for the Age property.
	int age = 0;

	// This is a backing field for the Name property.
	std::string name;

	// This is the implementation of the getters and setters.
	int get_Age() const { return age; }

	// Add validation to the property.
	void set_Age(int a) { 
		if (a < 0 || a>150) throw std::exception("Invalid age");
		age = a;
	}

	// Naturally, the class can use its own properties (i.e. Age).
	bool get_Adult() const { return Age >= 18; }

	// The property type can have a different type to its underlying field.
	const char * get_Name() const { return name.c_str(); }
	void set_Name(const char * n) { name = n; }

	// This is a virtual getter.
	virtual int get_YearsToRetirement() const
	{
		return 65 - Age;
	}
};


int main()
{
	//
	Person p;

	p.Age = 69;
	assert(p.Adult);
	p.Age = 17;
	assert(!p.Adult);
	assert(p.YearsToRetirement == (65 - 17));

	// Copying a person.
	auto p2 = p;
	assert(p2.Age == 17);
	return 0;
}