#ifndef GEMINI_IO_DataSource_INCLUDE
#define GEMINI_IO_DataSource_INCLUDE
#include "../Object.h"

namespace gemini {
namespace io {

struct DataHeader {
  Int _size;
  Int _version;
  DateTime _time;
};

struct DataConfig {
  String _sepField;
  String _sepEntity;
  String _replaceField;
  String _replaceEntity;
  const Class* _cls;
  const Field* _field;
};

class CORE_API DataSource {
 public:
  DataSource();
  virtual ~DataSource();

  const String& getName() const { return _name; }
  void setName(const String& name) { _name = name; }

  const DataConfig& getConfig() const { return _config; }

  virtual Boolean open(const String& connection) = 0;
  virtual void close() = 0;

  virtual Boolean step() = 0;
  virtual String getData(Int index);
  virtual String getData(const Field* fd);

  virtual Boolean write(const Field* fd, const String& data) = 0;

  Boolean getMatrix() const { return _matrix; }
  void setMatrix(Boolean matrix) { _matrix = matrix; }

 protected:
  Boolean _matrix;
  String _name;
  DataHeader _header;
  DataConfig _config;
};

}  // namespace io
}  // namespace gemini
#endif  // GEMINI_IO_DataSource_INCLUDE
