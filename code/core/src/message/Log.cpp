#include "message/Log.h"
#include "tools/File.h"

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, gemini::Logger::Level lvl)
{
	static const char* const str[] = {
		"TRACE",
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FATAL"
	};
	if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
		strm << str[lvl];
	else
		strm << static_cast< int >(lvl);
	return strm;
}

// Declare attribute keywords
BOOST_LOG_ATTRIBUTE_KEYWORD(_severity, "Severity", gemini::Logger::Level)
BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(_uptime, "Uptime", attrs::timer::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(_scope, "Scope", attrs::named_scope::value_type)

namespace gemini {
	
// A logger class that allows to intercept exceptions and supports severity level
class gemini_logger :
	public src::basic_composite_logger<
	char,
	gemini_logger,
	src::single_thread_model,
	src::features<
	src::severity<Logger::Level>,
	src::exception_handler
	>
	>
{
	typedef typename gemini_logger::logger_base base_type;
	BOOST_LOG_FORWARD_LOGGER_MEMBERS(gemini_logger)
public:
	explicit gemini_logger(severity_level level) : base_type(keywords::severity = level) {}
};

Logger::Logger(const char* file, int line, Level level /* = Level::LOG_INFO */)
	: _level(level)
	, _logger(new gemini_logger(level))
{
}

Logger::~Logger(void)
{
}

void Logger::init() {
	FilePath filePath = FilePath::currentPath().append("LOG");
	if (!filePath.isExist())
		filePath.createDirectories();

	static std::string strPath = filePath.string();
	auto file_sink = logging::add_file_log ("sample.log",
		keywords::filter = _severity >= Level::INFO,
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = expr::stream
		<< expr::format_date_time(_timestamp, "%Y-%m-%d, %H:%M:%S.%f")
		<< " [" << expr::format_date_time(_uptime, "%O:%M:%S")
		<< "] [" << expr::format_named_scope(_scope, keywords::format = "%n (%f:%l)")
		<< "] <" << _severity
		<< "> " << expr::message
		/*
		keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
		% expr::format_date_time(_timestamp, "%Y-%m-%d, %H:%M:%S.%f")
		% expr::format_date_time(_uptime, "%O:%M:%S")
		% expr::format_named_scope(_scope, keywords::format = "%n (%f:%l)")
		% _severity
		% expr::message
		*/
	);

	boost::log::core::get()->add_sink(file_sink);
}

void Logger::unInit() {
}

Logger& Logger::log(const Char* str) {
	BOOST_LOG(*_logger) << str;
	return *this;
}

Logger& gemini::Logger::log(const Exception & exc) {
	//BOOST_LOG(*_logger) << exc.what();
	return *this;
}

void Logger::setMinLevel(Level level) {
	boost::log::core::get()->set_filter(
		expr::attr<Level>("Severity").or_default(Level::INFO) >= level // Write all records with "warning" severity or higher
		|| expr::begins_with(expr::attr<std::string>("Tag").or_default(std::string()), "IMPORTANT")); // ...or specifically tagged
}


}