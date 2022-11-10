#pragma once
#include <string>
#include <vector>
#include <fstream>
class InputInfo
{
public:
	InputInfo(){}
	InputInfo(const std::string &t, int min, int max)
		:type(t), min(min), max(max) {}
	std::string createInput();
private:
	std::string type;
	int min;
	int max;
};

class InputInfoList
{
	using info_container_type = std::vector<InputInfo>;
	using example_container_type = std::vector<std::string>;
public:
	InputInfoList(){}
	InputInfoList(const std::string &filename);
	void setFormatFile(const std::string &filename);
	void generateNewExamples();
	const example_container_type &getInputExamples() const
	{
		return exampleList;
	}
private:
	info_container_type infoList;
	example_container_type exampleList;
};


