#version 330
in vec3 position;
in vec3 colorIn;
out vec3 colorOut;

in vec2 textureIn;
out vec2 textureOut;

in vec3 normalIn;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 positionOut;

void main(void)
{
	//send interpolated color data to fragment shader
	colorOut = colorIn;
	textureOut = textureIn;
	normalOut = normalIn;

	//send interpolated world position data to fragment shader
	positionOut = (model * vec4(position, 1.0)).xyz;
	
	//interpolate each vertex based on MVP transformations
	gl_Position = projection * view * model * vec4(position, 1.0);
}