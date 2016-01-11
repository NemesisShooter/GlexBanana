#version 130

in vec3 position;
in vec3 color;

out vec3 frag_color;

uniform mat4 camera_projection;
uniform mat4 camera_view;
uniform mat4 camera_model;

void main() {
      gl_Position = (camera_projection * 
                      camera_view * 
                        camera_model) * 
                          vec4(position, 1);
      frag_color = color;
    }