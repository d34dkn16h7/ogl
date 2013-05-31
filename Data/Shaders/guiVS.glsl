#version 150

uniform vec2 scale;
uniform vec4 color;

in vec4 vert;

out vec4 col;

void main() 
{
	vert.x *= scale.x;
	vert.y *= scale.y;
	vert.z *= scale.x;
	vert.w *= scale.y;
    gl_Position = vert;

    col = color;
}