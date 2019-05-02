

#include <Property.hpp>
#include <cassert>
#include <string>

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

void main()
{
	Foo foo;
	foo.Foo2 = "Hello";
	assert(*foo.Foo2 == "Hello");
}
