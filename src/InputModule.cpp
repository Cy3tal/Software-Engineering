#include "../include/InputModule.h"
//#include "InputModule.h"
#include <sstream>
#include <algorithm>
using namespace std;
InputModule::InputModule(const string &inputDir)
{
	char cmd[256], buf[256];
	sprintf(cmd, "ls %s", inputDir.c_str());
	string res, subdir;
	if (FILE *fp = popen(cmd, "r")) {
		while (fgets(buf, 256, fp)) res += buf;
	}
	stringstream ss(res);
	while (ss >> subdir) {
		subDirNameList.emplace_back(subdir);
	}
	cur = subDirNameList.cbegin();

	size_t index = inputDir.rfind('/');
	if (index == string::npos) {
		inputDirName = inputDir;
		parentDirPath = "";
	} else {
		inputDirName = inputDir.substr(index + 1);
		parentDirPath = inputDir.substr(0, index+1);
	}
}

InputModule &InputModule::operator>>(Package &package)
{
	if (cur != subDirNameList.cend()) {
		FileSetUnion fset;
		InputInfoList ilist;
		const string &dir = *cur;

		fset.setPath(dir, inputDirName, parentDirPath);

		char cmd[256], buf[256];
		sprintf(cmd, "ls %s", (parentDirPath+inputDirName+'/'+dir).c_str());
		string res, filename;
		if (FILE *fp = popen(cmd, "r")) {
			while (fgets(buf, 256, fp)) res += buf;
		}
		stringstream ss(res);
		while (ss >> filename) {
			if (filename != "stdin_format.txt") {
				fset.insert(filename);
			} else {
				ilist.setFormatFile(parentDirPath + inputDirName + '/' + dir + '/' + filename);
			}
		}
		package.set(fset, ilist);
		++cur;
	}else{
		bad_bit = 1;
	}
	return *this;
}
