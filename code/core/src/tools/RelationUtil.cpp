#include "../../include/entities/FactoryMgr.h"
#include "../../public/tools/RelationUtil.h"

namespace gemini {

Int RelationUtil::getRelaType(const Class& cls, Int sign) {
  const gemini::EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(cls, sign);
  return data != nullptr ? (Int)(data->rela) : -1;
}

Int RelationUtil::getRelaReverseSign(const Class& cls, Int sign) {
  const gemini::EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(cls, sign);
  return data != nullptr ? data->relaSign : -1;
}

const Class* RelationUtil::getRelaClass(const Class& cls, Int sign) {
  const gemini::EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(cls, sign);
  if (data == nullptr) {
    return nullptr;
  }
  return &data->relaFactory->getEntityClass();
}

const Class* RelationUtil::getRelaClassByName(const Class& cls,
                                              const String& name) {
  const gemini::EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(cls, name);
  if (data == nullptr) {
    return nullptr;
  }
  return &data->relaFactory->getEntityClass();
}

}  // namespace gemini