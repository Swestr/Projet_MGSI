#version 450

uniform vec3 cameraPosition;
uniform vec3 LightPosition;
uniform sampler2D myTextureSampler;
uniform sampler2D myNormalMap;
uniform float materialShininess;
uniform vec3 materialSpecularColor;

in vec2 fragTexture;
in vec3 fragNormale;
in vec3 fragposition;
out vec4 finalColor;

uniform struct Light
{
  vec3 intensities;
  vec3 position;
  float ambientCoefficient;
  float diffuseCoefficient;
  float attenuation;
}light;


void main() {

vec3 normal = vec3(0,0,0);
//normal = normalize(fragNormale);

// lumière ambiante
vec3 ambient = light.ambientCoefficient * light.intensities;

//texture
vec3 tex = texture2D(myTextureSampler, fragTexture.st).xyz;

vec3 speculaire = vec3(0,0,0);
vec3 diffuse = vec3(0,0,0);
//lumiere diffuse
vec3 directionPosLumiere = normalize(light.position - fragposition);
float angleDiffuse = dot(normal, directionPosLumiere);
//facteur d'attenuation
float distance = sqrt(pow(directionPosLumiere.x,2) + pow(directionPosLumiere.y,2) + pow(directionPosLumiere.z,2));
float facteurAttenuation = 1 / (1.0 + light.attenuation * pow(distance,2));
//speculaire
vec3 oeil = normalize(cameraPosition - fragposition);
vec3 reflection = normalize(reflect(-directionPosLumiere , normal));
float angleSpeculaire = dot(oeil, reflection);
angleSpeculaire = pow(angleSpeculaire, materialShininess);

//normal map

if (angleDiffuse > 0)
{
    diffuse = light.intensities * angleDiffuse * light.diffuseCoefficient;

    if (angleSpeculaire > 0)
    {
    speculaire = angleSpeculaire * light.intensities * materialSpecularColor;
    }
}

//lumiere finale
    finalColor = vec4( tex * (ambient + (facteurAttenuation *(diffuse + speculaire)) ),0.0);
}
