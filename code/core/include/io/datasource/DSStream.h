#ifndef GEMINI_DSStream_INCLUDE
#define GEMINI_DSStream_INCLUDE
#include "../../../public/io/DataSource.h"

namespace gemini {
namespace io {

class DSStream : public DataSource {
 public:
  DSStream();
  virtual ~DSStream();

  virtual Boolean open(const String &connection) override;
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

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_DSStream_INCLUDE