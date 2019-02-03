#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;

out vec4 vxColor;
uniform float delta_time;

void main()
{
	// Position
    float x = ((aPos.x) * 2) -1;
    float y = ((aPos.y) * 2) -1;
	gl_Position = vec4(x, y, 1.0, 1.0);
	vxColor = aCol;
}