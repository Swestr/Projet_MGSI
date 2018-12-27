#version 450

uniform sampler2D myTextureSampler;

in vec2 fragTexture;
out vec4 finalColor;


void main() {
  vec3 tex = texture2D(myTextureSampler, fragTexture.st).xyz;
  finalColor = vec4( tex ,0.5);
}
