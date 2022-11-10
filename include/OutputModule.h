#pragma once
#include <string>
#include "Package.h"
class OutputModule
{
public:
	OutputModule(const std::string &parentDir);
	OutputModule &operator<<(Package &);
private:
	constexpr static const char 
		eqFileName[] = "equal.csv", 
		ineqFileName[] = "inequal.csv", 
		errFileName[] = "abnormal.csv",
		outputDirName[] = "output",
		inputDirName[] = "input";
	std::string eqFilePath, ineqFilePath, errFilePath, outputDirPath;
	void makeOutputDir(const std::string &parentDir);
	void out2err(FileSetUnion &fset,FileSetUnion::iterator it);
	void out2eq(FileSetUnion &fset, FileSetUnion::iterator it0,FileSetUnion::iterator it1);
	void out2ineq(FileSetUnion &fset, FileSetUnion::iterator it0,FileSetUnion::iterator it1);
	std::string toRelaPath(FileSetUnion &fset, FileSetUnion::iterator it);
};

