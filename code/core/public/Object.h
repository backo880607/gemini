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
class CORE_API BaseEntity : public Object, public AnyAbstract {
 protected:
  static Int s_index;
  BaseEntity();

 public:
  typedef SmartPtr<BaseEntity> SPtr;
  typedef SmartPtr<BaseEntity, WeakCounted, StorageNo> WPtr;

  virtual ~BaseEntity();

  static const gemini::Class& getClassStatic() { return _class; }
  virtual const gemini::Class& getClass() const { return _class; }

  Boolean getModified() const { return _modified; }

  ID getID() const { return _id; }

  virtual Boolean operator==(const Any& rhs) const;
  virtual Boolean operator<(const Any& rhs) const;

 private:
  friend class FieldRefWrapHelper;
  friend class IocRelation;
  friend class EntityFactory;
  friend class DaoUtil;
  static const Class _class;
  Boolean _modified;
  ID _id;
  std::vector<RefBase*> _relations;
  std::map<const Field*, Any> _userDefined;
};

class CORE_API Entity : public BaseEntity {
  DECLARE_ABSTRACT_CLASS(Entity, BaseEntity)
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
    virtual BaseEntity::SPtr nextImpl();

   private:
    std::shared_ptr<Iterator> _iter;
  };

  virtual Boolean empty() const = 0;
  virtual Long size() const = 0;
  virtual Iterator iterator() const = 0;

  virtual Boolean operator==(const Any& rhs) const;
};

class CORE_API EntityHelper {
 protected:
  BaseEntity::SPtr createImpl(const Class& cls, ID id) const;
  BaseEntity::SPtr createTempImpl(const Class& cls) const;
  BaseEntity::SPtr getImpl(const Class& cls) const;
  BaseEntity::SPtr getImpl(const Class& cls, ID id) const;
  BaseEntity::SPtr getInheritImpl(const Class& cls, ID id) const;
  const IList& getListImpl(const Class& cls) const;
  void eraseImpl(BaseEntity::SPtr entity) const;
  void clearImpl(const Class& cls) const;

  BaseEntity::SPtr getImpl(BaseEntity::SPtr entity,
                             const std::vector<Int>& signs) const;
  const IList& getListImpl(BaseEntity::SPtr entity,
                           const std::vector<Int>& signs) const;
  void setImpl(BaseEntity::SPtr entity, Int sign,
               BaseEntity::SPtr relaEntity) const;

  void removeImpl(BaseEntity::SPtr entity, Int sign) const;
  void removeImpl(BaseEntity::SPtr entity, Int sign,
                  BaseEntity::SPtr relaEntity) const;

  template <typename... A>
  class RefSign {};
  template <typename Head, typename... Tail>
  class RefSign<Head, Tail...> {
   public:
    typedef typename RefSign<Tail...>::value_type value_type;
    typedef typename RefSign<Tail...>::const_reference const_reference;
    static void collect(std::vector<gemini::Int>& vals) {
      vals.push_back(Head::index());
      RefSign<Tail...>::collect(vals);
    }
  };
  template <typename Tail>
  class RefSign<Tail> {
   public:
    typedef typename Tail::value_type value_type;
    typedef const SmartPtr<value_type>& const_reference;
    static void collect(std::vector<gemini::Int>& vals) {
      vals.push_back(Tail::index());
    }
  };

 public:
  template <typename T>
  typename T::SPtr create(ID id = 0) const {
    return createImpl(T::getClassStatic(), id);
  }
  template <typename Ref>
  SmartPtr<typename RefSign<Ref...>::value_type> create(
      const BaseEntity::SPtr& entity) const {
    SmartPtr<typename RefSign<Ref...>::value_type> relaEntity =
        create<typename Ref::value_type>();
    setImpl(entity, Ref::index(), relaEntity);
    return relaEntity;
  }
  template <typename T>
  typename T::SPtr createTemp() const {
    return createTempImpl(T::getClassStatic());
  }

  template <typename T>
  typename T::SPtr get() const {
    return getImpl(T::getClassStatic());
  }

  template <typename T>
  typename T::SPtr get(ID id) const {
    return getImpl(T::getClassStatic(), id);
  }

  template <typename T>
  typename T::SPtr getInherit(ID id) const {
    return getInheritImpl(T::getClassStatic(), id);
  }

