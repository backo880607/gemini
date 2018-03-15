#ifndef GEMINI_Json_INCLUDE
#define GEMINI_Json_INCLUDE
#include "../api/DataNode.h"

namespace gemini {

class CORE_API JsonNode : public DataNode
{
public:
	JsonNode() {}
	JsonNode(const DataNode& node) : DataNode(node) {}
	~JsonNode() {}
	JsonNode& operator= (const DataNode& node) { DataNode::operator=(node); return *this; }
};

class CORE_API JsonFile
{
	typedef JsonNode::node_type node_type;
public:
	enum class File_Mode { FM_NormalFile = 1, FM_CreateFile, FM_ClearFile, };

	JsonFile(const String& name, File_Mode mode = File_Mode::FM_NormalFile);
	~JsonFile();

	Boolean open(const String& name, File_Mode mode = File_Mode::FM_NormalFile);
	Boolean valid() const { return !_ptree; }

	void write() { write(_fileName); }
	void write(const String& name, File_Mode mode = File_Mode::FM_NormalFile);

	DataNode getNode();
	DataNode getNode(const Char* tagName);
	DataNode getNode(const String& tagName) { return getNode(tagName.c_str()); }

	DataNode createNode(const Char* tagName);
	DataNode createNode(const String& tagName) { return createNode(tagName.c_str()); }

	void remove();
private:
	Boolean ProJsonFile(String& path, File_Mode mode);
private:
	std::unique_ptr<node_type> _ptree;
	String _fileName;
};

class CORE_API Json {
public:
	typedef JsonNode::node_type node_type;

	Json();
	Json(const Char* val);
	~Json();

	Boolean valid() const { return !_ptree; }

	void write(std::basic_ostream<Char>& ss, Boolean bPretty = false);
	void read(std::basic_istream<Char>& ss);

	DataNode getNode();
	DataNode getNode(const Char* tagName);
	DataNode getNode(const String& tagName) { return getNode(tagName.c_str()); }

	DataNode createNode(const Char* tagName);
	DataNode createNode(const String& tagName) { return createNode(tagName.c_str()); }
private:
	std::unique_ptr<node_type> _ptree;
};

}
#endif // GEMINI_Json_INCLUDE