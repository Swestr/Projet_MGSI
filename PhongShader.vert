#version 450

uniform mat4 MVP;
uniform mat4 MODEL;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 indexUVTexture;
layout(location = 2) in vec3 normales;

out vec3 fragposition;
out vec3 fragNormale;
out vec2 fragTexture;

void main(){
gl_Position = MVP * vec4(position, 1.0);
fragTexture = indexUVTexture;
fragNormale = (transpose(inverse(MODEL)) * vec4(normales, 0.0)).xyz;
fragposition = (MODEL * vec4(position, 1.0)).xyz;



}
