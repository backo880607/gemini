#ifndef GEMINI_IocRelation_INCLUDE
#define GEMINI_IocRelation_INCLUDE
#include "Object.h"
#include "RefVector.h"

namespace gemini {

class IocRelation final {
  static BaseEntity::SPtr getImpl(BaseEntity::SPtr entity,
                                    std::vector<Int>::const_iterator iter,
                                    const std::vector<Int>& signs);

  static void getListImpl(BaseEntity::SPtr entity,
                          std::vector<Int>::const_iterator iter,
                          const std::vector<Int>& signs);

 public:
  static BaseEntity::SPtr get(BaseEntity::SPtr entity, Int sign);
  static BaseEntity::SPtr get(BaseEntity::SPtr entity,
                                const std::vector<Int>& signs);

  static const IList& getList(BaseEntity::SPtr entity, Int sign);
  static const IList& getList(BaseEntity::SPtr entity,
                              const std::vector<Int>& signs);

  static void set(BaseEntity::SPtr entity, Int sign,
                  BaseEntity::SPtr relaEntity);

  static void remove(BaseEntity::SPtr entity, Int sign);
  static void remove(BaseEntity::SPtr entity, Int sign,
                     BaseEntity::SPtr relaEntity);
};

}  // namespace gemini
#endif  // GEMINI_IocRelation_INCLUDE