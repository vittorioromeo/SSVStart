#include "AssetManager.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;
using namespace ssvs::Utils;

namespace ssvs
{
	namespace Assets
	{
		AssetManager::AssetManager(const string& mRootPath) : rootPath{mRootPath}, files{getRecursiveFiles(rootPath)}
		{			
			initImages();
			initTextures();
			initSounds();
			initMusics();
		}
		AssetManager::~AssetManager()
		{
			uninitImages();
			uninitTextures();
			uninitSounds();
			uninitMusics();
		}

		void AssetManager::initImages()
		{
			// Default 16x16 magenta missing image
			Image* missingImage{new Image}; missingImage->create(16, 16, Color::Magenta); images["missingImage"] = missingImage;

			vector<string> extensions{".png", ".jpg", ".bmp", ".jpeg"};
			
			for(auto file : files)
				for(auto extension : extensions)
					if(hasExtension(file, extension))
					{
						string id{replace(file, rootPath, "")};
						Image* image{new Image}; image->loadFromFile(file);	images[id] = image;
						log(id + " image added", "initImages(" + rootPath + ")");
					}

		}
		void AssetManager::initTextures()
		{
			for(auto key : getKeys(images))
			{
				Texture* texture{new Texture}; texture->loadFromImage(*images[key]); textures[key] = texture;
				log(key + " texture added", "initTextures(" + rootPath + ")");
			}
		}
		void AssetManager::initSounds()
		{
			vector<string> extensions{".wav", ".ogg"};
			
			for(auto file : files)
				for(auto extension : extensions)
					if(hasExtension(file, extension)) 
					{
						string id{replace(file, rootPath, "")};
						SoundBuffer* soundBuffer{new SoundBuffer}; soundBuffer->loadFromFile(file); soundBuffers[id] = soundBuffer;
						log(id + " soundBuffer added", "initSounds(" + rootPath + ")");
						Sound* sound{new Sound{*soundBuffer}}; sounds[id] = sound;
						log(id + " sound added", "initSounds(" + rootPath + ")");
					}
		}
		void AssetManager::initMusics()
		{
			vector<string> extensions{".wav", ".ogg"};

			for(auto file : files)
				for(auto extension : extensions)
					if(hasExtension(file, extension))
					{
						string id{replace(file, rootPath, "")};
						Music* music{new Music}; music->openFromFile(file); musics[id] = music;
						log(id + " music added", "initMusics(" + rootPath + ")");
					}
		}

		void AssetManager::uninitImages() { for(auto pair : images) delete pair.second; }
		void AssetManager::uninitTextures() { for(auto pair : textures) delete pair.second; }
		void AssetManager::uninitSounds() { for(auto pair : soundBuffers) delete pair.second; for(auto pair : sounds) delete pair.second; }
		void AssetManager::uninitMusics() { for(auto pair : musics) delete pair.second; }

		Texture& AssetManager::getTexture(const string& mId) { return *textures[mId]; }
		Sound& AssetManager::getSound(const string& mId) { return *sounds[mId]; }
		Music& AssetManager::getMusic(const string& mId) { return *musics[mId]; }
	}
}

