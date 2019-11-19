#version 330 core

out vec4 f_Color;
in vec4 outColor;

void main()
{
	f_Color = outColor;
}

