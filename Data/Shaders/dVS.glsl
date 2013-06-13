#version 150

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform vec4 color;

in vec4 vert;
out vec4 col;

void main() 
{
    gl_Position = cameraMatrix * modelMatrix * vert;

    if(color.x != -1)
    	col = color;
    else
	{
		vec4 v = vec4(.7,.7,.7,1);
		col = (vert + v) / 2;
	}
}
