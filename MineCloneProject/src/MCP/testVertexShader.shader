#version 330 core
layout (location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec2 a_UVs;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 outColor;

void main()
{
	gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);

	outColor = vec4(a_Normals.x, a_Normals.y, a_Normals.z, 1.0f);
}

