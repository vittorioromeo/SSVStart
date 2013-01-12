#include "Log.h"

using namespace std;

namespace ssvs
{
	vector<string> logEntries;
	vector<string>& getLogEntries() { return logEntries; }

	void saveLogToFile(const string& mPath)
	{
		ofstream o; o.open(mPath);
		for(auto& logEntry : logEntries) o << logEntry;
		o.flush(); o.close();
	}
}

