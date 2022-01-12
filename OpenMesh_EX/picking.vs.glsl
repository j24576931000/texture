#version 410 core

layout(location = 0) in vec3 vertex;
//layout(location = 1) in vec3 color;
uniform mat4 um4mv;
uniform mat4 um4p;
//out vec3 vs_pos;
//out vec3 vs_color;
void main()
{
    //vs_pos=vertex;//д@пык║
    
    //vs_color=color;
	gl_Position = um4p * um4mv * vec4(vertex, 1.0);
}
