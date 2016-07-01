#version 430

in vec4 vPosition;
in vec4 color;
uniform mat4 ortho;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void 
main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
}