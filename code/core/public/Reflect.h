#ifndef GEMINI_Reflect_INCLUDE
#define GEMINI_Reflect_INCLUDE
#include "SmartPtr.h"

namespace gemini {

class Object;
class EntityObject;
class Class;
class IList;
class CORE_API Field final
{
	Field(const Field&) = delete;
	Field& operator= (const Field&) = delete;
public:
	Field(const Class& type, Long offset, const Class& cls, const Char* name, Int index = 0, Boolean multiRef = 0);
	~Field();
	
	Boolean getMultiRef() const { return _multiRef; }
	const String& getName() const { return _name; }
	const Class& getClass() const { return _class; }
	const Class& getType() const { return _type; }
	Int index() const { return _index; }
	
	template <class Value> Value get(const Object *object) const;
	template <class Value> void set(Object *object, const Value &value) const;

	template <class Value> Value get(const SmartPtr<EntityObject>& object) const { return get<Value>(object.rawPointer()); }
	template <class Value> void set(SmartPtr<EntityObject>& object, const Value &value) const { return set<Value>(object.rawPointer(), value); }

private:
	Boolean _multiRef;
	Int _index;
	const Class& _type;
	Long _offset;
	const Class& _class;
	String _name;
};
struct CORE_API __register_field__ {
	__register_field__(const Class& type, Long offset, const Class& cls, const Char* name, Int index = 0, Boolean multiRef = 0);
};

template <class Value> Value Field::get(const Object *object) const {
	return *(const Value *)(((const char *)object) + _offset);
}

template <class Value> void Field::set(Object *object, const Value &value) const {
	*(Value *)(((char *)object) + _offset) = value;
}

class Method;
class CORE_API Class final
{
	typedef void* (*PNewInstance)();
	template <typename T>
	static void* create() { return new T; }
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	template<>
	static void* create<void>() { return nullptr; }
	template<>
	static void* create<Object>() { return nullptr; }
	template<>
	static void* create<EntityObject>() { return nullptr; }
	template<>
	static void* create<IList>() { return nullptr; }
	template<>
	static void* create<const IList&>() { return nullptr; }
#endif
	template <typename T, Boolean BEntity>
	struct forTypeImpl {
		static const Class& value() { return T::getClassStatic(); }
	};
	template <typename T>
	struct forTypeImpl<T, false> {
		static const Class& value() { static const Class _class(getName<T>().c_str(), nullptr, create<T>); return _class; }
	};

	Class(const Class& rhs) = delete;
	Class& operator= (const Class& rhs) = delete;
public:
	Class(const Char* name, const Class* superClass, PNewInstance instance);
	~Class();

	static String getName(const Char* name);
	template<typename T>
	static String getName() {
		return getName(typeid(T).name());
	}

	static Int max_limits();
	static Int maxIndex() { return s_maxIndex; }
	Int index() const { return _index; }
	const String& getName() const { return _name; }
	const Class& getSuperClass() const { return *_superClass; }
	Boolean hasSuper() const;
	Boolean isBase(const Class& cls) const;

	operator Int() const { return _index; }

	static const Class& forName(const String& name);
	template <typename T>
	static const Class& forType() { return forTypeImpl<T, std::is_base_of<Object, T>::value>::value(); }
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	template <>
	static const Class& forType<void>() { static const Class _class("void", nullptr, create<void>); return _class; }
	template <>
	static const Class& forType<Boolean>() { static const Class _class("Boolean", nullptr, create<Boolean>); return _class; }
	template <>
	static const Class& forType<Char>() { static const Class _class("Char", nullptr, create<Char>); return _class; }
	template <>
	static const Class& forType<Short>() { static const Class _class("Short", nullptr, create<Short>); return _class; }
	template <>
	static const Class& forType<Int>() { static const Class _class("Int", nullptr, create<Int>); return _class; }
	template <>
	static const Class& forType<Long>() { static const Class _class("Long", nullptr, create<Long>); return _class; }
	template <>
	static const Class& forType<Float>() { static const Class _class("Float", nullptr, create<Float>); return _class; }
	template <>
	static const Class& forType<Double>() { static const Class _class("Double", nullptr, create<Double>); return _class; }
	template <>
	static const Class& forType<String>() { static const Class _class("String", nullptr, create<String>); return _class; }
	template <>
	static const Class& forType<const Char*>() { return forType<String>(); }
#endif

