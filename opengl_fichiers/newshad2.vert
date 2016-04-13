
uniform float translate;
uniform int rotangle;
uniform int ordre;

attribute vec3 v_color;
varying vec3 f_color;

#define M_PI 3.14159265358979323846

void main (void)
{   

	float rotate = float(rotangle)*M_PI/180.0;

     	mat3 rot_x = mat3(
       	     vec3(1.0, 0.0, 0.0),
       	     vec3(0.0, cos(rotate), sin(rotate)),
             vec3(0.0, -sin(rotate), cos(rotate))
    	);
	mat3 rot_y = mat3(
	     vec3(cos(rotate), 0.0, -sin(rotate)),
	     vec3(0.0, 1.0, 0.0),
	     vec3(sin(rotate), 0.0, cos(rotate))
	);
	mat3 rot_z = mat3(
             vec3(cos(rotate), sin(rotate), 0.0),
             vec3(-sin(rotate), cos(rotate), 0.0),
             vec3(0.0, 0.0, 1.0)
	);
	
	vec3 p = gl_Vertex.xyz;
	if (ordre==1) {
	   p =  rot_x * rot_y * rot_z* p; // rotation
	   p = p + vec3(0,translate,0); // translation
	}
	else {
	   p = p + vec3(0,translate,0); // translation	     
	   p = rot_x * rot_z * p; // rotation
	}   
	vec4 q = vec4(p,gl_Vertex.w);

	gl_Position = gl_ModelViewProjectionMatrix * q;

	f_color = v_color;

}
