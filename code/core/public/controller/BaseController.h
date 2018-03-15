#ifndef GEMINI_BaseController_INCLUDE
#define GEMINI_BaseController_INCLUDE
#include "../Object.h"

namespace gemini {

class CORE_API DtoBase
{
public:
	DtoBase() {}
	virtual ~DtoBase() {}

	static const gemini::Class& getClassStatic() { return _class; }
	virtual const gemini::Class& getClass() const { return _class; }

protected:
	virtual gemini::UInt signMaxIndex() { return 0; }

private:
	static const Class _class;
};

class CORE_API BaseController : public Object
{
protected:
	static UInt s_index;
	BaseController();
public:
	typedef SmartPtr<BaseController> SPtr;
	typedef SmartPtr<BaseController, WeakCounted, StorageNo> WPtr;

	virtual ~BaseController();

	static const gemini::Class& getClassStatic() { return _class; }
	virtual const gemini::Class& getClass() const { return _class; }

private:
	static const Class _class;
};

}
#endif // GEMINI_BaseController_INCLUDE
