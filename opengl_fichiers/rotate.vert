
uniform float rotate;
attribute vec4 position;
attribute vec4 color;


uniform vec2 offset;
uniform float zNear;
uniform float zFar;
uniform float frustumScale;

void main (void)
{    
     mat3 rotation = mat3(
        vec3( cos(rotate),  sin(rotate),  0.0),
        vec3(-sin(rotate),  cos(rotate),  0.0),
        vec3(        0.0,         0.0,  1.0)
    );
     mat3 rotation2 = mat3(
        vec3(        1.0,         0.0,  0.0),
        vec3( 0.0,cos(rotate),  sin(rotate)),
        vec3(0.0,-sin(rotate),  cos(rotate))
    );

   vec4 p =  vec4(rotation * rotation2 *position.xyz, 1.0);

    vec4 cameraPos = p + vec4(offset.x, offset.y, 0.0, 0.0);

    vec4 clipPos;
    
    clipPos.xy = cameraPos.xy * frustumScale;
    
    clipPos.z = cameraPos.z * (zNear + zFar) / (zNear - zFar);
    clipPos.z += 2 * zNear * zFar / (zNear - zFar);
    
    clipPos.w = -cameraPos.z;	
  gl_Position = clipPos;	    

    gl_FrontColor = color;
}
