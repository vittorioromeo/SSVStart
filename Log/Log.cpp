#include <chrono>
#include <fstream>
#include "Log.h"

using namespace std;
using namespace std::chrono;
using namespace ssvs::Utils;

namespace ssvs
{
	vector<string> logEntries;
	time_point<high_resolution_clock> start, end;

	vector<string>& getLogEntries() { return logEntries; }

	void saveLogToFile(const string& mPath)
	{
		#ifndef SSVS_RELEASE
			ofstream o; o.open(mPath);
			for(auto& logEntry : logEntries) o << logEntry;
			o.flush(); o.close();
		#endif
	}
	void startBenchmark()
	{
		#ifndef SSVS_RELEASE
			start = high_resolution_clock::now();
		#endif
	}
	string endBenchmark()
	{
		#ifndef SSVS_RELEASE
			end = high_resolution_clock::now();
			auto elapsed = duration_cast<milliseconds>(end-start).count();
			return toStr(elapsed) + toStr(" ms");
		#endif
	}
}