	const Field& getField(const String& name) const;

	template <typename FUN>
	void foreach_fields(FUN fun) const {
		for (std::map<String, const Field*>::const_iterator iter = _fields.begin();
			iter != _fields.end(); ++iter) {
			fun(iter->second);
		}
	}

	Boolean operator== (const Class& rhs) const { return this == &rhs; }
	Boolean operator!= (const Class& rhs) const { return !(*this == rhs); }
	Boolean operator< (const Class& rhs) const { return this < &rhs; }
	Boolean operator> (const Class& rhs) const { return rhs < *this; }
	Boolean operator<= (const Class& rhs) const { return !(*this > rhs); }
	Boolean operator>= (const Class& rhs) const { return !(*this < rhs); }

	void* newInstance() const { return (*_instance)(); }

private:
	void addField(const Field* field);
	void addMethod(const Method* method);

	friend class Object;
	friend class DtoBase;
	friend class EntityObject;
	friend struct __register_field__;
	friend struct __register_method__;
private:
	static Int s_maxIndex;
	Int _index;
	const Class* _superClass;
	PNewInstance _instance;
	String _name;

	std::map<String, const Field*> _fields;
	std::map<String, const Method*> _methods;
};
CORE_API const std::map<String, const Class* const>& geminiAfxEntityClasses();
CORE_API const std::map<String, const Class* const>& geminiAfxControllerClasses();
#if GEMINI_OS == GEMINI_OS_LINUX
template<>
void* Class::create<void>() { return nullptr; }
template<>
void* Class::create<Object>() { return nullptr; }
template<>
void* Class::create<EntityObject>() { return nullptr; }
template<>
void* Class::create<IList>() { return nullptr; }
template<>
void* Class::create<const IList&>() { return nullptr; }

template <>
const Class& Class::forType<void>() { static const Class _class("void", nullptr, create<void>); return _class; }
template <>
const Class& Class::forType<Boolean>() { static const Class _class("Boolean", nullptr, create<Boolean>); return _class; }
template <>
const Class& Class::forType<Char>() { static const Class _class("Char", nullptr, create<Char>); return _class; }
template <>
const Class& Class::forType<Short>() { static const Class _class("Short", nullptr, create<Short>); return _class; }
template <>
const Class& Class::forType<Int>() { static const Class _class("Int", nullptr, create<Int>); return _class; }
template <>
const Class& Class::forType<Long>() { static const Class _class("Long", nullptr, create<Long>); return _class; }
template <>
const Class& Class::forType<Float>() { static const Class _class("Float", nullptr, create<Float>); return _class; }
template <>
const Class& Class::forType<Double>() { static const Class _class("Double", nullptr, create<Double>); return _class; }
template <>
const Class& Class::forType<String>() { static const Class _class("String", nullptr, create<String>); return _class; }
template <>
const Class& Class::forType<const Char*>() { return forType<String>(); }
#endif

template <class T>
class Property {
protected:
	typedef T value_type;
	typedef typename std::conditional<sizeof(T) <= 8, value_type, const value_type&>::type const_reference;

	Property() : _value() {}
	Property(const_reference val) : _value(val) {}
	~Property() {}
	Property& operator= (const_reference val) {
		_value = val;
		return *this;
	}

	operator const_reference() { return _value; }

private:
	value_type _value;
};
template <>
class Property<String> {
protected:
	typedef String value_type;
	typedef const value_type& const_reference;

