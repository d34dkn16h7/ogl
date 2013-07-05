#version 150

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

in vec4 vertex;
out vec3 col;

void main()
{
    gl_Position = cameraMatrix * modelMatrix * vertex;
    col = vec3(vertex.x,vertex.y,vertex.z);
}
