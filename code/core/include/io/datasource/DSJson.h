#ifndef GEMINI_IO_DSJson_INCLUDE
#define GEMINI_IO_DSJson_INCLUDE
#include "../../../public/io/DataSource.h"
#include "../../../public/tools/Json.h"

namespace gemini {
namespace io {

class DSJson : public DataSource {
 public:
  DSJson();
  virtual ~DSJson();

  virtual Boolean open(const String &connection) override;
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
  virtual Boolean open(const String &connection) override;
  virtual void close() override;

 private:
  std::shared_ptr<JsonFile> _jsonFile;
};

}  // namespace io
}  // namespace gemini
#endif  // GEMINI_IO_DSJson_INCLUDE