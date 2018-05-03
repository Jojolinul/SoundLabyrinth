#version 330

struct Light
{
 vec3 position;
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 float attenuation;
};

struct Material
{
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 float shininess;
};

in vec3 colorOut;
in vec2 textureOut;
in vec3 positionOut;
in vec3 normalOut;
vec3 FinalCol = vec3(0);

out vec4 pixelColor;

uniform sampler2D textureImage;
uniform sampler2D textureImage1;

uniform bool TextureFlag;
uniform bool isLit;

uniform Material material;
uniform Light light[6];

uniform float mixValue;
uniform vec3 cameraPosition;

uniform float AttenuationDistance;
uniform float FogDistance;

vec3 fogColor = vec3(0.02f, 0.02f, 0.02f);

vec3 CalculateLights(Light light)
{
		vec3 ambientColor = light.ambient* material.ambient;
		vec3 normal = normalize(normalOut);
		vec3 lightDirection = normalize(light.position - positionOut);
		float lightIntensity = max(dot(lightDirection, normal), 0.0);
		vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;
		vec3 viewDirection = normalize(cameraPosition - positionOut);
		vec3 reflection = reflect(-lightDirection, normal);
		float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
		vec3 specularColor = light.specular * material.specular * pow(specularTerm,1);
		
		float distance = length(cameraPosition - positionOut);
		//float distance = length(positionOut - cameraPosition);

		float attenuation = 1.0 / (0 + AttenuationDistance * distance + 0.0 * pow(distance, 2));
		vec3 Color = ((ambientColor + diffuseColor + specularColor) * attenuation);
		float FogF = (distance - FogDistance) / (FogDistance - 0);

		//Mostly debug returns that helped me see things in this extremely dim labyrinth
		//return ambientColor;
		//return ((ambientColor + diffuseColor + specularColor) * attenuation);
		return mix(fogColor, Color, FogF);
}

void main(void)
{
	if(isLit)
	{
		for(int x = 0; x < 6; x++)
		{
			FinalCol += CalculateLights(light[x]);
		}

		if(TextureFlag == false)
		{
			pixelColor = vec4(colorOut, 1.0);
		}

		else if(TextureFlag == true)
		{
			pixelColor = vec4(FinalCol, 1.0) * texture(textureImage, textureOut.st);
		}
	}
	else
	{
			pixelColor = vec4(colorOut, 1.0) * texture(textureImage, textureOut.st);
	}
}