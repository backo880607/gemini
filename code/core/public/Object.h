#ifndef GEMINI_Object_INCLUDE
#define GEMINI_Object_INCLUDE
#include "DateTime.h"

namespace gemini {

class CORE_API Object
{
protected:
	Object() {}
	Object(const Object& rhs) {};
	Object& operator= (const Object& rhs) { return *this; }
public:
	typedef SmartPtr<Object> SPtr;
	typedef SmartPtr<Object, WeakCounted, StorageNo> WPtr;

	virtual ~Object() {}
	
	static const Class& getClassStatic() { return s_class; }
	virtual const Class& getClass() const { return s_class; }

protected:
	virtual gemini::UInt signMaxIndex() = 0;

private:
	static const Class s_class;
};

class RefBase;
class CORE_API EntityObject : public Object, public AnyAbstract
{
protected:
	static UInt s_index;
	EntityObject();
public:
	typedef SmartPtr<EntityObject> SPtr;
	typedef SmartPtr<EntityObject, WeakCounted, StorageNo> WPtr;

	virtual ~EntityObject();

	static const gemini::Class& getClassStatic() { return _class; }
	virtual const gemini::Class& getClass() const { return _class; }

	ID getID() const { return _id; }

	virtual Boolean operator== (const Any& rhs) const;
	virtual Boolean operator< (const Any& rhs) const;

private:
	friend class IocRelation;
	friend class EntityFactory;
	template <class T, RefType Type> friend class PropertyRef;
	static const Class _class;
	ID _id;
	std::vector<RefBase*> _relations;
};

class CORE_API IList : public AnyAbstract
{
public:
	class CORE_API Iterator {
	public:
		Iterator(Iterator* iter) : _iter(iter) {}
		Iterator(const Iterator& rhs) : _iter(rhs._iter) {}
		Iterator& operator= (const Iterator& rhs) { _iter = rhs._iter; return *this; }

		virtual Boolean hasNext() { return _iter != nullptr && _iter->hasNext(); }
		template <class T>
		typename T::SPtr next() {
			return _iter->nextImpl();
		}
	protected:
		Iterator() : _iter(nullptr) {}
		virtual const EntityObject::SPtr& nextImpl() { return nullptr; }
	private:
		Iterator* _iter;
	};

	virtual Boolean empty() = 0;
	virtual ULong size() = 0;
	virtual Iterator iterator() const = 0;

	virtual Boolean operator== (const Any& rhs) const;
	virtual String str() const;
};

class CORE_API GlobalObject : public Object
{

};

}
#endif // GEMINI_Object_INCLUDE