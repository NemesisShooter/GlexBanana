#include "CubeAsset.h"

CubeAsset::CubeAsset(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z) {
  // model coordinates, origin at centre.
  GLfloat vertex_buffer [] {
    -0.5f + pos_x, -0.5f + pos_y, -0.5f +pos_z
   ,-0.5f + pos_x,  0.5f + pos_y, -0.5f +pos_z
   , 0.5f + pos_x, -0.5f + pos_y, -0.5f +pos_z
   , 0.5f + pos_x,  0.5f + pos_y, -0.5f +pos_z
   , 0.5f + pos_x, -0.5f + pos_y,  0.5f +pos_z
   , 0.5f + pos_x,  0.5f + pos_y,  0.5f +pos_z
   ,-0.5f + pos_x, -0.5f + pos_y,  0.5f +pos_z
   ,-0.5f + pos_x,  0.5f + pos_y,  0.5f +pos_z
  };
  vertex_buffer_length = sizeof(vertex_buffer);

//using buffer to assign colours for shape
  GLfloat color_buffer[] = {
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
    rngfloat(),  rngfloat(),  rngfloat(),
  };

  color_buffer_length = sizeof(color_buffer);

  //Creating a cube with the use of coordinates

  GLuint element_buffer []  {
      0, 1, 2//side[1]
    , 1, 3, 2//side[2]
    , 2, 3, 4//side[3]
    , 3, 5, 4//side[4]
    , 0, 2, 4//side[5]
    , 6, 0, 4//side[6]
    , 6, 7, 0//side[7]
    , 1, 0, 7//side[8]
    , 1, 7, 3//side[9]
    , 7, 5, 3//side[10]
    , 5, 6, 4//side[11]
    , 5, 7, 6//side[12]
  };
  element_buffer_length = sizeof(element_buffer);

  // Transfer buffers to the GPU
  //

  // create buffer
  // immediately bind the buffer and transfer the data
  glGenBuffers(1, &vertex_buffer_token);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
  glBufferData(GL_ARRAY_BUFFER, color_buffer_length, vertex_buffer, GL_STATIC_DRAW);

  // Send over GLfloats for the colours
  glGenBuffers(1, &color_buffer_token);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_token);
  glBufferData(GL_ARRAY_BUFFER, color_buffer_length, color_buffer, GL_STATIC_DRAW);

  // Send over GLfloats for the elements (joining the triangles)
  glGenBuffers(1, &element_buffer_token);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_length, element_buffer, GL_STATIC_DRAW);
}


float CubeAsset::rngfloat(){
  float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  return r;
}

CubeAsset::~CubeAsset() {
}

#ifdef DEBUG
#define checkGLError() checkError(__FILE__, __LINE__)
#else
// define symbol to be nothing
#define checkGLError()
#endif

void checkError(std::string file, int line) {
  GLenum gl_error = glGetError();
  if(GL_NO_ERROR != gl_error) {
    std::cerr << "GL error in " << file << " at line " << line << " error: " << gl_error << std::endl;
    exit(-1);
  }
}

void CubeAsset::Draw(GLuint program_token) {
  if(!glIsProgram(program_token)) {
    std::cerr << "Drawing Cube with invalid program" << std::endl;
    return;
  }
  GLint validation_ok;
  glValidateProgram(program_token);
  glGetProgramiv(program_token, GL_VALIDATE_STATUS, &validation_ok);
  if(!validation_ok) {
    GLint maxLength = 0;
    glGetProgramiv(program_token, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    std::vector<char> errorLog(maxLength);
    glGetProgramInfoLog(program_token, maxLength, &maxLength, &errorLog[0]);

    std::cerr << "Invalid program " << program_token << " with error code " << validation_ok << std::endl;
    for(auto c: errorLog) {
      std::cerr << c;
    }
    exit(-1);
  }

  GLuint position_attrib = glGetAttribLocation(program_token, "position");
  checkGLError();

  glUseProgram(program_token);
  checkGLError();

  // use the previously transferred buffer as the vertex array.  This way
  // we transfer the buffer once -- at construction -- not on every frame.

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
  glVertexAttribPointer(
    0,        /* attribute */
    3,        /* size */
    GL_FLOAT,   /* type */
    GL_FALSE,   /* normalized? */
    0,        /* stride */
    (void*)0    /* array buffer offset */
  );
  glEnableVertexAttribArray(1);
  checkGLError();

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer_token);
  glVertexAttribPointer(
    1,        /* attribute */
    3,        /* size */
    GL_FLOAT,   /* type */
    GL_FALSE,   /* normalized? */
    0,        /* stride */
    (void*)0    /* array buffer offset */
  );
  checkGLError();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
  glDrawElements(
    GL_TRIANGLES,
    element_buffer_length,
    GL_UNSIGNED_INT,
    (GLvoid*) 0
  );
  checkGLError();

  glDisableVertexAttribArray(position_attrib);
}
