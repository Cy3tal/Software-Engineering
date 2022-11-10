#include "../include/StrategyA.h"
//#include "StrategyA.h"
#include <omp.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unistd.h>
using namespace std;
void StrategyA::createInputFile(Package &package)
{
	InputInfoList &infolist = package.inputInfoList();
	for (int i = 1; i <= num_of_examples; ++i) {
		ofstream inputFile(exampleFileName(i));
		ostream_iterator<string> out_iter(inputFile, " ");
		infolist.generateNewExamples();
		auto &examples = infolist.getInputExamples();
		copy(examples.begin(), examples.end(), out_iter);
		inputFile.close();
	}
}

void StrategyA::removeFiles(Package &package)
{
	FileSetUnion &fset = package.fileSetUnion();
	for (auto it = fset.begin(); it != fset.end(); ++it)
		for (int i = 1; i <= num_of_examples; ++i) {
			remove(elfFileName(it).c_str());
			remove(errFileName(it).c_str());
			remove(outputFileName(it,i).c_str());
		}
	for (int i = 1; i <= num_of_examples; ++i) {
		remove(exampleFileName(i).c_str());
	}
}

void StrategyA::compile(FileSetUnion &fset, FileSetUnion::iterator it)
{
	char cmd[256];
	sprintf(cmd, "g++ -w -O2 -std=c++17 %s -o %s 2>%s",
			srcFilePath(fset, it).c_str(),
			elfFileName(it).c_str(),
			errFileName(it).c_str()
	);
	system(cmd);
}

bool StrategyA::checkError(FileSetUnion::iterator it)
{
	vector<string> errInfo;
	ifstream tmp(errFileName(it));
	istream_iterator<string> in_it(tmp);
	istream_iterator<string> end;
	copy(in_it, end, back_inserter(errInfo));
	tmp.close();
	return !errInfo.empty();
}

void StrategyA::test(FileSetUnion::iterator it)
{
	for (int i = 1; i <= num_of_examples; ++i) {
		char cmd[256];
		sprintf(cmd, "./%s < %s > %s",
				elfFileName(it).c_str(),
				exampleFileName(i).c_str(),
				outputFileName(it,i).c_str()
		);
		system(cmd);
	}
}


bool StrategyA::hasSameOutput(FileSetUnion::iterator it0, FileSetUnion::iterator it1)
{
	for (int i = 1; i < num_of_examples; ++i) {
		ifstream fp[2]{ ifstream(outputFileName(it0,i)),ifstream(outputFileName(it1,i)) };
		vector<vector<string>> list(2);
		for (int i = 0; i < 2; ++i) {
			istream_iterator<string> in_iter(fp[i]);
			istream_iterator<string> end;
			copy(in_iter, end, back_inserter(list[i]));
		}
		fp[0].close();
		fp[1].close();
		if (list[0] != list[1]) {
			return false;
		}
	}
	return true;
}

void StrategyA::process(Package &package)
{
	createInputFile(package);
	FileSetUnion &fset = package.fileSetUnion();
	vector<FileSetUnion::iterator> iterList;
	for (auto it = fset.begin(); it != fset.end(); ++it){
		iterList.emplace_back(it);//*Iterator invalidation is not considered
	}
	#pragma omp parallel for num_threads(8) shared(fset)
	for (size_t i=0;i<iterList.size();++i) {
		compile(fset, iterList[i]);
	}
	#pragma omp parallel for num_threads(8) shared(fset)
	for (size_t i=0;i<iterList.size();++i) {
		if(checkError(iterList[i])){
			fset.setError(iterList[i]);
		}
	}
	#pragma omp parallel for num_threads(8) shared(fset)
	for (size_t i=0;i<iterList.size();++i) {
		if(!fset.isError(iterList[i])){
			test(iterList[i]);
		}
	}
	for (auto it_i = fset.begin(); it_i != fset.end(); ++it_i)
		for (auto it_j = it_i; it_j != fset.end(); ++it_j) {
			if (it_i == it_j || fset.isError(it_i) || fset.isError(it_j) || fset.isEqual(it_i, it_j)) {
				continue;
			} else if (hasSameOutput(it_i, it_j)) {
				fset.setEqual(it_i, it_j);
			}
		}
	removeFiles(package);
}

std::string StrategyA::exampleFileName(int index)
{
	return "examples_" + to_string(index) + ".txt";
}

std::string StrategyA::srcFilePath(FileSetUnion &fset, FileSetUnion::iterator it)
{
	return fset.getParentDirPath() + fset.getInputDirName() + '/' + fset.getSubDirName() + '/'
		+ it->first;
}

string StrategyA::outputFileName(FileSetUnion::iterator it, int index)
{
	return "out_" + to_string(index) + '_' + it->first.substr(0, it->first.find('.'));
}

std::string StrategyA::elfFileName(FileSetUnion::iterator it)
{
	return "elf_" + it->first.substr(0, it->first.find('.'));
}

std::string StrategyA::errFileName(FileSetUnion::iterator it)
{
	return "err_" + it->first.substr(0, it->first.find('.'));
}
