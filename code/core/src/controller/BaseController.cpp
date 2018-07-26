#include "controller/BaseController.h"
#include "controller/ControllerMgr.h"
#include "dao/Memory.h"
#include "entities/IocRelation.h"

namespace gemini {

void *createDto() { return nullptr; }
const Class DtoBase::_class("DtoBase", nullptr, createDto);

Int BaseController::s_index = 0;
void *createBaseController() { return nullptr; }
const Class BaseController::_class("BaseController", nullptr,
                                   createBaseController);
BaseController::BaseController() {}

BaseController::~BaseController() {}

EntityObject::SPtr BaseController::createImpl(const Class &cls, Long id) const {
  return Memory::create(cls, id);
}

EntityObject::SPtr BaseController::createTempImpl(const Class &cls) const {
  return Memory::createTemp(cls);
}

EntityObject::SPtr BaseController::getImpl(const Class &cls) const {
  return Memory::get(cls);
}

EntityObject::SPtr BaseController::getImpl(const Class &cls, Long id) const {
  return Memory::get(cls, id);
}

EntityObject::SPtr BaseController::getInheritImpl(const Class &cls,
                                                  Long id) const {
  return EntityObject::SPtr();
}

static RefVector ddddddd = RefVector();
const IList &BaseController::getListImpl(const Class &cls) const {
  return ddddddd;
  // return Memory::getList(cls);
}

EntityObject::SPtr BaseController::getImpl(
    EntityObject::SPtr entity, const std::vector<Int> &signs) const {
  return IocRelation::get(entity, signs);
}

const IList &BaseController::getListImpl(EntityObject::SPtr entity,
                                         const std::vector<Int> &signs) const {
  return IocRelation::getList(entity, signs);
}

void BaseController::setImpl(EntityObject::SPtr entity, Int sign,
                             EntityObject::SPtr relaEntity) const {
  IocRelation::set(entity, sign, relaEntity);
}

}  // namespace gemini
