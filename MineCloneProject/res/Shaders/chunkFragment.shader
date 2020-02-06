#version 330 core

in vec4 v_textCoord;

void main()
{
	gl_FragColor = vec4(v_textCoord.x, v_textCoord.y, v_textCoord.z, 1.0);
	//gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}