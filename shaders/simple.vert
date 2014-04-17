uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_FrontColor = gl_Color;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Vertex;
}
