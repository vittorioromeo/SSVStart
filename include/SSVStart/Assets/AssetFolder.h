// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETFOLDER
#define SSVS_ASSETS_ASSETFOLDER

#include <vector>
#include <string>

namespace ssvs
{
	class AssetManager;

	class AssetFolder
	{
		private:
			std::string rootPath;
			std::vector<std::string> files;

			std::vector<std::string> getFilteredFiles(const std::vector<std::string>& mExtensions);
			void loadFontsToManager(AssetManager& mAssetManager);
			void loadImagesToManager(AssetManager& mAssetManager);
			void loadSoundsToManager(AssetManager& mAssetManager);
			void loadMusicsToManager(AssetManager& mAssetManager);

		public:
			AssetFolder(const std::string& mRootPath);
			void loadToManager(AssetManager& mAssetManager);
	};
}

#endif
