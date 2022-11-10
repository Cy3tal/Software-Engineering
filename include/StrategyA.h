#pragma once
#include "AbstractStrategy.h"
#include "FileSetUnion.h"
#include <stdio.h>
#include <string>
class StrategyA :
	public AbstractStrategy
{
public:
	void process(Package &) override;
private:
	constexpr static int num_of_examples = 5;
	std::string exampleFileName(int);
	std::string srcFilePath(FileSetUnion &, FileSetUnion::iterator);
	std::string outputFileName(FileSetUnion::iterator,int);
	std::string elfFileName(FileSetUnion::iterator);
	std::string errFileName(FileSetUnion::iterator);

	void createInputFile(Package &);
	void removeFiles(Package &);

	void compile(FileSetUnion &,FileSetUnion::iterator);
	bool checkError(FileSetUnion::iterator);
	void test(FileSetUnion::iterator);
	bool hasSameOutput(FileSetUnion::iterator, FileSetUnion::iterator);

};

