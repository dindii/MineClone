#version 330 core


in vec2 v_TextureCoordinates;
in float NormalLight;
flat in uint v_TextureID;

uniform sampler2D u_Textures[32];

out vec4 FinalColor;

//FOG
const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00005;

flat in uint v_ATB1;
flat in uint v_ATB2;


void main()
{
	//#TODO: move this to vertex shader
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fog = clamp(exp(-fogdensity * z * (z*1.2f)), 0.2, 1);

	vec2 FinalTextureCoordinates = vec2(v_TextureCoordinates.x * v_ATB1, v_TextureCoordinates.y * v_ATB2);
	

		//@TODO: v_TextureCoordinates * x for repeating factor to be scaled
		gl_FragColor = mix(fogcolor, (texture(u_Textures[(v_TextureID)], FinalTextureCoordinates) * NormalLight), fog);
		//gl_FragColor = mix(fogcolor, (texture(u_Textures[(v_TextureID)], v_TextureCoordinates) * NormalLight), fog);
}