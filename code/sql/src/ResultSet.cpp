#pragma once
#include "../public/ResultSet.h"

namespace gemini
{
namespace sql
{

ResultSet::ResultSet(const Statement &stmt)
{
}

ResultSet::~ResultSet()
{
}

UInt ResultSet::rowCount() const
{
	return 0;
}

UInt ResultSet::columnCount() const
{
	return 0;
}

ResultSet::const_iterator ResultSet::begin() const
{
	return RowIterator(this, 0);
}

ResultSet::iterator ResultSet::begin()
{
	return RowIterator(this, 0);
}

ResultSet::const_iterator ResultSet::end() const
{
	return RowIterator(this, rowCount());
}

ResultSet::iterator ResultSet::end()
{
	return RowIterator(this, rowCount());
}

Boolean ResultSet::moveFirst()
{
	return Boolean();
}

Boolean ResultSet::moveNext()
{
	return Boolean();
}

Boolean ResultSet::movePrevious()
{
	return Boolean();
}

Boolean ResultSet::moveLast()
{
	return Boolean();
}

} // namespace sql
} // namespace gemini