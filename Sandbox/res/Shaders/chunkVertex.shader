#version 330 core

layout(location = 0) in vec4 a_Coord;

out vec4 v_textCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_ChunkNumber;


void main()
{
	v_textCoord = a_Coord;

	gl_Position = u_ViewProjection * u_Transform * vec4(a_Coord.x, a_Coord.y, a_Coord.z, 1.0); //MVP
}