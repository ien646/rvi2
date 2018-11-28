#version 330 core

in vec4 vxColor;
out vec4 color;

uniform float delta_time;

void main()
{
    vec4 fcol = vec4(
        sin(vxColor.x + (delta_time * 1)),
        sin(vxColor.y + (delta_time * 1.223f)),
        sin(vxColor.z + (delta_time * 1.317f)),
        sin(vxColor.w + (delta_time * 1.132f))
    );
    color = fcol;
}