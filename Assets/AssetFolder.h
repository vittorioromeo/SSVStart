#ifndef ASSETFOLDER_H
#define ASSETFOLDER_H

#include <string>
#include "../Log/Log.h"
#include "../FileSystem/FileSystem.h"
#include "AssetManager.h"

namespace ssvs
{
	class AssetFolder
	{
		private:
			std::string rootPath;
			std::vector<std::string> files;

			std::vector<std::string> getFilteredFiles(const std::vector<std::string> mExtensions);
			void loadImagesToManager(AssetManager& mAssetManager);
			void loadSoundsToManager(AssetManager& mAssetManager);
			void loadMusicsToManager(AssetManager& mAssetManager);
			
		public:
			AssetFolder(const std::string& mRootPath);
			void loadToManager(AssetManager& mAssetManager);
	};
}

#endif // ASSETFOLDER_H
