#ifndef GEMINI_INTEGRATION_ImportHelper_INCLUDE
#define GEMINI_INTEGRATION_ImportHelper_INCLUDE
#include "ImportExport.h"
#include "api/IOHelper.h"

namespace gemini {
class DataNode;
namespace integration {

class DataSource;
class Scheme;
class GEMINI_INTEGRATION_API ImportHelper : public api::IOHelper {
  struct EntityData {
    Boolean imported;

    EntityData() : imported(false) {}
  };

 public:
  ImportHelper();
  ~ImportHelper();

  void addScheme(SmartPtr<Scheme> scheme) { _schemes.push_back(scheme); }
  void clearScheme() {
    _schemes.clear();
    _dataSource = nullptr;
  }

  void execute();

 protected:
  Boolean proIOScheme(SmartPtr<Scheme> scheme);
  String obtainValue(Int index, const Field* field);

  void checkKeyFields(SmartPtr<Scheme> scheme);
  BaseEntity::SPtr createEntity(const Class& cls);
  String checkEntity(const std::vector<const Field*>& keyFields,
                     const BaseEntity::SPtr& entity);
  void sureEntity(BaseEntity::SPtr& entity, const String& primary,
                  SmartPtr<Scheme> scheme);

 protected:
  std::shared_ptr<DataSource> _dataSource;
  std::vector<SmartPtr<Scheme>> _schemes;
  api::KeyMapEntity<String, EmptyType, EntityData> _cache;
};

/*class GEMINI_IMPORTEXPORT_EXPORTS DtoParser : public IOHelper {
 public:
  enum class DataType { Init, Json, XML };
  DtoParser();
  ~DtoParser();

  DataType getDataType() const { return _dataType; }
  void setDataType(DataType dataType) { _dataType = dataType; }

  template <class T>
  typename T::SPtr readObject(const String& value) {
    return parseObject(Class::forType<T>(), value);
  }
  template <typename T>
  std::vector<typename T::SPtr> readVector(const String& value) {
    DataNode node = getDataNode(value);
    std::vector<typename T::SPtr> result;
    node.foreach ([&](DataNode subNode) {
      result.push_back(parseObject(Class::forType<T>(), subNode));
    });
    return result;
  }
  template <typename T>
  std::list<typename T::SPtr> readList(const String& value) {
    DataNode node = getDataNode(value);
    std::list<typename T::SPtr> result;
    node.foreach ([&](DataNode subNode) {
      result.push_back(parseObject(Class::forType<T>(), subNode));
    });
    return result;
  }
  template <typename T>
  std::set<typename T::SPtr> readSet(const String& value) {
    DataNode node = getDataNode(value);
    std::set<typename T::SPtr> result;
    node.foreach ([&](DataNode subNode) {
      result.insert(parseObject(Class::forType<T>(), subNode));
    });
    return result;
  }

 private:
  DataNode getDataNode(const String& value);
  Object::SPtr parseObject(const Class& cls, const String& value);
  Object::SPtr parseObject(const Class& cls, const DataNode& dataNode);

 private:
  DataType _dataType;
};*/

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_ImportHelper_INCLUDE