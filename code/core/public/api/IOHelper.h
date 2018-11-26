#ifndef GEMINI_IO_IOHelper_INCLUDE
#define GEMINI_IO_IOHelper_INCLUDE
#include "Handler.h"

namespace gemini {
namespace api {

template <typename Key, class ClassExtra = EmptyType,
          class EntityExtra = EmptyType>
class KeyMapEntity : public EntityHelper {
  enum { IsID = std::is_same<Key, ID>::value };
  typedef typename std::conditional<sizeof(Key) <= 8, Key,
                                    typename std::add_const<Key>::type&>::type
      key_reference;

  template <typename KeyType, Boolean IDKey>
  struct FetchID {
    static ID get(KeyType key) { return key; }
  };
  template <typename KeyType>
  struct FetchID<KeyType, false> {
    static ID get(KeyType key) { return 0; }
  };

  struct EntityInfo {
    EntityInfo() : data(new EntityExtra) {}
    EntityInfo(const BaseEntity::SPtr& value)
        : entity(value), data(new EntityExtra) {}
    BaseEntity::SPtr entity;
    std::shared_ptr<EntityExtra> data;
  };

  struct ClassInfo {
    typedef std::map<Key, EntityInfo> key_entity;
    const Class* cls;
    key_entity entities;
    std::shared_ptr<ClassExtra> data;

    ClassInfo() : cls(nullptr), data(new ClassExtra) {}
    ClassInfo(const Class& value) : cls(&value), data(new ClassExtra) {}
    ~ClassInfo() {}
    void reset() { entities.clear(); }
    template <typename FUN>
    void foreach_entity(FUN fun) const {
      for (typename key_entity::const_iterator iter = entities.begin();
           iter != entities.end(); ++iter) {
        BaseEntity::SPtr entity = iter->second.entity;
        if (entity.ValidObj()) {
          fun(*cls, entity);
        }
      }
    }
    template <typename FUN>
    void foreach_data(FUN fun) const {
      for (typename key_entity::const_iterator iter = entities.begin();
           iter != entities.end(); ++iter) {
        BaseEntity::SPtr obj = iter->second.entity;
        if (entity.ValidObj()) {
          fun(*cls, entity, iter->second.data);
        }
      }
    }
  };

 public:
  KeyMapEntity() {}
  ~KeyMapEntity() {}

  template <typename FilterFun>
  void init(FilterFun fun) {
    const std::map<String, const Class* const>& clses =
        geminiAfxEntityClasses();
    for (auto iter = clses.begin(); iter != clses.end(); ++iter) {
      init(*iter->second, fun);
    }
  }
  template <typename FilterFun>
  void init(const std::vector<const Class*>& clses, FilterFun fun) {
    for (const Class* cls : clses) {
      init(*cls, fun);
    }
  }
  template <typename FilterFun>
  void init(const Class& cls, FilterFun fun) {
    if (!cls.isBase(BaseEntity::getClassStatic())) {
      return;
    }
    ClassInfo& clsInfo = getClassInfo(cls);
    clsInfo.reset();
    const IList::Iterator iter = getListImpl(cls).iterator();
    while (iter.hasNext()) {
      BaseEntity::SPtr entity = iter.next<BaseEntity>();
      Key key;
      if (fun(cls, entity, key)) {
        clsInfo.entities.insert(make_pair(key, entity));
      }
    }
  }

  Boolean existClass(const Class& cls) {
    return _value.find(&cls) != _value.end();
  }

  Boolean existKey(const Class& cls, key_reference key) {
    typename ClassInfo::key_entity& entities = getClassInfo(cls).entities;
    return entities.find(key) != entities.end();
  }

  BaseEntity::SPtr getEntity(const Class& cls, key_reference key,
                               Boolean bCreate = false, Boolean bTemp = false) {
    typename ClassInfo::key_entity& entities = getClassInfo(cls).entities;
    typename ClassInfo::key_entity::iterator iter = entities.find(key);
    if (iter != entities.end()) return iter->second.entity;

    BaseEntity::SPtr entity;
    if (bCreate) {
      ID id = FetchID<key_reference, IsID>::get(key);
      if (bTemp) {
        entity = createTempImpl(cls);
      } else {
      }
      entities.insert(std::make_pair(key, entity));
    }
    return std::move(entity);
  }

  std::shared_ptr<EntityExtra> getData(const Class& cls, key_reference key,
                                       Boolean bCreate = false) {
    typename ClassInfo::key_entity& entities = getClassInfo(cls).entities;
    typename ClassInfo::key_entity::iterator iter = entities.find(key);
    if (iter != entities.end()) return iter->second.data;

    /*if (bCreate) {
      return entities[key].data;
    }*/
    return nullptr;
  }
  std::shared_ptr<ClassExtra> getClassData(const Class& cls) {
    return getClassInfo(cls).data;
  }

