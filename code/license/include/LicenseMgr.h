#pragma once
#include <string>
#include <memory>
#include <atomic>

namespace APSUTIL {

class AuthorizeManager
{
public:
	AuthorizeManager() : _valid(false), _curCount(0) {}
	~AuthorizeManager() {}

	static AuthorizeManager& instance() { static AuthorizeManager mgr; return mgr; }

	bool Valid() { return _valid; }

	int GetCurCount() const { return _curCount; }
	void SetCurCount(int count) { _curCount = count; }
	void IncrementCurCount() { ++_curCount; }
	void DecrementCurCount() { --_curCount; }

private:
	friend class AuthorizeCheck;
	friend class Authorize;
	std::atomic_bool _valid;
	std::atomic_int _curCount;
};

}