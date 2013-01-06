#include "Log.h"

using namespace std;

namespace ssvs
{
	vector<string> logEntries;
	vector<string>& getLogEntries() { return logEntries; }

	void saveLogToFile(string mPath)
	{
		ofstream o; o.open(mPath);
		for(string logEntry : logEntries) o << logEntry;
		o.flush(); o.close();
	}
}

