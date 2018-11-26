#ifndef GEMINI_SQL_AdoCommon_INCLUDE
#define GEMINI_SQL_AdoCommon_INCLUDE
#include "Common.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename_namespace("ADODB") rename("BOF", "adoBOF") rename("EOF", "adoEOF")

namespace gemini {
namespace sql {

class AdoError {
 public:
  static String format(const _com_error& e);
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoCommon_INCLUDE