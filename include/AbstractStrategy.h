#pragma once
#include <string>
#include "Package.h"
class Package;
class AbstractStrategy
{
public:
	virtual void process(Package &) = 0;
};

