#version 150

in vec3 col;
out vec4 outColor;

uniform sampler2D textu;

void main()
{
	float offset = .5f;
	vec4 texel = vec4(col.x,col.y,col.z,1);

	/// Texture null check? Three ifs for not using texture coord
	if(col.z == 0 || col.z == 1 || col.z == -1)
		texel = texture (textu, vec2(col.x + offset,col.y + offset));
	else if(col.y == -1 || col.y == 1)
		texel = texture (textu, vec2(col.x + offset,col.z + offset));
	else
		texel = texture (textu, vec2(col.z + offset,col.y + offset));

	outColor = texel;
}
