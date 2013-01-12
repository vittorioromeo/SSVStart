#include "Assets.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;
using namespace ssvs::Utils;

namespace ssvs
{
	namespace Assets
	{
		AssetManager* assetManager;

		void init()
		{
			assetManager = new AssetManager;
			AssetFolder dataFolders{"Data/"};
			dataFolders.fillManager(*assetManager);
		}
		
		Texture& getTexture(const string& mId) { return assetManager->getTexture(mId); }
		Sound& getSound(const string& mId) { return assetManager->getSound(mId); }
		Music& getMusic(const string& mId) { return assetManager->getMusic(mId); }
	}
}
