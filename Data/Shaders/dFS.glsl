#version 150

in vec3 col;
out vec4 outColor;

layout(binding=0) uniform sampler2D textu;

void main()
{
	float offset = .5f;
	vec4 texel = vec4(1,1,1,1);
	//if(textu != null)
	{
		if(col.z == -1 || col.z == 1)
			texel = texture (textu, vec2(col.x + offset,col.y + offset));
		else if(col.y == -1 || col.y == 1)
			texel = texture (textu, vec2(col.x + offset,col.z + offset));
		else
			texel = texture (textu, vec2(col.z + offset,col.y + offset));
	}
	
	outColor = texel;
}