#version 130

uniform int levelSize;
uniform float objectID;
uniform vec2 nearFar;

void mainDeform();

out vec2 uv;

void main()
{
	uv = (gl_Vertex).xy / levelSize + vec2(0.5, 0.5);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex ;

	// todo bended
	// theNormal = normalize(gl_NormalMatrix * gl_Normal);
	// linearDepth = (-(gl_ModelViewMatrix * gl_Vertex).z-nearFar.x)/(nearFar.y-nearFar.x);
	// gl_TexCoord[1] = vec4(objectID);

	mainDeform();
	return;
}