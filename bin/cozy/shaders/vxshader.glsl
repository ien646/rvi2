#version 330 core
layout (location = 0) in vec2 aPos;

out vec4 vxColor;

void main()
{
    float x = ((aPos.x) * 2) -1;
    float y = ((aPos.y) * 2) -1;
    gl_Position = vec4(x, y, 1.0, 1.0);
}