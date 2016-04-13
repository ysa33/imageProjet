
uniform float translate;

void main (void)
{   
	vec4 p;
	p.xzw = gl_Vertex.xzw;	
	p.y = gl_Vertex.y + translate;

	gl_Position = gl_ModelViewProjectionMatrix * p;
	gl_FrontColor = gl_Color; 
	
}
