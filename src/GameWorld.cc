#include "GameWorld.h"

GameWorld::GameWorld (ApplicationMode mode) : asset_manager(std::make_shared<GameAssetManager>(mode)) {
  asset_manager->AddAsset(std::make_shared<CubeAsset>(0,0,0));
  asset_manager->AddAsset(std::make_shared<PiramidAsset>(0,0,0));
	/*
		making new cubes, if there is 0 cubes then there will be 1 created
		if there is more then 1 cube but less then 3 additional cubes
		will be created and added with new coordinates
	*/

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

	//for(int p=0; p<3; p++)
	//{
	//	if(p == 0)
	//	{
			asset_manager->AddAsset(std::make_shared<PiramidAsset>(1.0, 0.0, 0.0));
	//	}
	//	else
	//	{
	//		asset_manager->AddAsset(std::make_shared<PiramidAsset>(-1.5*p, 1.5*p, 0.0));
	//	}
	//}

}

//camera formulas
void GameWorld::Draw() 
{
	glm::vec3 direction(
		cos(camera_y) * sin(camera_x),
		sin(camera_y),
		cos(camera_y) * cos(camera_x)
		);

//view of the camera Pi/2
	x_direction = glm::vec3(
		sin(camera_x - 3.14f/2.0f),
		0,
		cos(camera_x - 3.14f/2.0f)
		);

	glm::vec3 vup = glm::cross(x_direction, direction);
	glm::mat4 camera_projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 camera_view = glm::lookAt(
		position,
		position + direction,
		vup
	);
  asset_manager->Draw(camera_projection, camera_view);
}
