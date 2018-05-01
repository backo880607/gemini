#ifndef GEMINI_Any_INCLUDE
#define GEMINI_Any_INCLUDE
#include "ReflectMethod.h"

namespace gemini {

namespace ns_any {

template <typename T, Boolean BEntity>
struct ObtainHolderTypeImpl {
	typedef SmartPtr<EntityObject> holder_type;
};
template <typename T>
struct ObtainHolderTypeImpl<T, false> {
	typedef T holder_type;
};
template <typename T>
struct ObtainHolderType {
	typedef typename ObtainHolderTypeImpl<T, std::is_base_of<EntityObject, T>::value>::holder_type holder_type;
	typedef const holder_type& const_reference;
};
template <>
struct ObtainHolderType<IList> {
	typedef const IList& holder_type;
	typedef const IList& const_reference;
};

}
class CORE_API Any
{
public:
	class PlaceHolder {
	public:
		virtual const Class& getClass() const = 0;
		virtual PlaceHolder* clone() const = 0;
		virtual Any operator+ (const Any& rhs) const = 0;
		virtual void operator+= (const Any& rhs) = 0;
		virtual Any operator- (const Any& rhs) const = 0;
		virtual void operator-= (const Any& rhs) = 0;
		virtual Any operator* (const Any& rhs) const = 0;
		virtual void operator*= (const Any& rhs) = 0;
		virtual Any operator/ (const Any& rhs) const = 0;
		virtual void operator/= (const Any& rhs) = 0;
		virtual Boolean operator== (const Any& rhs) const = 0;
		virtual Boolean operator< (const Any& rhs) const = 0;
		virtual String str() const = 0;
	};
	template <typename T>
	class Holder : public PlaceHolder {
	protected:
		friend class Any;
		T _value;
	public:
		Holder(const T& value) : _value(value) {}
		virtual const Class& getClass() const { return Class::forType<T>(); }
	};
	template <typename T>
	class HolderClass : public Holder<T> {
	public:
		HolderClass(const T& value) : Holder<T>(value) {}
		virtual PlaceHolder* clone() const { return new HolderClass(Holder<T>::_value); }
		virtual Any operator+ (const Any& rhs) const { return Holder<T>::_value + rhs; }
		virtual void operator+= (const Any& rhs) { Holder<T>::_value += rhs; }
		virtual Any operator- (const Any& rhs) const { return Holder<T>::_value - rhs; }
		virtual void operator-= (const Any& rhs) { Holder<T>::_value -= rhs; }
		virtual Any operator* (const Any& rhs) const { return Holder<T>::_value * rhs; }
		virtual void operator*= (const Any& rhs) { Holder<T>::_value *= rhs; }
		virtual Any operator/ (const Any& rhs) const { return Holder<T>::_value / rhs; }
		virtual void operator/= (const Any& rhs) { Holder<T>::_value /= rhs; }
		virtual Boolean operator== (const Any& rhs) const { return Holder<T>::_value == rhs; }
		virtual Boolean operator< (const Any& rhs) const { return Holder<T>::_value < rhs; }
		virtual String str() const { return Holder<T>::_value.str(); }
	};

	template <typename T>
	PlaceHolder* create(const T& value) { return new HolderClass<T>(value); }
	PlaceHolder* create(Boolean value);
	PlaceHolder* create(Char value);
	PlaceHolder* create(Char16 value);
	PlaceHolder* create(Char32 value);
	PlaceHolder* create(Short value);
	PlaceHolder* create(Int value);
	PlaceHolder* create(Long value);
	PlaceHolder* create(Float value);
	PlaceHolder* create(Double value);
	PlaceHolder* create(const String& value);
	PlaceHolder* create(const Char* value);
	PlaceHolder* create(const SmartPtr<EntityObject>& value);
	PlaceHolder* create(const IList& value);

public:
	Any() : _holder(nullptr) {};
	Any(std::nullptr_t rhs) : _holder(nullptr) {}
	template <typename T>
	Any(const T& value) : _holder(create(value)) {}
	template <typename T>
	Any(const SmartPtr<T>& value) : _holder(create(value)) {}
	Any(const Any& rhs);
	Any(Any&& rhs);
	~Any();

	template <typename T>
	Any& operator= (const T& value) {
		Any(value).swap(*this);
		return *this;
	}
	template <typename T>
	Any& operator= (const SmartPtr<T>& value) {
		Any(value).swap(*this);
		return *this;
	}
	Any& operator= (const Any& value) {
		Any(value).swap(*this);
		return *this;
	}
	Any& operator= (Any&& value) {
		Any(value).swap(*this);
		return *this;
	}
	Any& operator= (std::nullptr_t rhs);

	explicit operator Boolean() const noexcept { return _holder != nullptr; }
	Boolean operator!() const { return _holder == nullptr; }
	
	const Class& getClass() const;

	template <typename T>
	Boolean isType() const { return getClass() == Class::forType<T>(); }
	template <typename T1, typename T2>
	Boolean isType() const { return isType<T1>() || isType<T2>(); }
	template <typename T1, typename T2, typename T3>
	Boolean isType() const { return isType<T1>() || isType<T2>() || isType<T3>(); }
	template <typename T1, typename T2, typename T3, typename T4>
	Boolean isType() const { return isType<T1>() || isType<T2>() || isType<T3>() || isType<T4>(); }
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	Boolean isType() const { return isType<T1>() || isType<T2>() || isType<T3>() || isType<T4>() || isType<T5>(); }

	template <typename T>
	typename ns_any::ObtainHolderType<typename ns_class::remove_cv<T>::type>::const_reference cast() const {
		return static_cast<Holder<typename ns_any::ObtainHolderType<typename ns_class::remove_cv<T>::type>::holder_type>*>(_holder)->_value;
	}

	Any operator+ (const Any& rhs) const;
	Any& operator+= (const Any& rhs);
	Any operator- (const Any& rhs) const;
	Any& operator-= (const Any& rhs);
	Any operator* (const Any& rhs) const;
	Any& operator*= (const Any& rhs);
	Any operator/ (const Any& rhs) const;
	Any& operator/= (const Any& rhs);

	Boolean operator== (const Any& rhs) const;
	Boolean operator!= (const Any& rhs) const { return !(*this == rhs); }
	Boolean operator< (const Any& rhs) const;
	Boolean operator<= (const Any& rhs) const { return !(rhs < *this); }
	Boolean operator> (const Any& rhs) const { return rhs < *this; }
	Boolean operator>= (const Any& rhs) const { return !(*this < rhs); }

	String str() const;
private:
	void swap(Any& rhs) { std::swap(_holder, rhs._holder); }

private:
	PlaceHolder* _holder;
	friend class StringUtil;
};

class CORE_API AnyAbstract {
public:
	virtual Any operator+ (const Any& rhs) const;
	virtual void operator+= (const Any& rhs);
	virtual Any operator- (const Any& rhs) const;
	virtual void operator-= (const Any& rhs);
	virtual Any operator* (const Any& rhs) const;
	virtual void operator*= (const Any& rhs);
	virtual Any operator/ (const Any& rhs) const;
	virtual void operator/= (const Any& rhs);
	virtual Boolean operator== (const Any& rhs) const;
	virtual Boolean operator< (const Any& rhs) const;

	virtual String str() const;
};

}
#endif // GEMINI_Any_INCLUDE