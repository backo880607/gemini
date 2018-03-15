#ifndef GEMINI_Log_INCLUDE
#define GEMINI_Log_INCLUDE
#include "../Common.h"

namespace google { class LogMessage; }
namespace gemini {

class CORE_API Logger
{
	typedef std::shared_ptr<google::LogMessage> log_type;
public:
	enum Level {
		L_INFO = 0,
		L_WARNING,
		L_ERROR,
		L_FATAL,
		L_DEF
	};
	Logger(const char* file, int line, Level level = Level::L_INFO);
	~Logger(void);

	Logger& log(const Char* str);
	Logger& log(const String& str) { return log(str.c_str()); }
	Logger& log(std::exception& exc) { return log(exc.what()); }
	template <typename T>
	Logger& log(T val) {
		return log(StringUtil::format(val));
	}

	static void setMinLevel(Level level);

private:
	static void init();
	static void unInit();

protected:
	log_type m_log;
};

#define LOG_INFO Logger(__FILE__, __LINE__, Logger::Level::L_INFO)
#define LOG_WARNING	Logger(__FILE__, __LINE__, Logger::Level::L_WARNING)
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::Level::L_ERROR)
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::Level::L_FATAL)


}
#endif // GEMINI_Log_INCLUDE