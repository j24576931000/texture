#version 410 core

out uint fragColor;
//out vec4 fragColor;
//in vec3 vs_pos;
//in vec3 vs_color;
void main(void) 
{
	//fragColor = vec4(vs_color,1.f) ;
	fragColor=gl_PrimitiveID +1;
}