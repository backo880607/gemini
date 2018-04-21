#ifndef GEMINI_File_INCLUDE
#define GEMINI_File_INCLUDE
#include "../Common.h"

#include <fstream>

namespace boost { namespace filesystem { class path; } }

namespace gemini {

class CORE_API FilePath
{
private:
	typedef std::shared_ptr<boost::filesystem::path> path_type;

	FilePath(const boost::filesystem::path& path);
public:
	FilePath(const Char* str);
	FilePath(const FilePath& path);
	FilePath& operator= (const FilePath& path);
	~FilePath();

	String string() const;
	void reset(const String& path);

	Boolean valid() const;

	FilePath& append(const Char* name);

	String getDirectory() const;
	String getName() const;
	String getExtension() const;
	String getNameNotExtension() const;

	Boolean isAbsolute() const;
	Boolean isRelative() const;
	Boolean isFile() const;
	Boolean isDirectory() const;
	Boolean isExist() const;

	FilePath parent() const;

	std::vector<FilePath> getChildren() const;
	std::vector<FilePath> getChildrenRecursion() const;

	Boolean createDirectories();
	Boolean remove();

	static FilePath currentPath();
	static void currentPath(const Char* str);
	static FilePath homePath();
	static FilePath tempDirectoryPath();
	static const Char* separator();

private:
	const boost::filesystem::path& path() const { return *_path; }

private:
	static String s_currentPath;
	friend class File;
	path_type _path;
};

class CORE_API File
{
	explicit File(const File& rhs) : _path(rhs.getFilePath()) {}
	File& operator= (const File& rhs) { return *this; }
public:
	typedef Long pos_type;

public:
	File(const Char* path);
	explicit File(const FilePath& path);
	~File(void);

	const FilePath& getFilePath() const { return _path; }
	void setFilePath(const String& path);

	Long getSize() const;
	File& setSize(Long size);

	Boolean remove() { return _path.remove(); }
	void removeTo(const String& path);
	void copyTo(const String& path);

	Boolean open(std::ios_base::openmode flag = std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
	void close(Boolean bFlush = true);
	Boolean isOpen() const;
	void flush();

	File& write(const Char* str, Boolean bFlush = false) {
		return write(str, strlen(str), bFlush);
	}
	File& write(const Char* str, std::streamsize count, Boolean bFlush = false);
	File& write(const String& str, Boolean bFlush = false) {
		return write(str.c_str(), str.size(), bFlush);
	}
	template <typename T>
	File& write(T val, Boolean bFlush = false) {
		_file << val;
		if (bFlush) flush();
		return *this;
	}

	String readLine();
	template <typename T>
	void read(T& val) { _file >> val; }
	void read(Char* pBuf, Long size);

	Boolean isEnd() const;

	pos_type getWritePos();
	void setWritePos(pos_type pos);
	pos_type getReadPos();
	void setReadPos(pos_type pos);

	void write(File& rhs);

protected:
	FilePath _path;
	std::fstream _file;
};

}
#endif // GEMINI_File_INCLUDE