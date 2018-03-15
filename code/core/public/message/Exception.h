#ifndef GEMINI_Exception_INCLUDE
#define GEMINI_Exception_INCLUDE
#include "../Any.h"

namespace gemini {

class CORE_API log_info
{
public:
	virtual String getName() = 0;

	template <typename T>
	log_info& operator<< (T val) {
		_datas.push_back(val);
		return *this;
	}

private:
	mutable Char const * throw_function_;
	mutable Char const * throw_file_;
	mutable Int throw_line_;
	Long _dtCreated;
	std::vector<Any> _datas;
	friend class Exception;
};
class CORE_API LOG_INFO : public log_info
{
public:
	virtual String getName() override {
		return u8"INFO";
	}
};
class CORE_API LOG_WARNING : public log_info
{
public:
	virtual String getName() override {
		return u8"WARNING";
	}
};
class CORE_API LOG_ERROR : public log_info
{
public:
	virtual String getName() override {
		return u8"ERROR";
	}
};
class CORE_API LOG_FATAL : public log_info
{
public:
	virtual String getName() override {
		return u8"FATAL";
	}
};
class CORE_API TIPS_StrongError : public LOG_ERROR {
public:
	virtual String getName() override {
		return u8"STRONGERROR";
	}
};
class CORE_API TIPS_WEAK : public LOG_INFO {
public:
	virtual String getName() override {
		return u8"TIPS";
	}
};
class CORE_API TIPS_WARNING : public LOG_WARNING {
public:
	virtual String getName() override {
		return u8"WARNINGTIPS";
	}
};

class CORE_API Exception : public std::exception
{
	class exception_error : public LOG_WARNING {
	public:
		virtual String getName() override {
			return u8"";
		}
	};
public:
	Exception();
	~Exception();

	void setInfo(char const * curFun, char const * file, int line);

	template <typename T>
	Exception& operator<< (T val) {
		*_info << val;
		return *this;
	}

	virtual char const* what() const;
	String str() const { return what(); }

	virtual String getName() const { return u8"Exception"; }
private:
	std::shared_ptr<exception_error> _info;
};

class CORE_API ArithmeticExecption : public Exception
{
public:
	virtual String getName() const override { return u8"ArithmeticExecption"; }
};
class CORE_API OperandException : public Exception
{
public:
	virtual String getName() const override { return u8"OperandException"; }
};
class CORE_API NullPointerException : public Exception
{
public:
	virtual String getName() const override { return u8"NullPointerException"; }
};
class CORE_API ClassCastException : public Exception
{
public:
	virtual String getName() const override { return u8"ClassCastException"; }
};
class CORE_API FileNotFoundException : public Exception
{
public:
	virtual String getName() const override { return u8"FileNotFoundException"; }
};
class CORE_API IOException : public Exception
{
public:
	virtual String getName() const override { return u8"IOException"; }
};
class CORE_API NoSuchMethodException : public Exception
{
public:
	virtual String getName() const override { return u8"NoSuchMethodException"; }
};
class CORE_API CircularityException : public Exception
{
public:
	virtual String getName() const override { return u8"CircularityException"; }
};
class CORE_API NoClassDefException : public Exception
{
public:
	virtual String getName() const override { return u8"NoClassDefException"; }
};
class CORE_API UnknownException : public Exception
{
public:
	virtual String getName() const override { return u8"UnknownException"; }
};


#define THROW(ExceptionType) \
	ExceptionType exc##__LINE__; exc##__LINE__.setInfo(__FUNCTION__, __FILE__, __LINE__); throw exc##__LINE__


}
#endif // GEMINI_Exception_INCLUDE