#version 460 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
uniform mat4 um4mv;
uniform mat4 um4p;
//uniform mat4 um4u;
out VertexData
{
	vec3 normal;
	//vec2 texCoord;
} vertexOut;

void main()
{
    //vec4 newTexCoord = um4u * vec4(texCoord, 0.0, 1.0);
	vertexOut.normal = normal;
	//vertexOut.texCoord = newTexCoord.xy;
	gl_Position = um4p * um4mv * vec4(vertex, 1.0);
}
