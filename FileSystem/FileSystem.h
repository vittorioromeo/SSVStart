#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sstream>
#include <functional>
#include <string.h>
#include "../Log/Log.h"

namespace ssvs
{
	namespace FileSystem
	{
		// Helpers
		bool exists(const std::string& mPath);
		bool isFolder(const std::string& mPath);
		bool isRootOrParent(const std::string& mPath);
		std::string getNormalizedPath(const std::string& mPath);
		std::string getFileNameFromFilePath(const std::string& mFilePath, const std::string& mPrefix, const std::string& mSuffix);
		
		// Traversing
		void traverse(const std::string& mPath, std::function<void(std::string, std::string)> mFunction);
		
		// Fills (they fill an existing vector)
		void recursiveFillFiles(std::vector<std::string>& mResult, const std::string& mPath);
		void recursiveFillFilesByExtension(std::vector<std::string>& mResult, const std::string& mPath, const std::string& mExtension);
		void recursiveFillFolders(std::vector<std::string>& mResult, const std::string& mPath);
		void recursiveFillAll(std::vector<std::string>& mResult, const std::string& mPath);

		// Lists (they return a vector)
		std::vector<std::string> listFiles(const std::string& mPath);
		std::vector<std::string> listFilesByExtension(const std::string& mPath, const std::string& mExtension);
		std::vector<std::string> listFolders(const std::string& mPath);
		std::vector<std::string> listAll(const std::string& mPath);
		std::vector<std::string> listRecursiveFiles(const std::string& mPath);
		std::vector<std::string> listRecursiveFilesByExtension(const std::string& mPath, const std::string& mExtension);
		std::vector<std::string> listRecursiveFolders(const std::string& mPath);
		std::vector<std::string> listRecursiveAll(const std::string& mPath);
	}
}

#endif // FILESYSTEM_H
