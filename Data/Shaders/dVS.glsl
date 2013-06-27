#version 150

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform vec4 color;

in vec4 vert;
out vec3 col;

void main() 
{
    gl_Position = cameraMatrix * modelMatrix * vert;

    col = vec3(vert.x,vert.y,vert.z);
}
