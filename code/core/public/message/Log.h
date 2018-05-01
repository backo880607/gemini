#ifndef GEMINI_Log_INCLUDE
#define GEMINI_Log_INCLUDE
#include "../Core.h"

namespace gemini {

class gemini_logger;
class Exception;
class CORE_API Logger
{
	typedef std::shared_ptr<gemini_logger> log_type;
public:
	enum Level {
		TRACE,
		DEBUG,
		INFO,
		WARNING,
		ERROR_,
		FATAL,
	};
	Logger(const char* file, int line, Level level = Level::INFO);
	~Logger(void);

	Logger& log(const Char* str);
	Logger& log(const String& str) { return log(str.c_str()); }
	Logger& log(std::exception& exc) { return log(exc.what()); }
	Logger& log(const Exception& exc);
	template <typename T>
	Logger& log(T val) {
		return log(StringUtil::format(val));
	}

	static void setMinLevel(Level level);

private:
	static void init();
	static void unInit();

protected:
	Level _level;
	log_type _logger;
};

#define LOG_TRACE Logger(__FILE__, __LINE__, Logger::Level::TRACE)
#define LOG_DEBUG Logger(__FILE__, __LINE__, Logger::Level::DEBUG)
#define LOG_INFO Logger(__FILE__, __LINE__, Logger::Level::INFO)
#define LOG_WARNING	Logger(__FILE__, __LINE__, Logger::Level::WARNING)
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::Level::ERROR_)
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::Level::FATAL)


}
#endif // GEMINI_Log_INCLUDE