#include "Tool.h"

std::vector<std::string> readTFile(std::string fileName)
{
	std::vector<std::string> fileData;
	std::fstream file(fileName, std::ios_base::in | std::ios_base::out);

	while (!file.eof())
	{
		std::string fileStrings;
		std::getline(file, fileStrings);
		fileData.push_back(fileStrings);
		fileStrings.clear();
	}

	file.close();
	return fileData;
}
