#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vxColor;

uniform float delta_time;

void main()
{
	// Position
    float x = ((aPos.x) * 2) -1;
    float y = ((aPos.y) * 2) -1;
	gl_Position = vec4(x, y, 1.0, 1.0);

	// Vertex color
	uint dt = floatBitsToUint(aPos.z);
	uint ri = uint((dt >> 24) & uint(0x000000FF));
	uint gi = uint((dt >> 16) & uint(0x000000FF));
	uint bi = uint((dt >> 8) & uint(0x000000FF));
	uint ai = uint((dt) & uint(0x000000FF));

	float r = float(ri) / 255;
	float g = float(gi) / 255;
	float b = float(bi) / 255;
	float a = float(ai) / 255;

	vxColor = vec4(r, g, b, a);
}