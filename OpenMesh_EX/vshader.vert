#version 460
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertex_texcoord;

out vec3 vs_pos;
out vec3 vs_color;
out vec2 vs_texcoord;

void main() {
    
    //vs_pos=vertex_pos;//一般的
    vs_color=vertex_color;
    //vs_texcoord=vertex_texcoord;
    gl_Position=vec4(vertex_pos,1.f);//一般的

    
    
}