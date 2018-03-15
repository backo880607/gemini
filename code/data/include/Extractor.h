#pragma once
#include "StatementImpl.h"

namespace gemini {
namespace data {

class Extractor 
{
public:
	Extractor();
	virtual ~Extractor();

	virtual Boolean isNull(Int col, Int row = -1) = 0;

	virtual Boolean extract(Int pos, Char& val) = 0;
};

}
}