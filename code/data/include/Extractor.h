#ifndef GEMINI_SQL_Extractor_INCLUDE
#define GEMINI_SQL_Extractor_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class StatementImpl;
class GEMINI_SQL_API Extractor {
 public:
  Extractor(StatementImpl* stmt);
  virtual ~Extractor();

  void extract(Boolean &value);
  void extract(Char &value);
  void extract(Short &value);
  void extract(Int &value);
  void extract(Long &value);
  void extract(Float &value);
  void extract(Double &value);
  void extract(String &value);
  void extract(DateTime &value);
  void extract(Duration &value);
  void extract(DurationExtend &value);

 private:
  StatementImpl *_stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Extractor_INCLUDE