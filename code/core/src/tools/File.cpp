#include "tools/File.h"
#include "Buffer.h"
#include "tools/StringUtil.h"

#include <boost/filesystem.hpp>

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <windows.h>
#endif

namespace gemini {

String FilePath::s_currentPath;
FilePath::FilePath(const boost::filesystem::path& path)
	: _path(new boost::filesystem::path(path))
{
}

FilePath::FilePath(const Char* str)
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	: _path(new boost::filesystem::path(StringUtil::utf8_to_unicode(str)))
#else
	: _path(new boost::filesystem::path(str))
#endif // GEMINI_OS
{
	
}

FilePath::FilePath(const FilePath& path)
	: _path(path._path)
{

}

FilePath& FilePath::operator= (const FilePath& path)
{
	_path = path._path;
	return *this;
}

FilePath::~FilePath()
{

}

String FilePath::string() const {
	return _path->string();
}

void FilePath::reset(const String& path) {
	FilePath temp(path.c_str());
	_path = temp._path;
}

Boolean FilePath::valid() const {
	return !_path->empty() && _path->is_complete();
}

FilePath& FilePath::append(const Char* name) {
	*_path /= name;
	return *this;
}

String FilePath::getDirectory() const {
	if (isDirectory())
		return string();

	return _path->parent_path().string();
}

String FilePath::getName() const {
	return _path->filename().string();
}

String FilePath::getExtension() const {
	return _path->extension().string();
}

String FilePath::getNameNotExtension() const {
	String name = getName();
	const String::size_type pos = name.find(".");
	return pos != String::npos ? name.substr(0, pos) : "";
}

Boolean FilePath::isAbsolute() const {
	return _path->is_absolute();
}

Boolean FilePath::isRelative() const {
	return _path->is_relative();
}

Boolean FilePath::isFile() const {
	boost::system::error_code err;
	return boost::filesystem::is_regular_file(path(), err);
}

Boolean FilePath::isDirectory() const {
	boost::system::error_code err;
	return boost::filesystem::is_directory(path(), err);
}

Boolean FilePath::isExist() const {
	boost::system::error_code err;
	return boost::filesystem::exists(path(), err);
}

FilePath FilePath::parent() const {
	return _path->parent_path();
}

std::vector<FilePath> FilePath::getChildren() const {
	std::vector<FilePath> vecPath;
	boost::filesystem::directory_iterator end_iter; // ȱʡ��������һ������������
	for (boost::filesystem::directory_iterator iter(path()); iter != end_iter; ++iter) {
		boost::system::error_code err;
		if (boost::filesystem::is_regular_file(iter->path(), err) && !err) {
			vecPath.push_back(iter->path());
		}
	}

	return vecPath;
}

std::vector<FilePath> FilePath::getChildrenRecursion() const {
	std::vector<FilePath> vecPath;
	boost::filesystem::recursive_directory_iterator end_iter; // ȱʡ��������һ������������
	for (boost::filesystem::recursive_directory_iterator iter(path()); iter != end_iter; ++iter) {
		boost::system::error_code err;
		if (boost::filesystem::is_regular_file(iter->path(), err) && !err) {
			vecPath.push_back(iter->path());
		}
	}

	return vecPath;
}

Boolean FilePath::createDirectories() {
	boost::system::error_code err;
	return boost::filesystem::create_directories(path(), err);
}

Boolean FilePath::remove() {
	boost::system::error_code err;
	return boost::filesystem::remove_all(path(), err) != 0;
}

FilePath FilePath::currentPath() {
	if (s_currentPath.empty()) {
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
		HMODULE dll = (HMODULE)LoadLibraryA("core.dll");
		if (dll)
		{
			Buffer<Char> fileName(MAX_PATH + 1);
			DWORD n = ::GetModuleFileNameA(dll, fileName.begin(), (DWORD)fileName.size());

			if (n > 0) s_currentPath = fileName.begin();
			FreeLibrary(dll);
			s_currentPath.erase(s_currentPath.find_last_of("\\"));
		}
#else
		boost::system::error_code err;
		s_currentPath = boost::filesystem::current_path(err).string();
#endif
	}

	return s_currentPath.c_str();
}

void FilePath::currentPath(const Char* str) {
	s_currentPath = str;
}

FilePath FilePath::homePath() {
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	Char* dir = getenv("USERPROFILE");
#elif GEMINI_OS == GEMINI_OS_LINUX
	Char* dir = getenv("HOME");
#elif GEMINI_OS == GEMINI_OS_MAC_OS_X
	Char* dir = getenv("HOME");
#endif
	return dir == nullptr ? "" : dir;
}

FilePath FilePath::tempDirectoryPath() {
	return boost::filesystem::temp_directory_path();
}

const Char * gemini::FilePath::separator() {
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
	return "/";
#else
	return "/";
#endif
}

File::File(const Char* path)
	: _path(path)
{

}

File::File(const FilePath& path)
	: _path(path)
{

}

File::~File(void)
{
	close();
}

void File::setFilePath(const String& path) {
	_path.reset(path);
}

Long File::getSize() const {
	boost::system::error_code err;
	return boost::filesystem::file_size(_path.path(), err);
}

File& File::setSize(Long size) {
	boost::system::error_code err;
	boost::filesystem::resize_file(_path.path(), size, err);
	return *this;
}

void File::removeTo(const String& path) {
	copyTo(path);
	remove();
}

void File::copyTo(const String& path) {
	boost::system::error_code err;
	boost::filesystem::copy_file(_path.path(), path, err);
}

Boolean File::open(std::ios_base::openmode flag /*= std::ios_base::in | std::ios_base::out | std::ios_base::trunc*/) {
	if (_file.is_open())
		return true;

	return _file.rdbuf()->open(getFilePath().string().c_str(), flag) != nullptr;
}

void File::close(Boolean bFlush /* = true */) {
	if (!_file.fail()) {
		if (bFlush)
			_file.flush();
	}

	_file.clear();
	_file.close();
}

Boolean File::isOpen() const {
	return _file.is_open();
}

void File::flush() {
	_file.flush();
}

File& File::write(const Char* str, std::streamsize count, Boolean bFlush /* = false */) {
	if (!_file.fail()) {
		_file.write(str, count);
		if (bFlush) _file.flush();
	}

	return *this;
}

String File::readLine() {
	Buffer<Char> buffer(10240);
	_file.getline(buffer.begin(), buffer.size());
	return buffer.begin();
}

void File::read(Char* pBuf, Long size) {
	_file.read(pBuf, size);
}

Boolean File::isEnd() const {
	return _file.eof();
}

File::pos_type File::getWritePos() {
	return _file.tellp();
}

void File::setWritePos(pos_type pos) {
	_file.seekp(pos);
}

File::pos_type File::getReadPos() {
	return _file.tellg();
}

void File::setReadPos(pos_type pos) {
	_file.seekg(pos);
}

void File::write(File& rhs) {
	rhs.open();
	_file.seekp(std::ios_base::end);
	while (!rhs.isEnd()) {
		write(rhs.readLine());
	}
}

}