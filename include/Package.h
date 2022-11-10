#pragma once
#include "FileSetUnion.h"
#include "InputInfoList.h"
class Package
{
	using f_type = FileSetUnion;
	using i_type = InputInfoList;
public:
	Package() {};
	Package(f_type &f, i_type &i)
		:package(f, i) {}
	void set(f_type &f, i_type &i)
	{
		package = std::make_pair(f, i);
	}
	f_type &fileSetUnion()
	{
		return package.first;
	}
	i_type &inputInfoList()
	{
		return package.second;
	}
private:
	std::pair < f_type , i_type > package;
};

