#version 330 core

layout(location = 0) in uint a_Coord;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out float NormalLight;

float Z = float((a_Coord >> 16u) & 0xFu);
float X = float((a_Coord >> 20u) & 0xFu);
float Y = float((a_Coord >> 24u) & 0xFFu);


void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(X, Y, Z, 1.0f); //MVP
	NormalLight = clamp(float((a_Coord >> 13u) & 0x7u) / 5.0f, 0.0f, 1.0f);
}
