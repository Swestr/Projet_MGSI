#version 450

uniform mat4 MVP;
uniform mat4 MODEL;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 indexUVTexture;

out vec2 fragTexture;

void main(){
  gl_Position = MVP * vec4(position, 1.0);
  fragTexture = indexUVTexture;
}
