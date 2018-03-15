#pragma once
#include "SQLConfig.h"

namespace gemini {
namespace data {

class ConnectionImpl;
class GEMINI_DATA_API Connection 
{
	typedef std::shared_ptr<ConnectionImpl> impl_type;
public:
    virtual Boolean open();
    virtual Boolean open(const SQLConfig& config);

    virtual void close();

private:
	friend class Statement;
	impl_type _impl;
};

}
}