	Property() : _value(nullptr) {}
	Property(const_reference val) : _value(new Char[val.size()]) {}
	~Property() { if (_value != nullptr) delete[] _value; }
	Property& operator= (const_reference val) {
		if (_value != nullptr) {
			delete[] _value;
			_value = nullptr;
		}

		_value = new Char[val.size()];
		std::memcpy(_value, val.c_str(), val.size());
		return *this;
	}

	operator const_reference() { return _value; }

private:
	Char* _value;
};
class IList;
enum class RefType {
	Entity,
	Vector,
	List,
	Set
};
class CORE_API PropertyRefHelp {
public:
	static SmartPtr<EntityObject> get(const EntityObject* entity, Int sign);
	static void set(EntityObject* entity, Int sign, const SmartPtr<EntityObject>& relaEntity);
	static const IList& getList(const EntityObject* entity, Int sign);
};
template <class T, RefType Type>
class PropertyRef {
protected:
	typedef const IList& const_reference;
	typedef T value_type;

	PropertyRef() {}
	~PropertyRef() {}
	
	const_reference get(const EntityObject* entity, Int sign) {
		//return *((const IList*)(entity->_relations[sign]));
		return PropertyRefHelp::getList(entity, sign);
	}
};
template <class T>
class PropertyRef<T, RefType::Entity> {
protected:
	typedef SmartPtr<T> const_reference;
	typedef T value_type;

	PropertyRef() {}
	~PropertyRef() {}

	const_reference get(EntityObject* entity, Int sign) {
		return PropertyRefHelp::get(entity, sign);
	}

