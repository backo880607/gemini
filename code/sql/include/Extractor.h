#ifndef GEMINI_SQL_Extractor_INCLUDE
#define GEMINI_SQL_Extractor_INCLUDE
#include "StatementImpl.h"

namespace gemini
{
namespace sql
{

class Extractor
{
  public:
	Extractor();
	virtual ~Extractor();

	virtual Boolean isNull(Int col, Int row = -1) = 0;

	virtual Boolean extract(Int pos, Char &val) = 0;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Extractor_INCLUDE