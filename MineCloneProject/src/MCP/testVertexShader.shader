#version 330 core
layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 outColor;

void main()
{
	gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);

	outColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}

