// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETFOLDER
#define SSVS_ASSETS_ASSETFOLDER

#include <vector>
#include <string>
#include <SSVUtils/String/String.hpp>
#include <SSVUtils/Log/Log.hpp>
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/Assets/AssetManager.h"

namespace ssvs
{
	class AssetManager;

	class AssetFolder
	{
		private:
			Path rootPath;
			std::vector<Path> files;

			std::vector<Path> getFilteredFiles(const std::vector<std::string>& mExtensions)
			{
				std::vector<Path> result;
				for(const auto& f : files) for(const auto& e : mExtensions) if(f.hasExtension(e)) result.push_back(f);
				return result;
			}
			void loadFontsToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".ttf", ".otf", ".pfm"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Font>(id, f);
					ssvu::lo("ssvs::AssetFolder::loadFontsToManager(" + rootPath.getStr() + ")") << id + " font added" << std::endl;
				}
			}
			void loadImagesToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Image>(id, f);
					ssvu::lo("ssvs::AssetFolder::loadImagesToManager(" + rootPath.getStr() + ")") << id + " image added" << std::endl;
				}
			}
			void loadTexturesToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Texture>(id, f);
					ssvu::lo("ssvs::AssetFolder::loadTexturesToManager(" + rootPath.getStr() + ")") << id + " texture added" << std::endl;
				}
			}
			void loadSoundBuffersToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::SoundBuffer>(id, f);
					ssvu::lo("ssvs::AssetFolder::loadSoundsToManager(" + rootPath.getStr() + ")") << id + " soundBuffer added" << std::endl;
				}
			}
			void loadMusicsToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Music>(id, f);
					ssvu::lo("ssvs::AssetFolder::loadMusicsToManager(" + rootPath.getStr() + ")") << id + " music added" << std::endl;
				}
			}
			void loadShadersToManager(AssetManager& mAssetManager)
			{
				for(const auto& f : getFilteredFiles({".vert"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Shader>(id, f, sf::Shader::Type::Vertex, Internal::ShaderFromPath{});
					ssvu::lo("ssvs::AssetFolder::loadShadersToManager(" + rootPath.getStr() + ")") << id + " vertex shader added" << std::endl;
				}
				for(const auto& f : getFilteredFiles({".frag"}))
				{
					std::string id{ssvu::getReplaced(f, rootPath, "")};
					mAssetManager.load<sf::Shader>(id, f, sf::Shader::Type::Fragment, Internal::ShaderFromPath{});
					ssvu::lo("ssvs::AssetFolder::loadShadersToManager(" + rootPath.getStr() + ")") << id + " fragment shader added" << std::endl;
				}
			}

		public:
			AssetFolder(const Path& mRootPath) : rootPath{mRootPath}, files{ssvu::FileSystem::getScan<ssvu::FileSystem::Mode::Recurse, ssvu::FileSystem::Type::File>(rootPath)} { }
			void loadToManager(AssetManager& mAssetManager)
			{
				loadImagesToManager(mAssetManager);
				loadTexturesToManager(mAssetManager);
				loadSoundBuffersToManager(mAssetManager);
				loadMusicsToManager(mAssetManager);
				loadFontsToManager(mAssetManager);
				loadShadersToManager(mAssetManager);
			}
	};
}

#endif