  void insert(const Class& cls, key_reference key, BaseEntity::SPtr entity,
              Boolean bReplace = true) {
    getClassInfo(cls).entities[key].entity = entity;
  }
  void insert(const Class& cls, key_reference key, BaseEntity::SPtr entity,
              const std::shared_ptr<EntityExtra>& data) {
    EntityInfo& info = getClassInfo(cls).entities[key];
    info.entity = entity;
    info.data = data;
  }

  void remove(const Class& cls, key_reference key) {
    getClassInfo(cls).entities.erase(key);
  }

  template <typename FUN>
  void foreach_obj(FUN fun, const Class* cls) const {
    if (cls == nullptr) {
      for (typename std::map<const Class*, ClassInfo>::const_iterator iter =
               _value.begin();
           iter != _value.end(); ++iter) {
        iter->second.foreach_obj(fun);
      }
    } else {
      typename std::map<const Class*, ClassInfo>::const_iterator iter =
          _value.find(cls);
      if (iter == _value.end()) return;

      iter->second.foreach_obj(fun);
    }
  }

  template <typename FUN>
  void foreach_data(FUN fun, const Class* cls) const {
    if (cls == nullptr) {
      for (typename std::map<const Class*, ClassInfo>::const_iterator iter =
               _value.begin();
           iter != _value.end(); ++iter) {
        iter->second.foreach_data(fun);
      }
    } else {
      typename std::map<const Class*, ClassInfo>::const_iterator iter =
          _value.find(cls);
      if (iter == _value.end()) return;

      iter->second.foreach_data(fun);
    }
  }
  template <typename FUN>
  void foreach_cls(FUN fun) const {
    for (typename std::map<const Class*, ClassInfo>::const_iterator iter =
             _value.begin();
         iter != _value.end(); ++iter) {
      fun(iter->second.data);
    }
  }

  void clear(const Class* cls = nullptr) {
    cls == nullptr ? _value.clear() : _value.erase(cls);
  }

  BaseEntity::SPtr createTemp(const Class& cls) const {
    return createTempImpl(cls);
  }

 private:
  ClassInfo& getClassInfo(const Class& cls) {
    ClassInfo& clsInfo = _value[&cls];
    if (clsInfo.cls == nullptr) clsInfo.cls = &cls;
    return clsInfo;
  }

 private:
  std::map<const Class*, ClassInfo> _value;
};

class DataHandler;
class ObjectHandler;
class ValidateHandler;
class IOScheme;
class DataHandlerHelper;
class ObjectHandlerHelper;
class ValidateHandlerHelper;
class CORE_API IOHelper {
 public:
  IOHelper();
  virtual ~IOHelper();

  template <typename T, class HANDLER>
  void registerDataHandler() {
    registerDataHandlerImpl(Class::forType<T>(), new HANDLER());
  }

  template <class CLS, typename FIELD, class HANDLER>
  void registerDataHandler() {
    registerDataHandlerImpl(Class::forType<CLS>(), FIELD::field(),
                            new HANDLER());
  }

  template <class CLS, class HANDLER>
  void registerObjectHandler() {
    registerObjectHandlerImpl(Class::forType<CLS>(), new HANDLER());
  }

  template <typename T, class HANDLER>
  void registerValidateHandler() {
    registerValidateHandlerImpl(Class::forType<T>(), new HANDLER());
  }

  template <class CLS, typename FIELD, class HANDLER>
  void registerValidateHandler() {
    registerValidateHandlerImpl(Class::forType<CLS>(), FIELD::field(),
                                new HANDLER());
  }

  template <class CLS, class HANDLER>
  void registerDefaultObjectHandler() {
    registerDefaultObjectHandlerImpl(Class::forType<CLS>(), new HANDLER());
  }

 protected:
  std::shared_ptr<ObjectHandler> getObjectHandler(const Class& cls);
  std::shared_ptr<ValidateHandler> getValidateHandler(const Field& field);
  void write(Object::SPtr entity, const Field* field, const String& value);

 private:
  void registerDataHandlerImpl(const Class& cls, DataHandler* handler);
  void registerDataHandlerImpl(const Class& cls, const Field& field,
                               DataHandler* handler);

  void registerObjectHandlerImpl(const Class& cls, ObjectHandler* handler);
  void registerDefaultObjectHandlerImpl(const Class& cls,
                                        ObjectHandler* handler);

  void registerValidateHandlerImpl(const Class& cls, ValidateHandler* handler);
  void registerValidateHandlerImpl(const Class& cls, const Field& field,
                                   ValidateHandler* handler);

 protected:
  std::shared_ptr<DataHandlerHelper> _dataHelper;
  std::shared_ptr<ObjectHandlerHelper> _objectHelper;
  std::shared_ptr<ValidateHandlerHelper> _validateHelper;
  std::shared_ptr<ObjectHandler> _defaultObjectHandler;
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_IOHelper_INCLUDE