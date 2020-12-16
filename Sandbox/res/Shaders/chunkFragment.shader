#version 330 core


in float NormalLight;

void main()
{
	gl_FragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f) * NormalLight;
}