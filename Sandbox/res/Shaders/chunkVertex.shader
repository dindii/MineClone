#version 330 core

layout(location = 0) in uint a_Coord;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out float NormalLight;
out vec2 v_TextureCoordinates;
flat out uint v_TextureID;


float Z = float((a_Coord >> 16u) & 0xFu);
float X = float((a_Coord >> 20u) & 0xFu);
float Y = float((a_Coord >> 28u) & 0xFu);

flat out uint v_ATB1;
flat out uint v_ATB2;

uint TextureCoordinatesIndex = ((a_Coord >> 6) & 0x03u);

    vec2 texCoords[4] = vec2[4](
	vec2(0.0f, 0.0f),
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f)
	);




void main()
{
	v_ATB1 = uint((a_Coord >> 2)  & 0xFu);
	v_ATB2 = uint((a_Coord >> 24) & 0xFu);

	v_TextureCoordinates = texCoords[TextureCoordinatesIndex];
	v_TextureID = ((a_Coord >> 8u) & 0x1Fu);
	NormalLight = clamp(float((a_Coord >> 13u) & 0x7u) / 5.0f, 0.0f, 1.0f);
	gl_Position = u_ViewProjection * u_Transform * vec4(X, Y, Z, 1.0f); //MVP
}
