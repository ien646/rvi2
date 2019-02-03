#version 330 core

in vec4 vxColor;
out vec4 color;

uniform float delta_time;

void main()
{
    vec4 fcol = vec4(
		vxColor.a,
		vxColor.b,
		vxColor.g,
		vxColor.r
	);
    color = fcol;
}