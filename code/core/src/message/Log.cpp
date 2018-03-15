#include "../../public/message/Log.h"
#include "../../public/tools/File.h"

#define GOOGLE_GLOG_DLL_DECL
#include <glog/logging.h>
#include <glog/stl_logging.h>

namespace gemini {
	
Logger::Logger(const char* file, int line, Level level /* = Level::LOG_INFO */)
{
	if (level > L_FATAL)
		level = L_INFO;

	m_log = log_type(new google::LogMessage(file, line, level));
}

Logger::~Logger(void)
{
}

void Logger::init()
{
	FilePath filePath = FilePath::currentPath().append("LOG");
	if (!filePath.isExist())
		filePath.createDirectories();

	static std::string strPath = filePath.string();
	FLAGS_log_dir = strPath;
	google::InitGoogleLogging("");
}

void Logger::unInit()
{
	google::ShutdownGoogleLogging();
}

Logger& Logger::log(const Char* str)
{
	m_log->stream() << str;
	return *this;
}

void Logger::setMinLevel(Level level)
{
	FLAGS_minloglevel = level;
}


}