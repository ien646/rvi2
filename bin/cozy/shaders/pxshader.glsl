#version 330 core

in vec4 vxColor;
out vec4 color;

uniform float delta_time;

void main()
{
    vec4 fcol = vec4(
		vxColor.x,
		vxColor.y,
		vxColor.z,
		vxColor.w
	);
    color = fcol;
}