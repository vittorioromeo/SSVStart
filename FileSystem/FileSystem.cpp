#include "FileSystem.h"

using namespace std;

namespace ssvs
{
	namespace FileSystem
	{
		bool exists(const string& mPath) { struct stat buf; return (stat(getNormalizedPath(mPath).c_str(), &buf) != -1); }
		bool isFolder(const string& mPath)
		{
			struct stat fileStat;
			int err{stat(getNormalizedPath(mPath).c_str(), &fileStat)};
			if (err != 0) return false;
			return (fileStat.st_mode & S_IFMT) == S_IFDIR;
		}
		bool isRootOrParent(const string& mPath) { return (endsWith(mPath, ".") || endsWith(mPath, "..")); }
		string getNormalizedPath(const string& mPath)
		{
			//if(!isFolder(mPath)) return mPath;
			//if(isRootOrParent(mPath)) return mPath;

			string result{mPath};

			while(endsWith(result, R"(\)")) result = result.substr(0, result.size() - 1);
			while(endsWith(result, "/")) result = result.substr(0, result.size() - 1);

			return result;
		}
		string getFileNameFromFilePath(const string& mFilePath, const string& mPrefix, const string& mSuffix)
		{
			return mFilePath.substr(mPrefix.length(), mFilePath.length() - mPrefix.length() - mSuffix.length());
		}

		void traverse(const string& mPath, function<void(string, string)> mFunction)
		{
			DIR *dir{opendir(mPath.c_str())};
			struct dirent *entry{readdir(dir)};

			while (entry != NULL)
			{
				string name{entry->d_name};
				string path{getNormalizedPath(mPath) + "/" + name};

				mFunction(name, path);
				entry = readdir(dir);
			}

			closedir(dir);
		}

		vector<string> listFiles(const string& mPath)
		{
			vector<string> result;
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path)) if(!isFolder(path)) result.push_back(path);
			});
			return result;
		}
		vector<string> listFilesByExtension(const string& mPath, const string& mExtension)
		{
			vector<string> result;
			traverse(mPath, [&](string name, string path){
				if(!isRootOrParent(path)) if(!isFolder(path)) if(endsWith(name, mExtension)) result.push_back(path);
			});
			return result;
		}
		vector<string> listFolders(const string& mPath)
		{
			vector<string> result;
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path)) if(isFolder(path)) result.push_back(path);
			});
			return result;
		}
		vector<string> listAll(const string& mPath)
		{
			vector<string> result;
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path)) result.push_back(path);
			});
			return result;
		}

		void recursiveFillFiles(vector<string>& mResult, const string& mPath)
		{
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path))
				{
					if(isFolder(path)) recursiveFillFiles(mResult, path);
					if(!isFolder(path)) mResult.push_back(path);
				}
			});
		}
		void recursiveFillFilesByExtension(vector<string>& mResult, const string& mPath, const string& mExtension)
		{
			traverse(mPath, [&](string name, string path){
				if(!isRootOrParent(path))
				{
					if(isFolder(path)) recursiveFillFiles(mResult, path);
					if(!isFolder(path)) if(endsWith(name, mExtension)) mResult.push_back(path);
				}
			});
		}
		void recursiveFillFolders(vector<string>& mResult, const string& mPath)
		{
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path))
				{
					if(isFolder(path)) recursiveFillFolders(mResult, path);
					if(isFolder(path)) mResult.push_back(path);
				}
			});
		}
		void recursiveFillAll(vector<string>& mResult, const string& mPath)
		{
			traverse(mPath, [&](string, string path){
				if(!isRootOrParent(path))
				{
					if(isFolder(path)) recursiveFillAll(mResult, path);
					mResult.push_back(path);
				}
			});
		}		
	}
}

