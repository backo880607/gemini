#ifndef GEMINI_INTEGRATION_DSJson_INCLUDE
#define GEMINI_INTEGRATION_DSJson_INCLUDE
#include "../../public/DataSource.h"
#include "tools/Json.h"

namespace gemini {
namespace integration {

class DSJson : public DataSource {
 public:
  DSJson();
  virtual ~DSJson();

  virtual Boolean validConnection(const Source::SPtr& source,
                                  const String& tblName) override;
  virtual Boolean open(const Source::SPtr& source,
                       const String& tblName) override;
  virtual void close() override;

  virtual Boolean step() override;
  virtual String getData(const Field *fd) override;

  virtual Boolean write(const Field *fd, const String &data) override;

 protected:
  Int _index;
  std::vector<DataNode> _datas;

 private:
  Json _json;
};

class DSJsonFile : public DSJson {
 public:
  DSJsonFile();
  ~DSJsonFile();
  virtual Boolean validConnection(const Source::SPtr& source,
                                  const String& tblName) override;
  virtual Boolean open(const Source::SPtr& source,
                       const String& tblName) override;
  virtual void close() override;

 private:
  std::shared_ptr<JsonFile> _jsonFile;
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_DSJson_INCLUDE