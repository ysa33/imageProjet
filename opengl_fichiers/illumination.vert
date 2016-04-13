

varying vec3 v, N;



void main (void)
{   
    gl_Position = gl_ModelViewProjectionMatrix *  gl_Vertex;
    gl_FrontColor = gl_Color; 	       
    v = vec3(gl_ModelViewMatrix * gl_Vertex); // transformation dans le repère de la caméra 
    N = normalize(gl_NormalMatrix * gl_Normal);	
}

