#ifndef GEMINI_SQL_Extractor_INCLUDE
#define GEMINI_SQL_Extractor_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class GEMINI_SQL_API Extractor {
 public:
  Extractor();
  virtual ~Extractor();

  virtual Boolean extract(Int pos, Boolean &value) = 0;
  virtual Boolean extract(Int pos, Char &value) = 0;
  virtual Boolean extract(Int pos, Short &value) = 0;
  virtual Boolean extract(Int pos, Int &value) = 0;
  virtual Boolean extract(Int pos, Long &value) = 0;
  virtual Boolean extract(Int pos, Float &value) = 0;
  virtual Boolean extract(Int pos, Double &value) = 0;
  virtual Boolean extract(Int pos, String &value) = 0;
  virtual Boolean extract(Int pos, DateTime &value) = 0;
  virtual Boolean extract(Int pos, Duration &value) = 0;
  virtual Boolean extract(Int pos, DurationExtend &value) = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Extractor_INCLUDE