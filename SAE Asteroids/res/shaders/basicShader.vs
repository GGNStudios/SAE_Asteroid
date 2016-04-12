#version 400

in vec2 TexCoord;
in vec3 coord2d;

out vec2 texCoord;

uniform mat4 MVP;
uniform mat4 transform;
uniform vec3 position;

void main()
{
	gl_Position = MVP * (transform * vec4(coord2d,1)) + vec4(position,1);
	texCoord = TexCoord;
}