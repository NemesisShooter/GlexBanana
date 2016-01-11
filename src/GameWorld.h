#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>

#include <GL/gl.h>

#include "common.h"
#include "GameAssetManager.h"
#include "CubeAsset.h"

/**
 * GameWorld allows us to separate the management of the game world from the
 * nuts and bolts of game loop initialisation.  The GameWorld currently has
 * a very simplified scene graph consisiting of a single GameAssetManager.
 */
class GameWorld {
 public:
  /**
   * We thread the ApplicationMode through the GameWorld ss we want to read it
   * in from the user.  Threading the state through the various function calls
   * is preferable (in this case) to having some kind of global state.
   */
  GameWorld(ApplicationMode);

  /**
   * Calling Draw() will draw the entire world.
   */
  void Draw();
 private:
  std::shared_ptr<GameAssetManager> asset_manager;


    int block_dist = 3;

    GLfloat camera_speed = 0.1;
    GLfloat camera_x = 0.0;
    GLfloat camera_y = 0.0;

    double point = 0.39375;

    std::string f_pos = "N";

    glm::vec3 offset_pos;
    glm::vec3 position = glm::vec3(0, 0, -3);
    glm::vec3 x_direction;
    
    glm::mat4 camera_projection;
    glm::mat4 camera_view;
};
#endif // GAMEWORLD_H
