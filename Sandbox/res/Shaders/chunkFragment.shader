#version 330 core


in vec2 v_TextureCoordinates;
in float NormalLight;
flat in uint v_TextureID;

uniform sampler2D u_Textures[32];

out vec4 FinalColor;

void main()
{
	//@TODO: v_TextureCoordinates * x for repeating factor to be scaled
	gl_FragColor = texture(u_Textures[(v_TextureID)], v_TextureCoordinates) * NormalLight;
}