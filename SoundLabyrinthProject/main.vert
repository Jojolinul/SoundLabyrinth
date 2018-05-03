#version 330
in vec3 position;
in vec3 colorIn;
out vec3 colorOut;

in vec2 textureIn;
out vec2 textureOut;

in vec3 normalIn;
out vec3 normalOut;

uniform float frequency;
uniform float time;
uniform bool isShaking;


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

	if(isShaking)
	{
		// choose a displacement amount
		float displacement = 0.5 * (sin(time * frequency * 10) + 1) * 0.05;

		// displace it in the direction of the normal
		vec3 displacementDirection = vec3(normalIn.x, normalIn.y, normalIn.z) ;

		// move the vertex
		vec3 newPosition = position + displacement * displacementDirection ;

		positionOut = (model * vec4(newPosition, 1.0)).xyz;
		gl_Position = projection * view * model * vec4(newPosition, 1.0);

	}
	else
	{
		//send interpolated world position data to fragment shader
		positionOut = (model * vec4(position, 1.0)).xyz;

		//interpolate each vertex based on MVP transformations
		gl_Position = projection * view * model * vec4(position, 1.0);
	}
}