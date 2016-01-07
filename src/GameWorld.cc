#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) : asset_manager(std::make_shared<GameAssetManager>(mode)) {
  asset_manager->AddAsset(std::make_shared<CubeAsset>(0,0,0));
	//making new cubes
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
