#pragma once
#include "..\..\include\Connection.h"

namespace gemini {
namespace data {

class MySQL : public Connection
{
public:
    virtual Boolean open() override;

    virtual void close() override;

private:
    MYSQL* _impl;
};

}
}