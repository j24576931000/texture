#version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VertexData
{
	vec3 vNormal;
} vertexIn[];

out VertexData
{
	vec3 vNormal;
	vec3 barycentric;
} vertexOut;

void main()
{
	vertexOut.vNormal = vertexIn[0].vNormal;
	vertexOut.barycentric = vec3(1, 0, 0);
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	vertexOut.vNormal = vertexIn[1].vNormal;
	vertexOut.barycentric = vec3(0, 1, 0);
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	vertexOut.vNormal = vertexIn[2].vNormal;
	vertexOut.barycentric = vec3(0, 0, 1);
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}