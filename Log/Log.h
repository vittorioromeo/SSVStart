#ifndef SSVS_LOG
#define SSVS_LOG

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include "Utils/Utils.h"

namespace ssvs
{
	std::vector<std::string>& getLogEntries();
	template<class T> void log(T mValue, std::string mTitle = "")
	{
		#ifndef SSVS_RELEASE
			std::ostringstream entryStream;

			if(mTitle != "") entryStream << "[" << mTitle << "] ";
			entryStream << Utils::toStr(mValue) << std::endl;

			std::cout << entryStream.str();
			getLogEntries().push_back(entryStream.str());
		#endif
	}

	void startBenchmark();
	std::string endBenchmark();

	void saveLogToFile(const std::string& mPath);
}

#endif
