#version 330 core

in vec4 v_textCoord;

void main()
{
	gl_FragColor = vec4(v_textCoord.w / 128.0, v_textCoord.w / 256.0, v_textCoord.w / 512.0, 1.0);
}