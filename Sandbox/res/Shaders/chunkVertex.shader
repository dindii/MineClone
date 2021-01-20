#version 330 core

layout(location = 0) in uint a_Coord;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out float NormalLight;
out vec2 v_TextureCoordinates;
flat out uint v_TextureID;


float Z = float((a_Coord >> 16u) & 0xFu);
float X = float((a_Coord >> 20u) & 0xFu);
float Y = float((a_Coord >> 24u) & 0xFFu);



uint TextureCoordinatesIndex = (a_Coord & 0xFFu);

    vec2 texCoords[4] = vec2[4](
	vec2(0.0f, 0.0f),
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f)
	);


void main()
{
	v_TextureCoordinates = texCoords[TextureCoordinatesIndex];
	v_TextureID = ((a_Coord >> 8u) & 0x1Fu);
	NormalLight = clamp(float((a_Coord >> 13u) & 0x7u) / 5.0f, 0.0f, 1.0f);
	gl_Position = u_ViewProjection * u_Transform * vec4(X, Y, Z, 1.0f); //MVP
}
