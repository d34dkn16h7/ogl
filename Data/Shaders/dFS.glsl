#version 150

in vec3 col;
out vec4 outColor;

uniform sampler2D textu;

void main()
{
	vec4 texel;
	if(col.z == -1 || col.z == 1)
		texel = texture (textu, vec2(col.x + 1,col.y + 1));
	else if(col.y == -1 || col.y == 1)
		texel = texture (textu, vec2(col.x + 1,col.z + 1));
	else
		texel = texture (textu, vec2(col.z + 1,col.y + 1));
	
	outColor = texel;
}