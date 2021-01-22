#version 330 core


in vec2 v_TextureCoordinates;
in float NormalLight;
flat in uint v_TextureID;

uniform sampler2D u_Textures[32];

out vec4 FinalColor;

//FOG
const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

void main()
{
	//#TODO: move this to vertex shader
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fog = clamp(exp(-fogdensity * z * z), 0.2, 1);

		//@TODO: v_TextureCoordinates * x for repeating factor to be scaled
		gl_FragColor = mix(fogcolor, (texture(u_Textures[(v_TextureID)], v_TextureCoordinates) * NormalLight), fog);
}