#include "../include/InputInfoList.h"
//#include "InputInfoList.h"
#include <sstream>
using namespace std;
string InputInfo::createInput()
{
	if (type == "char") {
		int randc = rand() % 26, randu = rand() % 2;
		int base = randu ? 'A' : 'a';
		return { static_cast<char>(base + randc) };
	} else if (type == "int") {
		int ret = rand() % (max + 1) + min;
		return to_string(ret);
	} else if (type == "string") {
		int num = rand() % (max + 1) + min;
		string tmp(num, ' ');
		for (auto it = tmp.begin(); it != tmp.end(); ++it) {
			int randc = rand() % 26, randu = rand() % 2;
			int base = randu ? 'A' : 'a';
			*it = static_cast<char>(base + randc);
		}
		return tmp;
	}
	return "";
}

InputInfoList::InputInfoList(const string &filename)
{
	setFormatFile(filename);
}

void InputInfoList::setFormatFile(const std::string &filename)
{
	infoList.clear();
	ifstream fp(filename);
	if (fp.is_open()) {
		string line;
		while (getline(fp, line)) {
			stringstream ss(line);
			string unit;
			while (ss >> unit) {
				size_t index = unit.find('(');
				if (index != string::npos) {
					int max, min;
					string t = unit.substr(0, index);
					sscanf(unit.substr(index).c_str(), "(%d,%d)", &min, &max);
					infoList.emplace_back(t, min, max);
				} else {
					infoList.emplace_back("char", 0, 0);
				}
				exampleList.emplace_back(infoList.back().createInput());
			}
		}
		fp.close();
	}
}

void InputInfoList::generateNewExamples()
{
	for (size_t i = 0; i < infoList.size(); ++i) {
		exampleList[i] = infoList[i].createInput();
	}
}
