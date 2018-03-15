#pragma once
#include "../ConnectionImpl.h"

extern "C"
{
	typedef struct sqlite3 sqlite3;
}

namespace gemini {
namespace data {

class SQLite : public ConnectionImpl
{
public:
	SQLite();
	~SQLite();

    virtual Boolean open() override;
    virtual void close() override;

	virtual std::shared_ptr<StatementImpl> createStatement() override;
    
private:
    sqlite3* _pDB;
};

}
}