  template <class T, typename Filter>
  typename T::SPtr get(Filter filter) const {}

  template <class T, typename Fun>
  void foreach (Fun fun) const {
    IList::Iterator iter = getListImpl(T::getClassStatic()).iterator();
    while (iter.hasNext()) {
      fun(iter.next<T>());
    }
  }

  template <typename T>
  const IList& getList() const {
    return getListImpl(T::getClassStatic());
  }

  template <class T, typename Filter>
  std::list<typename T::SPtr> getList(Filter filter) const {
    std::list<typename T::SPtr> entities;
    IList::Iterator iter = getList<T>().iterator();
    while (iter.hasNext()) {
      typename T::SPtr entity = iter.next<T>();
      if (filter(entity)) {
        entities.push_back(entity);
      }
    }
    return entities;
  }

  template <class T>
  std::list<typename T::SPtr> getList(const Char* strExpression) const {
    std::list<typename T::SPtr> entities;
    return entities;
  }

  template <class T>
  std::list<typename T::SPtr> getList(const String& strExpression) const {
    return getList<T>(strExpression.c_str());
  }

  void erase(BaseEntity::SPtr entity) const { eraseImpl(entity); }
  virtual void onErase(BaseEntity::SPtr entity) const {}

  template <class T>
  void clear() {
    clearImpl()
  }

  template <typename... Ref>
  SmartPtr<typename RefSign<Ref...>::value_type> getRela(
      BaseEntity::SPtr entity) const {
    std::vector<Int> signs;
    RefSign<Ref...>::collect(signs);
    return getImpl(entity, signs);
  }

  template <typename... Ref>
  SmartPtr<typename RefSign<Ref...>::value_type> getRela(
      BaseEntity::SPtr entity,
      std::function<Boolean(typename RefSign<Ref...>::const_reference)> filter)
      const {
    std::vector<Int> signs;
    RefSign<Ref...>::collect(signs);
    IList::Iterator iter = getListImpl(entity, signs).iterator();
    while (iter.hasNext()) {
      auto target = iter.next<typename RefSign<Ref...>::value_type>();
      if (filter(target)) {
        return target;
      }
    }

    return nullptr;
  }

  template <typename... Ref>
  void foreach_rela(
      BaseEntity::SPtr entity,
      std::function<void(SmartPtr<typename RefSign<Ref...>::value_type>)> fun)
      const {
    std::list<SmartPtr<typename RefSign<Ref...>::value_type>> entities =
        getRelaList<Ref...>(entity);
    for (auto target : entities) {
      fun(target);
    }
  }

  template <typename... Ref>
  std::list<SmartPtr<typename RefSign<Ref...>::value_type>> getRelaList(
      BaseEntity::SPtr entity) const {
    std::list<SmartPtr<typename RefSign<Ref...>::value_type>> entities;
    std::vector<Int> signs;
    RefSign<Ref...>::collect(signs);
    IList::Iterator iter = getListImpl(entity, signs).iterator();
    while (iter.hasNext()) {
      entities.push_back(iter.next<typename RefSign<Ref...>::value_type>());
    }
    return entities;
  }

  template <typename... Ref>
  std::list<SmartPtr<typename RefSign<Ref...>::value_type>> getRelaList(
      BaseEntity::SPtr entity,
      std::function<Boolean(SmartPtr<typename RefSign<Ref...>::value_type>)>
          filter) const {
    std::list<SmartPtr<typename RefSign<Ref...>::value_type>> entities;
    std::vector<Int> signs;
    RefSign<Ref...>::collect(signs);
    IList::Iterator iter = getListImpl(entity, signs).iterator();
    while (iter.hasNext()) {
      auto entity = iter.next<typename RefSign<Ref...>::value_type>();
      if (filter(entity)) {
        entities.push_back(entity);
      }
    }
    return entities;
  }

  template <typename Ref>
  void removeRela(BaseEntity::SPtr entity) const {
    removeImpl(entity, Ref::index());
  }
  template <typename Ref>
  void removeRela(BaseEntity::SPtr entity, BaseEntity::SPtr relaEntity) const {
    removeImpl(entity, Ref::index(), relaEntity);
  }

  void sync() const;
};

}  // namespace gemini
#endif  // GEMINI_Object_INCLUDE