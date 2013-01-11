#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>
#include "../Utils/Utils.h"

namespace ssvs
{
	std::vector<std::string>& getLogEntries();
	template<class T> void log(T mValue, std::string mTitle = "")
	{
		std::ostringstream entryStream;

		if(mTitle != "") entryStream << "[" << mTitle << "] ";
		entryStream << Utils::toStr(mValue) << std::endl;

		std::cout << entryStream.str();
		getLogEntries().push_back(entryStream.str());
	}

	void saveLogToFile(std::string mPath);
}

#endif // LOG_H
