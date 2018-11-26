#ifndef GEMINI_EntityFactory_INCLUDE
#define GEMINI_EntityFactory_INCLUDE
#include "Object.h"

namespace gemini {

class Class;
class EntityFactory final {
 public:
  enum class Relation { OneToOne, OneToMulti, MultiToOne, MultiToMulti };
  struct Data {
    Boolean storage;             ///< 是否进行持久化
    Boolean owner;               ///< 是否为拥有关系
    Int sign;                    ///< 字段标识
    Int relaSign;                ///< 关联字段标识
    Relation rela;               ///< 关联类型
    EntityFactory* relaFactory;  ///< 关联工厂类
    RefKind kind;                ///< 字段结构类型
    String name;                 ///< 字段名称
  };

  EntityFactory(const Class& cls);
  ~EntityFactory();

  const Class& getEntityClass() const { return _cls; }

  EntityFactory* getSuper() const { return _super; }

  Int getRelaSign(const String& signName) const;
  const Data* getRelaData(Int sign) const;
  const Data* getRelaData(const String& signName) const;

  void createRelation(const BaseEntity::SPtr& entity);

 private:
  friend class FactoryMgr;
  const Class& _cls;
  BaseEntity::SPtr _all;
  EntityFactory* _super;
  std::vector<EntityFactory*> _childs;
  std::map<Int, Data> _relations;
};

}  // namespace gemini
#endif  // GEMINI_EntityFactory_INCLUDE