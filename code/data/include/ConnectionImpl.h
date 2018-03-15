#pragma once
#include "../public/SQLConfig.h"

namespace gemini {
namespace data {

class StatementImpl;
class ConnectionImpl
{
	ConnectionImpl(const ConnectionImpl&) = delete;
	ConnectionImpl& operator= (const ConnectionImpl&) = delete;
protected:
	ConnectionImpl() {}
public:
	virtual ~ConnectionImpl() { close(); }

	const SQLConfig& getConfig() const { return _config; }

	virtual Boolean open() = 0;
    virtual Boolean open(const SQLConfig& config);
	virtual void close() {}

	virtual std::shared_ptr<StatementImpl> createStatement() = 0;

private:
    SQLConfig _config;
};

}
}