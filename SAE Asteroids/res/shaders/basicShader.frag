#version 400

out vec3 color_frag;

in vec2 texCoord;

uniform sampler2D diffuse;

void main()
{
	color_frag = texture(diffuse, texCoord).rgb;
}