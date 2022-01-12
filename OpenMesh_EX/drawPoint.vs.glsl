#version 410 core

layout(location = 0) in vec3 vertex;

uniform mat4 um4mv;
uniform mat4 um4p;

void main()
{
	vec4 pos = vec4(vertex, 1.0);
	gl_Position = um4p * um4mv * pos;
}