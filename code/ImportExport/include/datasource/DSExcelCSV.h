#ifndef GEMINI_INTEGRATION_DSExcelCSV_INCLUDE
#define GEMINI_INTEGRATION_DSExcelCSV_INCLUDE
#include "../../public/DataSource.h"

namespace gemini {
class File;
namespace integration {

class DSExcelCSV : public DataSource {
 public:
  DSExcelCSV();
  virtual ~DSExcelCSV();

  virtual Boolean validConnection(const Source::SPtr& source,
                                  const String& tblName) override;
  virtual Boolean open(const Source::SPtr& source,
                       const String& tblName) override;
  virtual void close() override;

  virtual Boolean step() override;
  virtual String getData(Int index) override;

  virtual Boolean write(const Field* fd, const String& data) override;

 private:
  std::shared_ptr<File> _file;
  std::vector<String> _rowDatas;
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_DSExcelCSV_INCLUDE
