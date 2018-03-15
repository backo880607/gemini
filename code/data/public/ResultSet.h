#pragma once
#include "Statement.h"
#include "RowIterator.h"

namespace gemini {
namespace data {

class ResultSetImpl;
class GEMINI_DATA_API ResultSet
{
	typedef std::shared_ptr<ResultSetImpl> impl_type;
public:
	typedef RowIterator		iterator;
	typedef const iterator	const_iterator;

public:
	ResultSet(const Statement& stmt);
	~ResultSet();

	UInt rowCount() const;
	UInt columnCount() const;

	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();
	Boolean moveFirst();
	Boolean moveNext();
	Boolean movePrevious();
	Boolean moveLast();

private:
	impl_type _impl;
};

}
}