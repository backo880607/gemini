#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_MemoryINCLUDE
#include "DaoMgr.h"

#include <mutex>

namespace gemini {

class DaoUtil final : noncopyable {
 private:
  static std::shared_ptr<BaseDao> getDao(const Class &cls);
  friend class Session;
  DaoUtil();

 public:
  ~DaoUtil();

  static BaseEntity::SPtr create(const Class &cls, ID id);
  static BaseEntity::SPtr createTemp(const Class &cls);

  static BaseEntity::SPtr get(const Class &cls);
  static BaseEntity::SPtr get(const Class &cls, ID id);
  static const IList &getList(const Class &cls);

  static void insert(const BaseEntity::SPtr &entity);
  static void update(const BaseEntity *entity);
  static void erase(const Class &cls, ID id);
  static void erase(const BaseEntity *entity);
  static void clear(const Class &cls);

  static void sync();

 private:
  static BaseEntity::SPtr createImpl(const Class &cls, ID id);

 private:
  DaoMgr _daoMgr;
};

}  // namespace gemini
#endif  // GEMINI_Memory_INCLUDE