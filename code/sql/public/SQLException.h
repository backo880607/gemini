#ifndef GEMINI_SQL_SQLException_INCLUDE
#define GEMINI_SQL_SQLException_INCLUDE
#include "SQLExport.h"
#include "message/Exception.h"

namespace gemini {

namespace sql {

class GEMINI_SQL_API ConnectionException : public Exception {
  virtual String getName() const override { return "Connection"; }
};
class GEMINI_SQL_API DataBaseException : public Exception {
  virtual String getName() const override { return "DataBase"; }
};
class GEMINI_SQL_API UnknownTypeException : public Exception {
  virtual String getName() const override { return "UnknownType"; }
};
class GEMINI_SQL_API ExecutionException : public Exception {
  virtual String getName() const override { return "Execution"; }
};
class GEMINI_SQL_API LimitException : public Exception {
  virtual String getName() const override { return "Limit"; }
};
class GEMINI_SQL_API NotSupportedException : public Exception {
  virtual String getName() const override { return "NotSupported"; }
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLException_INCLUDE