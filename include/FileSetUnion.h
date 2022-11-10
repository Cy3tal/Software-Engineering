#pragma once
#include <unordered_map>
#include <string>
class FileSetUnion
{
public:
	using container_type = std::unordered_map<std::string, std::string>;
	using iterator = container_type::iterator;
	void insert(const std::string &filename);
	iterator begin();
	iterator end();
	bool isEqual(const std::string &s0, const std::string &s1);
	bool isEqual(iterator it0, iterator it1);
	bool isError(const std::string &s);
	bool isError(iterator it);
	void setError(const std::string &s);
	void setError(iterator it);
	void setEqual(const std::string &s0, const std::string &s1);
	void setEqual(iterator it0, iterator it1);

	void setPath(const std::string &subdir, const std::string &inputdir, const std::string &parentdir);
	const std::string &getSubDirName() const;
	const std::string &getInputDirName() const;
	const std::string &getParentDirPath() const;
private:
	container_type container;
	std::string subDirName, inputDirName, parentDirPath;
	const std::string &find(const std::string &str);
};

