#ifndef GEMINI_INTEGRATION_ExportHelper_INCLUDE
#define GEMINI_INTEGRATION_ExportHelper_INCLUDE
#include "ImportExport.h"
#include "api/IOHelper.h"

namespace gemini {
namespace integration {

class DataSource;
class Scheme;
class GEMINI_INTEGRATION_API ExportHelper : public api::IOHelper {
 public:
  ExportHelper();
  ~ExportHelper();

  void execute();
  void execute(const Class& cls);
  void execute(const Object::SPtr& object);

 private:
  Boolean execute(SmartPtr<Scheme> scheme);
  void handleScheme(SmartPtr<Scheme> scheme);

 private:
  std::shared_ptr<DataSource> _dataSource;
  std::vector<SmartPtr<Scheme>> _schemes;
};

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_ExportHelper_INCLUDE