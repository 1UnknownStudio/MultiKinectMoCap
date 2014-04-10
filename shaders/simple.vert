uniform mat4 sFrustum;
uniform mat4 sLookAt;

void main()
{
	gl_FrontColor = gl_Color;
	gl_Position = sFrustum * sLookAt * gl_Vertex;
}