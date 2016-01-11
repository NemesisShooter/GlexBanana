#ifndef PIRAMIDASSET_H
#define PIRAMIDASSET_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class PiramidAsset : public GameAsset {
 public:
  PiramidAsset(GLfloat, GLfloat, GLfloat);
  ~PiramidAsset();
  virtual void Draw(GLuint);
  float randfloat();

 private:
  GLuint vertex_buffer_length, element_buffer_length, color_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token, color_buffer_token;
};

#endif // PIRAMIDASSET_H
