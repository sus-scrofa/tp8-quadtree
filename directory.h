#pragma once
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
class directory
{
public:
	directory(const char* dir);
	~directory();
	std::string getNextPath(std::string extension);
	bool isError();
private:
	bool validateExtension(std::string path, std::string Extension);
	boost::filesystem::path p;
	boost::filesystem::directory_iterator iterator;
	bool error;

};
