#pragma once
#include <iostream>
#include <vector>
#include "Package.h"
class InputModule
{
public:
	using container_type = std::vector<std::string>;
	using iterator = container_type::iterator;
	using const_iterator = container_type::const_iterator;

	InputModule(const std::string &input);
	InputModule &operator>>(Package &);
	operator bool() { return !bad_bit;}
private:
	container_type subDirNameList;
	const_iterator cur;
	std::string inputDirName;
	std::string parentDirPath;
	bool bad_bit = 0;
};

