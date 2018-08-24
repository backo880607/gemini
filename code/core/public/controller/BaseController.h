#ifndef GEMINI_BaseController_INCLUDE
#define GEMINI_BaseController_INCLUDE
#include "../Object.h"

namespace gemini {

class CORE_API DtoBase : public Object {
 public:
  DtoBase() {}
  virtual ~DtoBase() {}

  static const gemini::Class& getClassStatic() { return _class; }
  virtual const gemini::Class& getClass() const { return _class; }

 private:
  static const Class _class;
};

class CORE_API BaseController : public Object {
  EntityObject::SPtr createImpl(const Class& cls, Long id) const;
  EntityObject::SPtr createTempImpl(const Class& cls) const;
  EntityObject::SPtr getImpl(const Class& cls) const;
  EntityObject::SPtr getImpl(const Class& cls, Long id) const;
  EntityObject::SPtr getInheritImpl(const Class& cls, Long id) const;
  const IList& getListImpl(const Class& cls) const;

  EntityObject::SPtr getImpl(EntityObject::SPtr entity,
                             const std::vector<Int>& signs) const;
  const IList& getListImpl(EntityObject::SPtr entity,
                           const std::vector<Int>& signs) const;
  void setImpl(EntityObject::SPtr entity, Int sign,
               EntityObject::SPtr relaEntity) const;

  template <typename... A>
  class RefSign {};
  template <typename Head, typename... Tail>
  class RefSign<Head, Tail...> {
   public:
    typedef typename RefSign<Tail...>::value_type value_type;
    static void collect(std::vector<gemini::Int>& vals) {
      vals.push_back(Head::index());
      RefSign<Tail...>::collect(vals);
    }
  };
  template <typename Tail>
  class RefSign<Tail> {
   public:
    typedef Tail value_type;
    static void collect(std::vector<gemini::Int>& vals) {
      vals.push_back(Tail::index());
    }
  };

 protected:
  static Int s_index;
  BaseController();

 public:
  typedef SmartPtr<BaseController> SPtr;
  typedef SmartPtr<BaseController, WeakCounted, StorageNo> WPtr;

  virtual ~BaseController();

  static const gemini::Class& getClassStatic() { return _class; }
  virtual const gemini::Class& getClass() const { return _class; }

  template <typename T>
  typename T::SPtr create(Long id = 0) const {
    return createImpl(T::getClassStatic(), id);
  }
  template <typename T>
  typename T::const_reference create(const EntityObject::SPtr& entity) const {
    typename T::const_reference relaEntity = create<typename T::value_type>();
    setImpl(entity, T::index(), relaEntity);
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
  typename T::SPtr get(Long id) const {
    return getImpl(T::getClassStatic(), id);
  }

  template <typename T>
  typename T::SPtr getInherit(Long id) const {
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

  template <typename T, typename... Ref>
  typename T::SPtr get(EntityObject::SPtr entity) const {
    std::vector<gemini::Int> signs;
    RefSign<Ref...>::collect(signs);
    return getImpl(entity, signs);
  }

  template <typename T, typename... Ref>
  typename T::SPtr get(EntityObject::SPtr entity,
                       std::function<Boolean(typename T::SPtr)> filter) const {
    std::vector<gemini::Int> signs;
    RefSign<Ref...>::collect(signs);
    IList::Iterator iter = getListImpl(entity, signs).iterator();
    while (iter.hasNext()) {
      typename T::SPtr target = iter.next<T>();
      if (filter(target)) {
        return target;
      }
    }

    return nullptr;
  }

  template <typename T, typename... Ref>
  void foreach (EntityObject::SPtr entity,
                std::function<void(typename T::SPtr)> fun) const {
    std::list<typename T::SPtr> entities = getList<T, Ref...>(entity);
    for (typename T::SPtr target : entities) {
      fun(target);
    }
  }

  template <typename T, typename... Ref>
  std::list<typename T::SPtr> getList(EntityObject::SPtr entity) const {
    std::list<typename T::SPtr> entities;
    std::vector<gemini::Int> signs;
    RefSign<Ref...>::collect(signs);
    IList::Iterator iter = getListImpl(entity, signs).iterator();
    while (iter.hasNext()) {
      entities.push_back(iter.next<T>());
    }
    return entities;
  }

  template <class T, typename... Ref>
  std::list<typename T::SPtr> getList(
      EntityObject::SPtr entity,
      std::function<Boolean(typename T::SPtr)> filter) const {
    std::list<typename T::SPtr> entities = getList<T>();
    for (typename std::list<typename T::SPtr>::iterator iter = entities.begin();
         iter != entities.end(); ++iter) {
      if (!filter(*iter)) {
        iter = entities.erase(iter);
      }
    }
    return entities;
  }

 private:
  static const Class _class;
};

#define CONTROLLER_METHOD(RETURN_TYPE, METHOD_NAME, METHOD_ARGS) \
  METHOD(RETURN_TYPE, METHOD_NAME, METHOD_ARGS)

}  // namespace gemini
#endif  // GEMINI_BaseController_INCLUDE