#version 460 core

out vec4 fragColor;

in VertexData
{
	vec3 vNormal;
	//vec2 texCoord;
vec3 barycentric;
} vertexIn;
uniform sampler2D tex0;
float edgeFactor()
{
	vec3 d = fwidth(vertexIn.barycentric);
	vec3 a3 = smoothstep(vec3(0.0), d * 1.5, vertexIn.barycentric);
	return min(min(a3.x, a3.y), a3.z);
}

void main(void)
{
	float ef = edgeFactor();
	vec4 faceColor = vec4(0.0, 0.0, 1.0, 1.0);
	//vec2 vs_tex=vec2 (vertexIn.vNormal.x,vertexIn.vNormal.y);
	//vec4 faceColor =texture(tex0,vs_tex) ;
	vec4 edgeColor = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 color = mix(edgeColor, faceColor, ef);

	/*if (color.a < ef)
	{
	discard;
	}
	else
	{
	fragColor = color;
	}*/

	fragColor = color;
}