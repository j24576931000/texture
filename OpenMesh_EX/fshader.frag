#version 460 
out vec4 fragcolor;
in vec3 vs_pos;
in vec3 vs_color;
in vec2 vs_texcoord;
          
void main() {
      
    fragcolor = vec4(vs_color,1.f) ;//д@пык║
    
}