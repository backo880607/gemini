#pragma once
#include "../common/Exception.h"

namespace APSUTIL {

class LicenseNotFound : public Exception {
public:
	DECLARE_ExceptionError(NotFound, EmptyType)
};
class LicenseException : public Exception
{
public:
	DECLARE_ExceptionError(LocaleKey, EmptyType)
	DECLARE_ExceptionError(DiskSerialNo, EmptyType)
	DECLARE_ExceptionError(MacAddr, EmptyType)
	DECLARE_ExceptionError(RandomCode, EmptyType)
	DECLARE_ExceptionError(Authorize, EmptyType)
	DECLARE_ExceptionError(ModifyHardInfo, EmptyType)
	DECLARE_ExceptionError(ModifySystemTime, EmptyType)
	DECLARE_ExceptionError(MaxCount, EmptyType)
};

}