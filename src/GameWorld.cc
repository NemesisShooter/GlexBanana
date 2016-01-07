#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) : asset_manager(std::make_shared<GameAssetManager>(mode)) {
  asset_manager->AddAsset(std::make_shared<CubeAsset>(0,0,0));
	/*making new cubes, if there is 0 cubes then there will be 1 created
		if there is more then 1 cube but less then 3 additional cubes
	*/will be created and abbd with new coordinates
	for(int i=0; i<3; i++)
	{
		if(i == 0)
		{
			asset_manager->AddAsset(std::make_shared<CubeAsset>(0.0, 0.0, 0.0));
		}
		else
		{
			asset_manager->AddAsset(std::make_shared<CubeAsset>(1.5*i, 1.5*i, 0.0));
		}
	}
}


void GameWorld::Draw() {
  asset_manager->Draw();
}
