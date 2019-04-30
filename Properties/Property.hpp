
template<typename ObjectType, typename T, typename Tag = void>
struct Property
{
	typedef T value_type;
	value_type Get();
	void Set(value_type t);

	Property() { }
	Property(value_type init) { Set(init); }
	Property(const Property & src) {
		Set(const_cast<Property&>(src).Get());
	}

	Property & operator=(const Property & src)
	{
		Set(const_cast<Property&>(src).Get());
		return *this;
	}

	value_type operator*() { return Get(); }

	/*
		Returns the object containing this property.

		This assumes that the "this" pointer refers to a field inside the object.
		The address of the object will always be a fixed offset away from the
		address of the property. This delta is a compile-time constant, which
		makes the code efficient.
	*/
	template<Property ObjectType::*Member>
	ObjectType & Object()
	{
		return *reinterpret_cast<ObjectType*>(reinterpret_cast<char*>(this) - reinterpret_cast<char*>(&((ObjectType*)nullptr->*Member)));
	}

	operator value_type() { return Get(); }

	Property & operator=(value_type t) { Set(t); return *this; }
};

template<typename Tag>
class PropertyTraits;

template<typename TraitsType>
class Property2
{
public:
	typedef typename TraitsType::value_type value_type;

	value_type Get() const
	{
		return PropertyTraits<TraitsType>::Get(*this);
	}

	value_type operator*() const { return Get(); }
};

#define DECLARE_PROPERTY(Tag, Type) struct Tag { typedef Type value_type; };

#define DEFINE_PROPERTY2(Object,Tag,Field,Getter,Setter) \
	template<> class PropertyTraits<Tag> : \
		public BaseTraits<Tag, Object, &Object::Getter, &Object::Setter, &Object::Field> { };

#define DEFINE_PROPERTY(Object,Tag,Field) DEFINE_PROPERTY2(Object,Tag,Field,get_##Field,set_##Field)

template<typename Tag, typename ObjectType, typename Tag::value_type(ObjectType::*Getter)() const,
	void(ObjectType::*Setter)(typename Tag::value_type), Property2<Tag> ObjectType::*Member>
	class BaseTraits
{
public:
	typedef Tag tag;
	typedef ObjectType object;
	typedef typename Tag::value_type value_type;

	static const ObjectType & Object(const Property2<Tag> & prop)
	{
		return *reinterpret_cast<const ObjectType*>(reinterpret_cast<const char*>(&prop) - reinterpret_cast<const char*>(&((ObjectType*)nullptr->*Member)));
	}

	static inline value_type Get(const Property2<Tag> & prop) {
		return (Object(prop).*Getter)();
	}
};