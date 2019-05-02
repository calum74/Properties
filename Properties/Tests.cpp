

#include "Property.hpp"
#include <cassert>
#include <string>

class Foo
{
	friend Getter<Foo, int>;
	friend Getter<Foo, int, struct Foo3Tag>;
	friend Setter<Foo, int>;
	int foo_value;

	friend Getter<Foo, const std::string&>;
	friend Setter<Foo, const std::string&>;
	std::string name;
public:
	Setter<Foo, int> Foo1;
	Getter<Foo, int> Foo2;
	Property<Foo, int, struct Foo3Tag> Foo3;

	Property<Foo, const std::string&> Name = "Fred";
};

int Getter<Foo, int>::Get() const
{
	return Object<&Foo::Foo2>().foo_value;
}

void Setter<Foo, int>::Set(int v)
{
	Object<&Foo::Foo1>().foo_value = v;
}

int Getter<Foo, int, Foo3Tag>::Get() const
{
	return Object<&Foo::Foo3>().Foo2;
}

void Setter<Foo, int, Foo3Tag>::Set(int x)
{
	Object<&Foo::Foo3>().Foo1 = x;
}


const std::string & Getter<Foo, const std::string &>::Get() const
{
	return Object<&Foo::Name>().name;
}

void Setter<Foo, const std::string&>::Set(const std::string & s)
{
	Object<&Foo::Name>().name = s;
}

void main()
{
	Foo foo;
	foo.Foo1 = 12;
	assert(foo.Foo2 == 12);
	assert(foo.Foo3 == 12);

	assert(*foo.Name == "Fred");

	auto foo2 = foo;
	foo2.Name = "Ned";
	assert(*foo.Name == "Fred");
	assert(*foo2.Name == "Ned");
}