	void set(EntityObject* entity, Int sign, const_reference val) {
		PropertyRefHelp::set(entity, sign, val);
	}
};

template <class T>
class Sign {
public:
	static Int index;
};
template <class T> Int Sign<T>::index = 0;

template <typename Enum_T>
class EnumHelper {
private:
	static void SplitEnumString(const char* str) {
		/*const char * p = str;
		Int index = 0;
		while (std::isspace(*p)) p++;
		while (*p != '\0') {
			const char* temp = p;
			while (*p == '_' || std::isdigit(*p) || std::isalpha(*p)) p++;
			String name(temp, p - temp);
			while (std::isspace(*p)) p++;

			if (*p == '\0') {
				s_info.insert(std::make_pair(name, index++));
				break;
			}

			if (*p == '=') {
				p++;
				while (std::isspace(*p)) p++;
				temp = p;
				while (std::isdigit(*p)) p++;
				String value(temp, p - temp);
				index = StringUtil::convert<Int>(value.c_str());
				while (std::isspace(*p)) p++;
			}

			if (*p == ',') {
				s_info.insert(std::make_pair(name, index++));
			}
			p++;

			while (std::isspace(*p)) p++;
		}*/
	}
private:
	static const char * s_name;
	static const Class s_class;
	static std::map<String, Int> s_info;
};
template<typename Enum_T> std::map<String, Int> EnumHelper<Enum_T>::s_info;


#define DECLARE_CLASS(CLASS_NAME, SUPER_CLASS_NAME)\
private:\
	typedef CLASS_NAME ClassType;\
	static void* create() { return new CLASS_NAME; }\
	static const gemini::Class _class;\
protected:\
	CLASS_NAME() {}\
	static gemini::Int s_index;\
	virtual gemini::Int signMaxIndex() override { return ClassType::s_index; }\
public:\
	typedef gemini::SmartPtr<ClassType>	SPtr;\
	typedef gemini::SmartPtr<ClassType, gemini::WeakCounted, gemini::StorageNo>	WPtr;\
	virtual ~CLASS_NAME() {}\
    static const gemini::Class& getClassStatic() { return CLASS_NAME::_class; }\
    virtual const gemini::Class& getClass() const { return CLASS_NAME::_class; }


#define DECLARE_CLASS_IMPL(CLASS_NAME, SUPER_CLASS_NAME)\
gemini::Int CLASS_NAME::s_index = SUPER_CLASS_NAME::s_index;\
const gemini::Class CLASS_NAME::_class(#CLASS_NAME, &SUPER_CLASS_NAME::getClassStatic(), create);


#define __OFFSET__(C, M)\
    ((gemini::Long)(&((const C *)1024)->M)-1024)


#define DECLARE_FIELD(FIELD_TYPE, FIELD_NAME)\
public:\
	class __field_##FIELD_NAME : public gemini::Property<FIELD_TYPE>  {\
		typedef gemini::Property<FIELD_TYPE> base_type;\
	public:\
		__field_##FIELD_NAME(): base_type() {\
			static gemini::__register_field__ reg(gemini::Class::forType<FIELD_TYPE>(), __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME);\
		}\
		~__field_##FIELD_NAME() {}\
		__field_##FIELD_NAME& operator= (const_reference val) { \
			base_type::operator=(val); return *this; \
		}\
		operator const_reference() { return base_type::operator const_reference(); }\
		const gemini::Field* field() { static const gemini::Field* holder = &getClassStatic().getField(#FIELD_NAME); return holder; }\
	} _##FIELD_NAME;\
	friend class __field_##FIELD_NAME;


#define DECLARE_ENTITY(CLASS_NAME, FIELD_NAME)\
public:\
	class FIELD_NAME : public gemini::PropertyRef<CLASS_NAME, gemini::RefType::Entity>  {\
		typedef gemini::PropertyRef<CLASS_NAME, gemini::RefType::Entity> base_type;\
	public:\
		FIELD_NAME(): base_type() { index();\
			static gemini::__register_field__ reg(gemini::Class::forName(#CLASS_NAME), __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, index());\
		}\
		~FIELD_NAME() {}\
		FIELD_NAME& operator= (const_reference val) {\
			base_type::set(cur(), index(), val); return *this;\
		}\
		operator const_reference() { return base_type::get(cur(), index()); }\
		static gemini::Int index() { static const gemini::Int temp = ClassType::s_index++; return temp; }\
	private:\
		gemini::EntityObject * cur() { return (gemini::EntityObject *)(((const char *)this) - __OFFSET__(ClassType, _##FIELD_NAME)); }\
	} _##FIELD_NAME;


#define DECLARE_VECTOR(CLASS_NAME, FIELD_NAME)\
public:\
	class FIELD_NAME : public gemini::PropertyRef<CLASS_NAME, gemini::RefType::Vector>  {\
		typedef gemini::PropertyRef<CLASS_NAME, gemini::RefType::Vector> base_type;\
	public:\
		FIELD_NAME(): base_type() { index();\
			static gemini::__register_field__ reg(gemini::Class::forName(#CLASS_NAME), __OFFSET__(ClassType, _##FIELD_NAME), getClassStatic(), #FIELD_NAME, index(), true);\
		}\
		~FIELD_NAME() {}\
		operator const_reference() { return base_type::get(cur(), index()); }\
		static gemini::Int index() { static const gemini::Int temp = ClassType::s_index++; return temp; }\
	private:\
		const gemini::EntityObject * cur() { return (const gemini::EntityObject *)(((const char *)this) - __OFFSET__(ClassType, _##FIELD_NAME)); } \
	} _##FIELD_NAME;

#define DEFINE_ENUM(enum_type_name, ...)\
	enum class enum_type_name {__VA_ARGS__};\
	template<> const gemini::Class gemini::EnumHelper<enum_type_name>::s_class(#enum_type_name, __FILE__, gemini::EntityObject::getClassStatic(), nullptr);\
	template<> const char * gemini::EnumHelper<enum_type_name>::s_name = (gemini::EnumHelper<enum_type_name>::SplitEnumString(#__VA_ARGS__), #enum_type_name);


}
#endif  // GEMINI_Reflect_INCLUDE