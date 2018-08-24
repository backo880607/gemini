#ifndef GEMINI_IO_ImportHelper_INCLUDE
#define GEMINI_IO_ImportHelper_INCLUDE
#include "IOHelper.h"

namespace gemini {
class DataNode;
namespace io {

class IOScheme;
class CORE_API ImportHelper : public IOHelper {
 public:
  ImportHelper();
  ~ImportHelper();

  void addScheme(SmartPtr<IOScheme> scheme) { _schemes.push_back(scheme); }
  void clearScheme() {
    _schemes.clear();
    _dataSource = nullptr;
  }

  void execute();

 private:
  Boolean parseIOScheme(SmartPtr<IOScheme> scheme);
  std::map<Int, const Field*> parsePrimaries(SmartPtr<IOScheme> scheme);
  String obtainValue(Int index, const Field* field);
  String obtainPrimary(const std::map<Int, const Field*>& primaries);

 private:
  std::vector<SmartPtr<IOScheme>> _schemes;
};

class CORE_API DtoParseHelper : public DtoHelper {
 public:
  DtoParseHelper();
  ~DtoParseHelper();

  //Object::SPtr read();

 private:
  Object::SPtr parseObject(const Class& cls, const DataNode& dataNode);
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_ImportHelper_INCLUDE