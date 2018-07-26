#ifndef GEMINI_IocRelation_INCLUDE
#define GEMINI_IocRelation_INCLUDE
#include "../../public/Object.h"
#include "RefVector.h"

namespace gemini {

class IocRelation final {
  static EntityObject::SPtr getImpl(EntityObject::SPtr entity,
                                    std::vector<Int>::const_iterator iter,
                                    const std::vector<Int>& signs);

  static void getListImpl(EntityObject::SPtr entity,
                          std::vector<Int>::const_iterator iter,
                          const std::vector<Int>& signs);

 public:
  static EntityObject::SPtr get(EntityObject::SPtr entity, Int sign);
  static EntityObject::SPtr get(EntityObject::SPtr entity,
                                const std::vector<Int>& signs);

  static const IList& getList(EntityObject::SPtr entity, Int sign);
  static const IList& getList(EntityObject::SPtr entity,
                              const std::vector<Int>& signs);

  static void set(EntityObject::SPtr entity, Int sign,
                  EntityObject::SPtr relaEntity);

  static void remove(EntityObject::SPtr entity, Int sign);
  static void remove(EntityObject::SPtr entity, Int sign,
                     EntityObject::SPtr relaEntity);
};

}  // namespace gemini
#endif  // GEMINI_IocRelation_INCLUDE