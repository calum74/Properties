/*
	This is a lightweight mechanism to add C#-style properties to structs
	and classes. This can make the interface to the class nicer by making getters
	and setters field-like. For example:

	class Person
	{
	public:
	    PROPERTY(Person, Name, const std::string&);
		GETTER(Person, Adult, bool);
		PROPERTY(Person, Age, int);
	private:
	    const std::string &get_Name() const;
		void set_Name(const std::string&);
		int get_Age() const;
		void set_Age(int);
		bool get_Adult() const;
	};

	Person p;
	p.Name = "Fred";
*/

#pragma once

#define PROPERTY(Outer, Name, Type) \
	struct Name##_type { \
		const Outer & Object() const { return *reinterpret_cast<const Outer*>(reinterpret_cast<const char*>(this) - reinterpret_cast<const char*>(&((Outer*)nullptr)->Name)); } \
		Outer & Object() { return *reinterpret_cast<Outer*>(reinterpret_cast<char*>(this) - reinterpret_cast<char*>(&((Outer*)nullptr)->Name)); } \
		Type Get() const { return Object().get_##Name(); } \
		void Set(Type value) { Object().set_##Name(value); } \
		Name##_type & operator=(Type value) { Set(value); return *this; } \
		operator Type() const { return Get(); } \
		Type operator*() const { return Get(); } \
		Name##_type & operator=(const Name##_type & src) { Set(src.Get()); return *this; } \
    private: \
        friend Outer; \
        Name##_type() { } \
        Name##_type(const Name##_type&) { } \
	} Name;

#define GETTER(Outer, Name, Type) \
	struct Name##_type { \
		const Outer & Object() const { return *reinterpret_cast<const Outer*>(reinterpret_cast<const char*>(this) - reinterpret_cast<const char*>(&((Outer*)nullptr)->Name)); } \
		Type Get() const { return Object().get_##Name(); } \
		operator Type() const { return Get(); } \
		Type operator*() const { return Get(); } \
    private: \
        friend Outer; \
        Name##_type() { } \
        Name##_type(const Name##_type&) { } \
	} Name;
