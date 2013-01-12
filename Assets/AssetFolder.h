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
			void initImages(AssetManager& mAssetManager);
			void initSounds(AssetManager& mAssetManager);
			void initMusics(AssetManager& mAssetManager);
			
		public:
			AssetFolder(const std::string& mRootPath);
			void fillManager(AssetManager& mAssetManager);
	};
}

#endif // ASSETFOLDER_H
