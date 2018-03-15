#include <boost/test/unit_test.hpp>

#include "File.h"
#include "tools/StringUtil.h"

#include <iostream>

BOOST_AUTO_TEST_CASE(t_test_filepath)
{
	using namespace gemini;
	String str = StringUtil::format("中国");
	FilePath path("D:\\HTC");
	BOOST_CHECK(path.isValid());
	BOOST_CHECK(path.isExist());
	BOOST_CHECK(path.isDirectory());
	BOOST_CHECK(path.isFile());

	std::cout << path.getDirectory().c_str() << std::endl;
	std::cout << path.getExtension().c_str() << std::endl;
	std::cout << path.getName().c_str() << std::endl;
	std::cout << path.getNameNotExtension().c_str() << std::endl;

	FilePath parent = path.parent();
	std::vector<FilePath> vecChilds = path.getListFiles();
	std::vector<FilePath> vecAll = path.getAllFiles();

	std::cout << FilePath::currentPath().string().c_str() << std::endl;
	std::cout << FilePath::homePath().string().c_str() << std::endl;
	std::cout << FilePath::tempDirectoryPath().string().c_str() << std::endl;
}

BOOST_AUTO_TEST_CASE(t_test_file)
{
	using namespace gemini;
	File file("D:\\Hello.txt");
	std::cout << file.getFilePath().string().c_str() << std::endl;
	if (file.getFilePath().isExist()) {
		BOOST_CHECK(file.open());
	} else {
		BOOST_CHECK(file.open(std::ios_base::in | std::ios_base::out | std::ios_base::_Nocreate));
	}
}