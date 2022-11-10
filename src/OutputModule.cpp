#include "../include/OutputModule.h"
//#include "OutputModule.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;

OutputModule::OutputModule(const string &input)
{
	string parentDir;
	size_t index = input.rfind('/');
	if(index==string::npos){
		parentDir = "";
	}else{
		parentDir = input.substr(0,index+1);
	}
	makeOutputDir(parentDir);
}

OutputModule &OutputModule::operator<<(Package &package)
{
	FileSetUnion &fset = package.fileSetUnion();
	for (auto it = fset.begin(); it != fset.end(); ++it) {
		if (fset.isError(it)) {
			out2err(fset, it);
		}
	}
	for (auto it_i = fset.begin(); it_i != fset.end(); ++it_i)
		for (auto it_j = it_i; it_j != fset.end(); ++it_j) {
			if (it_i==it_j||fset.isError(it_i) || fset.isError(it_j)) {
				continue;
			} else if(fset.isEqual(it_i,it_j)) {
				out2eq(fset, it_i, it_j);
			} else {
				out2ineq(fset, it_i, it_j);
			}
		}
	return *this;
}

void OutputModule::makeOutputDir(const string &parentDir)
{
	char cmd[256];
	outputDirPath = parentDir + outputDirName;
	sprintf(cmd, "rm -rf %s; mkdir %s", outputDirPath.c_str(),outputDirPath.c_str());
	system(cmd);
	eqFilePath = outputDirPath + '/' + eqFileName;
	ineqFilePath = outputDirPath + '/' + ineqFileName;
	errFilePath = outputDirPath + '/' + errFileName;
}

void OutputModule::out2err(FileSetUnion &fset, FileSetUnion::iterator it)
{
	ofstream fp(errFilePath, ios::app);
	fp << toRelaPath(fset, it) << endl;
	fp.close();
}

void OutputModule::out2eq(FileSetUnion &fset, FileSetUnion::iterator it0, FileSetUnion::iterator it1)
{
	ofstream fp(eqFilePath, ios::app);
	fp << toRelaPath(fset, it0) << ',' << toRelaPath(fset, it1) << endl;
	fp.close();
}

void OutputModule::out2ineq(FileSetUnion &fset, FileSetUnion::iterator it0, FileSetUnion::iterator it1)
{
	ofstream fp(ineqFilePath, ios::app);
	fp << toRelaPath(fset,it0) << ',' << toRelaPath(fset, it1) << endl;
	fp.close();
}

string OutputModule::toRelaPath(FileSetUnion &fset, FileSetUnion::iterator it)
{
	return fset.getInputDirName() + '/' + fset.getSubDirName() + '/' + it->first;
}
