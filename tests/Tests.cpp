

#include <Property.hpp>

#undef NDEBUG
#include <cassert>
#include <string>
#include <iostream>

struct PropertySizes
{
	GETTER(PropertySizes, P1, int);
	GETTER(PropertySizes, P2, int);
	GETTER(PropertySizes, P3, int);
	int get_P1() const { return 0; }
	int get_P2() const { return 0; }
	int get_P3() const { return 0; }
};

class PersonWithoutProperties
{
public:
	const std::string & get_Name() const { return name; }
	void set_Name(const std::string&value) { name = value; }
private:
	std::string name;
};

class PersonWithProperties : public PersonWithoutProperties
{
public:
	PROPERTY(PersonWithProperties, Name, const std::string&);
};

class Foo
{
public:
	PROPERTY(Foo, Foo1, int);
	PROPERTY(Foo, Foo2, std::string);
	std::string name;
public:
	int get_Foo1() const { return 1; }
	void set_Foo1(int) { }
	std::string str;
	const std::string & get_Foo2() const { return str; }
	void set_Foo2(const std::string &s) { str = s; }
};

int main()
{
	// Tests the size of the property.
	// This is compiler-specific, however in practice, each property
	// will be allocated 1 byte somewhere in the type.
	{
		// This isn't portable but records what happens in practise.
		assert(sizeof(PropertySizes::P1) == 1);
		assert(sizeof(PropertySizes) == 3);
	}

	// Tests an integer getter
	{
		struct IntGetter
		{
			GETTER(IntGetter, P, int);
			int get_P() const { return 10; }
		} p;

		assert(p.P == 10);
		assert((int)p.P == 10);
		assert(*p.P == 10);
		assert(p.P.Get() == 10);

		// These are compilation errors:
		// auto prop1 = p.P;
		// decltype(p.P) prop2;
	}

	// Tests an integer property
	{
		struct IntProperty
		{
			PROPERTY(IntProperty, P, int);
		private:
			int get_P() const { return p; }
			void set_P(int value) { p = value; }
		private:
			int p;
		} p;

		p.P = 10;
		assert(p.P == 10);
		assert((int)p.P == 10);
		assert(*p.P == 10);
		assert(p.P.Get() == 10);

		p.P.Set(30);
		assert(p.P == 30);

		// These are compilation errors:
		// auto prop1 = p.P;
		// decltype(p.P) prop2;
	}

	// Tests const std::string & property.
	{
		PersonWithProperties p;
		assert(*p.Name == "");
		p.Name = "Fred";
		assert(*p.Name == "Fred");

		// Tests the copy constructor
		auto p2 = p;
		assert(*p2.Name == "Fred");  // The underlying field was copied.

		p2.Name = "Alf";
		p = p2;
		assert(*p.Name == "Alf");  // The underlying field was assigned
	}

	std::cout << "Tests passed\n";
	return 0;
}
