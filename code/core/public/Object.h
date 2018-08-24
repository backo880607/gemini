#ifndef GEMINI_Object_INCLUDE
#define GEMINI_Object_INCLUDE
#include "DateTime.h"

namespace gemini {

class CORE_API Object {
 protected:
  static Int s_index;
  Object() {}
  Object(const Object& rhs){};
  Object& operator=(const Object& rhs) { return *this; }

 public:
  typedef SmartPtr<Object> SPtr;
  typedef SmartPtr<Object, WeakCounted, StorageNo> WPtr;

  virtual ~Object() {}

  static const Class& getClassStatic() { return s_class; }
  virtual const Class& getClass() const { return s_class; }

 protected:
  virtual Int signMaxIndex() = 0;

 private:
  static const Class s_class;
};

class RefBase;
class CORE_API EntityObject : public Object, public AnyAbstract {
 protected:
  static Int s_index;
  EntityObject();

 public:
  typedef SmartPtr<EntityObject> SPtr;
  typedef SmartPtr<EntityObject, WeakCounted, StorageNo> WPtr;
  struct Flag {
    Boolean created;
    Boolean modified;
    Boolean tempRead;
  };

  virtual ~EntityObject();

  static const gemini::Class& getClassStatic() { return _class; }
  virtual const gemini::Class& getClass() const { return _class; }

  ID getID() const { return _id; }

  Flag& getFlag() { return _flag; }

  virtual Boolean operator==(const Any& rhs) const;
  virtual Boolean operator<(const Any& rhs) const;

 private:
  friend class PropertyRefHelp;
  friend class IocRelation;
  friend class EntityFactory;
  friend class Memory;
  template <class T, RefType Type>
  friend class PropertyRef;
  static const Class _class;
  Flag _flag;
  ID _id;
  std::vector<RefBase*> _relations;
};

class CORE_API IList : public AnyAbstract {
 public:
  class CORE_API Iterator {
   public:
    virtual ~Iterator() {}
    Iterator(Iterator* iter) : _iter(iter) {}
    Iterator(const Iterator& rhs) : _iter(rhs._iter) {}
    Iterator& operator=(const Iterator& rhs) {
      _iter = rhs._iter;
      return *this;
    }

    virtual Boolean hasNext() { return _iter != nullptr && _iter->hasNext(); }
    template <class T>
    typename T::SPtr next() {
      return _iter->nextImpl();
    }

   protected:
    Iterator() : _iter(nullptr) {}
    virtual const EntityObject::SPtr& nextImpl();

   private:
    std::shared_ptr<Iterator> _iter;
  };

  virtual Boolean empty() const = 0;
  virtual Long size() const = 0;
  virtual Iterator iterator() const = 0;

  virtual Boolean operator==(const Any& rhs) const;
};

class CORE_API GlobalObject : public Object {};

}  // namespace gemini
#endif  // GEMINI_Object_INCLUDE