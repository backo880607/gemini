#include "Object.h"
#include "dao/DaoUtil.h"
#include "entities/IocRelation.h"
#include "entities/RefBase.h"
#include "message/Exception.h"
#include "tools/StringUtil.h"

#include <atomic>
#include <chrono>

namespace gemini {

void *createObject() { return nullptr; }
const Class Object::s_class("Object", nullptr, createObject, nullptr);
Int Object::s_index = 0;

static const std::chrono::steady_clock::time_point s_startTime;
class IDGenerator final {
  IDGenerator() : _lastMilliseconds(0), _logicSlice(0), _seq_id(0) {
    tm t1;
    t1.tm_year = 2018 - 1900;
    t1.tm_mon = 8 - 1;
    t1.tm_mday = 1;
    t1.tm_hour = 0;
    t1.tm_min = 0;
    t1.tm_sec = 0;
    _startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now() -
                     std::chrono::system_clock::from_time_t(mktime(&t1)))
                     .count();

    _lastMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now().time_since_epoch())
                            .count();
  }

 public:
  ~IDGenerator() {}
  static IDGenerator &instance() {
    static IDGenerator obj;
    return obj;
  }

  ID getID(ID id = 0) {
    if (0 != id) return id;

    Long totalMilliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch())
            .count();
    Long seqID = 0;
    if (totalMilliseconds > _lastMilliseconds) {
      _startTime += (totalMilliseconds - _lastMilliseconds);
      _lastMilliseconds = totalMilliseconds;
      _seq_id = 0;
    } else {
      seqID = ++_seq_id;
      if ((seqID >> 10) > 0) {
        THROW(SystemExecption, "generator id error!")
      }
    }

    id |= (_startTime << 22);
    id |= (_logicSlice << 10);
    id |= seqID;
    return id;
  }
  Long getLogicalSlice() const { return _logicSlice; }

 private:
  Long _startTime;
  Long _lastMilliseconds;
  Long _logicSlice;
  Long _seq_id;
};

const Class BaseEntity::_class("BaseEntity", &Object::getClassStatic(),
                                 createObject, nullptr);
Int BaseEntity::s_index = ++Object::s_index;
BaseEntity::BaseEntity()
    : _modified(true), _id(IDGenerator::instance().getID()) {
  static __register_field__ regEntityObjectId(
      Class::forType<ID>(), __OFFSET__(BaseEntity, _id),
      Class::forName("BaseEntity"), "id");
}

BaseEntity::~BaseEntity() {
  for (RefBase *ref : _relations) {
    delete ref;
  }
}

Boolean BaseEntity::operator==(const Any &rhs) const { return Boolean(); }

Boolean BaseEntity::operator<(const Any &rhs) const { return Boolean(); }

DECLARE_CLASS_IMPL(Entity, BaseEntity)

Boolean IList::operator==(const Any &rhs) const {
  if (!rhs.isType<IList>()) {
    return false;
  }
  const IList &rhsList = rhs.cast<IList>();
  IList::Iterator iter = iterator();
  IList::Iterator rhsIter = rhsList.iterator();
  while (iter.hasNext()) {
    BaseEntity::SPtr entity = iter.next<BaseEntity>();
    if (rhsIter.hasNext()) {
      BaseEntity::SPtr rhsEntity = iter.next<BaseEntity>();
      if (entity->getID() != rhsEntity->getID()) {
        break;
      }
    } else {
      break;
    }
  }
  return rhsIter.hasNext() ? false : true;
}

BaseEntity::SPtr IList::Iterator::nextImpl() { return nullptr; }

BaseEntity::SPtr EntityHelper::createImpl(const Class &cls, ID id) const {
  return DaoUtil::create(cls, id);
}

BaseEntity::SPtr EntityHelper::createTempImpl(const Class &cls) const {
  return DaoUtil::createTemp(cls);
}

BaseEntity::SPtr EntityHelper::getImpl(const Class &cls) const {
  return DaoUtil::get(cls);
}

BaseEntity::SPtr EntityHelper::getImpl(const Class &cls, ID id) const {
  return DaoUtil::get(cls, id);
}

BaseEntity::SPtr EntityHelper::getInheritImpl(const Class &cls, ID id) const {
  BaseEntity::SPtr entity = getImpl(cls, id);
  if (entity.valid()) {
    return entity;
  }

  return nullptr;
}

thread_local RefVector ddddddd = RefVector();
const IList &EntityHelper::getListImpl(const Class &cls) const {
  return DaoUtil::getList(cls);
}

void EntityHelper::eraseImpl(BaseEntity::SPtr entity) const {
  DaoUtil::erase(entity->getClass(), entity->getID());
}

void EntityHelper::clearImpl(const Class &cls) const { DaoUtil::clear(cls); }

BaseEntity::SPtr EntityHelper::getImpl(BaseEntity::SPtr entity,
                                         const std::vector<Int> &signs) const {
  return IocRelation::get(entity, signs);
}

const IList &EntityHelper::getListImpl(BaseEntity::SPtr entity,
                                       const std::vector<Int> &signs) const {
  return IocRelation::getList(entity, signs);
}

void EntityHelper::setImpl(BaseEntity::SPtr entity, Int sign,
                           BaseEntity::SPtr relaEntity) const {
  IocRelation::set(entity, sign, relaEntity);
}

void EntityHelper::removeImpl(BaseEntity::SPtr entity, Int sign) const {
  IocRelation::remove(entity, sign);
}

void EntityHelper::removeImpl(BaseEntity::SPtr entity, Int sign,
                              BaseEntity::SPtr relaEntity) const {
  IocRelation::remove(entity, sign, relaEntity);
}

void EntityHelper::sync() const { DaoUtil::sync(); }

}  // namespace gemini