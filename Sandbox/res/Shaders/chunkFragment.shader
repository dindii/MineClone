#version 330 core


in vec2 v_TextureCoordinates;
in float NormalLight;
in uint v_TextureID;

uniform sampler2D u_Textures[32];

out vec4 FinalColor;

void main()
{
	//@TODO: v_TextureCoordinates * x for repeating factor to be scaled
	FinalColor = texture(u_Textures[0], v_TextureCoordinates) * NormalLight;
}