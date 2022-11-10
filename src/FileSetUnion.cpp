#include "../include/FileSetUnion.h"
//#include "FileSetUnion.h"
using namespace std;
void FileSetUnion::insert(const string &filename)
{
	container[filename] = filename;
}

FileSetUnion::iterator FileSetUnion::begin()
{
	return container.begin();
}

FileSetUnion::iterator FileSetUnion::end()
{
	return container.end();
}

bool FileSetUnion::isEqual(const string &s0, const string &s1)
{
	return find(s0) == find(s1);
}

bool FileSetUnion::isEqual(iterator it0, iterator it1)
{
	return find(it0->first) == find(it1->first);
}

bool FileSetUnion::isError(const std::string &s)
{
	return container[s].empty();
}

bool FileSetUnion::isError(iterator it)
{
	return it->second.empty();
}

void FileSetUnion::setError(const std::string &s)
{
	container[s] = "";
}

void FileSetUnion::setError(iterator it)
{
	it->second = "";
}

void FileSetUnion::setEqual(const std::string &s0, const std::string &s1)
{
	auto p = container.find(s0);
	p->second = s1;
}

void FileSetUnion::setEqual(iterator it0, iterator it1)
{
	setEqual(it0->first, it1->first);
}

void FileSetUnion::setPath(const std::string &subdir, const std::string &inputdir, const std::string &parentdir)
{
	subDirName = subdir;
	inputDirName = inputdir;
	parentDirPath = parentdir;
}

const std::string &FileSetUnion::getSubDirName() const
{
	return subDirName;
}

const std::string &FileSetUnion::getInputDirName() const
{
	return inputDirName;
}

const std::string &FileSetUnion::getParentDirPath() const
{
	return parentDirPath;
}

const string &FileSetUnion::find(const std::string &str)
{
	auto p = container.find(str);
	if (p->first!=p->second) {
		p->second = find(p->second);
	}
	return p->second;
}




