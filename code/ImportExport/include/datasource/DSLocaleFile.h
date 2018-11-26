#ifndef GEMINI_INTEGRATION_DSLocaleFile_INCLUDE
#define GEMINI_INTEGRATION_DSLocaleFile_INCLUDE
#include "../../public/DataSource.h"

namespace gemini {
class File;
namespace integration {

class DSLocaleFile : public DataSource {
 public:
  DSLocaleFile();
  ~DSLocaleFile();

  virtual Boolean open(const String &connection) override;
  virtual void close() override;

  virtual Boolean step() override;
  virtual String getData(Int index) override;

  virtual Boolean write(const Field *fd, const String &data) override;

 private:
  void parseFields();

 private:
  std::shared_ptr<File> _file;
  String::size_type _prevPos;
  String::size_type _curPos;
  String _stream;
  std::vector<String::size_type> _fieldsPos;
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_DSLocaleFile_INCLUDE