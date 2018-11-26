#ifndef GEMINI_INTEGRATION_DSStream_INCLUDE
#define GEMINI_INTEGRATION_DSStream_INCLUDE
#include "../../public/DataSource.h"

namespace gemini {
namespace integration {

class DSStream : public DataSource {
 public:
  DSStream();
  virtual ~DSStream();

  virtual Boolean validConnection(const Source::SPtr& source,
                                  const String& tblName) override;
  virtual Boolean open(const Source::SPtr& source,
                       const String& tblName) override;
  virtual void close() override;

  virtual Boolean step() override;
  virtual String getData(Int index) override;

  virtual Boolean write(const Field *fd, const String &data) override;

 private:
  void parseFields();

 private:
  String::size_type _prevPos;
  String::size_type _curPos;
  String _stream;
  std::vector<String::size_type> _fieldsPos;
};

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_DSStream_INCLUDE