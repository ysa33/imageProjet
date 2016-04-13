varying vec3 v, N;
void main()
{
vec3 normal = normalize(N);	
   vec3 L = normalize(vec3(gl_LightSource[0].position.xyz-v));
   vec3 E = normalize(v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(reflect(L,N));  

  
 
  // calcul du cosinus de l'angle entre la normale et le rayon lumineux :	 
  // correspond au produit scalaire puisque les vecteurs sont normalises	 
  float cosinusD = dot(N, L);	 
  if (cosinusD > 0.0)
   gl_FragColor = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * cosinusD; //couleur de la lumiere diffuse * coefficient de diffusion * cosinus 

  // calcul du cosinus de l'angle entre le vecteur relechi et le rayon de la camera
   float cosinusS = max(dot(R,E),0.0); 

  
 gl_FragColor += gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(cosinusS,gl_FrontMaterial.shininess) ; //couleur de la lumiere speculaire * coefficient speculaire * cosinus
}