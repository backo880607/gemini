#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_MemoryINCLUDE
#include "DaoMgr.h"

#include <mutex>

namespace gemini {

class Memory final : noncopyable {
 private:
  static Memory &current();
  static std::shared_ptr<BaseDao> getDao(const Class &cls) {
    return current()._daoMgr.getDao(cls);
  }

  friend class Session;
  Memory();

 public:
  ~Memory();

  static EntityObject::SPtr create(const Class &cls, Long id);
  static EntityObject::SPtr createTemp(const Class &cls);

  static EntityObject::SPtr get(const Class &cls);
  static EntityObject::SPtr get(const Class &cls, Long id);
  static const IList &getList(const Class &cls);

  static void update(const EntityObject *entity);
  static void erase(const Class &cls, ID id);
  static void erase(const EntityObject *entity);
  static void clear(const Class &cls);

  static void sync();

 private:
  static EntityObject::SPtr createImpl(const Class &cls, Long id);

 private:
  DaoMgr _daoMgr;
};

}  // namespace gemini
#endif  // GEMINI_Memory_INCLUDE