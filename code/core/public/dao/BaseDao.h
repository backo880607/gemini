#ifndef GEMINI_BaseDao_INCLUDE
#define GEMINI_BaseDao_INCLUDE
#include "../public/Object.h"

namespace gemini {

class CORE_API DaoListener {
 public:
  DaoListener() {}
  virtual ~DaoListener() {}

  virtual void startSync() = 0;
  virtual void endSync() = 0;
};

class CORE_API BaseDao : public Object {
  DECLARE_ABSTRACT_CLASS(BaseDao, Object)

  virtual void init(std::vector<DaoListener *> &listeners) {}

  const Class &getEntityClass() { return *_entityCls; }

  virtual const IList &select() = 0;
  virtual BaseEntity::SPtr select(ID id) = 0;
  virtual void insert(BaseEntity::SPtr entity) = 0;
  virtual void update(BaseEntity::SPtr entity) = 0;
  virtual void erase(ID id) = 0;
  virtual void erase(BaseEntity::SPtr entity) = 0;
  virtual void clear() = 0;

  virtual void insert(const std::vector<BaseEntity::SPtr> &entities) = 0;
  virtual void update(const std::vector<BaseEntity::SPtr> &entities) = 0;
  virtual void erase(const std::vector<BaseEntity::SPtr> &entities) = 0;

  virtual void sync() {}

 protected:
  BaseEntity::SPtr createEntity(const Class &cls, ID id);

 private:
  friend class DaoMgr;
  const Class *_entityCls = nullptr;
};

namespace dao {
class CORE_API DaoRegister {
 public:
  DaoRegister(const Class &daoClass, const Class &entityClass,
              Boolean global = false);
  ~DaoRegister();
};
class CORE_API ListenerRegister {
  typedef DaoListener *(*Creater)();

 public:
  ListenerRegister(Creater creater);
  ~ListenerRegister();
};
}  // namespace dao

#define DAO_REGISTER(DaoClass, EntityClass)             \
  gemini::dao::DaoRegister gemini_##DaoClass##Register( \
      DaoClass::getClassStatic(), EntityClass::getClassStatic());

#define DAO_GLOBAL_REGISTER(DaoClass, EntityClass)      \
  gemini::dao::DaoRegister gemini_##DaoClass##Register( \
      DaoClass::getClassStatic(), EntityClass::getClassStatic(), true);

#define DAO_LISTENER_REGISTER(ListenerClass)                    \
  \
gemini::DaoListener *gemini_create_##ListenerClass() {          \
    return new ListenerClass();                                 \
  }                                                             \
  \
gemini::dao::ListenerRegister gemini_##ListenerClass##Register( \
      gemini_create_##ListenerClass);

}  // namespace gemini
#endif  // GEMINI_BaseDao_INCLUDE