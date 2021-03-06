#ifndef CUBEASSET_H
#define CUBEASSET_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class CubeAsset : public GameAsset {
 public:
  CubeAsset(GLfloat, GLfloat, GLfloat);
  ~CubeAsset();
  virtual void Draw(GLuint);
  float rngfloat();

 private:
  GLuint vertex_buffer_length, element_buffer_length, color_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token, color_buffer_token;
};

#endif // CUBEASSET_H
