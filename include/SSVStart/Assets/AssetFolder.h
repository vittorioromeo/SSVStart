// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETFOLDER
#define SSVS_ASSETS_ASSETFOLDER

#include <vector>
#include <string>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class AssetManager;

	class AssetFolder
	{
		private:
			Path rootPath;
			std::vector<Path> files;

			std::vector<Path> getFilteredFiles(const std::vector<std::string>& mExtensions);
			void loadFontsToManager(AssetManager& mAssetManager);
			void loadImagesToManager(AssetManager& mAssetManager);
			void loadTexturesToManager(AssetManager& mAssetManager);
			void loadSoundBuffersToManager(AssetManager& mAssetManager);
			void loadMusicsToManager(AssetManager& mAssetManager);
			void loadShadersToManager(AssetManager& mAssetManager);

		public:
			AssetFolder(const ssvu::FileSystem::Path& mRootPath);
			void loadToManager(AssetManager& mAssetManager);
	};
}

#endif
