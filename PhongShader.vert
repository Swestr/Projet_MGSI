#version 450

uniform mat4 MVP;
uniform mat4 MODEL;

layout(location = 0) in vec3 position; // le location permet de dire de quel flux/canal on récupère les données (doit être en accord avec le location du code opengl)
layout(location = 1) in vec2 indexUVTexture;
layout(location = 2) in vec3 normales;
layout(location = 3) in vec3 tangentes;
layout(location = 4) in vec3 bitangentes;
layout(location = 5) in vec3 sommetPlan;

out vec3 fragposition;
out vec3 fragNormale;
out vec2 fragTexture;

void main(){
gl_Position = MVP * vec4(position, 1.0);
fragTexture = indexUVTexture;
fragNormale = (transpose(inverse(MODEL)) * vec4(normales, 0.0)).xyz;
fragposition = (MODEL * vec4(sommetPlan, 1.0)).xyz;



}
