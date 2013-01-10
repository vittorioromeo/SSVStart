#include "Assets.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;

namespace ssvs 
{
	namespace Assets
	{
		string dataPath{"Data/"};
		string imagesPath{dataPath + "Images/"};

		bool loadImages{true};
		bool loadTextures{true};

		map<string, Image> imagesMap;
		map<string, Texture> texturesMap;

		void init()
		{
			if (loadImages) initImages();
			if (loadTextures) initTextures();
		}

		void initImages()
		{
			// Default 16x16 magenta missing image
			Image missingImage; missingImage.create(16, 16, Color::Magenta);
			imagesMap["missingImage"] = missingImage;

			// Does the images folder exist?
			if (!exists(imagesPath)) { log(imagesPath + " does not exist", "Assets::initImages"); return; }

			// Valid image extensions
			vector<string> extensions{".png", ".jpg", ".bmp", ".jpeg"};

			// Get all folders in the images folder (and add the parent folder)
			vector<string> imagesFolders;
			recursiveFillFolders(imagesFolders, imagesPath);
			imagesFolders.push_back(imagesPath);

			// Get all the images in all folders
			for(auto imageFolder : imagesFolders)
			{
				log(imageFolder + " folder entered", "Assets::initImages");

				for(auto imageFile : listFiles(imageFolder))
				{
					for(auto extension : extensions)
						if(endsWith(toLower(imageFile), extension))
						{
							Image image; image.loadFromFile(imageFile);
							string imageId{imageFile}; replace(imageId, imagesPath, "");
							imagesMap[imageId] = image;

							log(imageId + " image added", "Assets::initImages");
						}
				}
			}
		}

		void initTextures()
		{
			for(string key : getKeys(imagesMap))
			{
				Texture texture; texture.loadFromImage(imagesMap[key]); texturesMap[key] = texture;
				log(key + " texture created", "Assets::initTextures");							
			}
		}

		Texture& getTexture(const string& mId) { return texturesMap[mId]; }
	}
}

