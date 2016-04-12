#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* fichiers d'entetes OpenGL, GLU, GLUT et GLEW */
#include <GL/glew.h> //OpenGL extension wrangler library
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h> 


GLuint shaderProg;
GLuint positionBufferObject;
GLuint rectangle;
float rot;
float trans = 0.1f;
int sens = 0;


char* readFile(const char* fname) {
  FILE *f;
  char *content = NULL;
  int count = 0;
  if (fname != NULL) {
    f = fopen(fname,"rt");

    if (f != NULL) {
      fseek(f, 0, SEEK_END);  
      count = ftell(f);
      rewind(f);

      if (count > 0) {
	content = (char *)malloc(sizeof(char) * (count+1));
	count = fread(content,sizeof(char),count,f);
	content[count] = '\0';
      }
      fclose(f);
    }
  }
  return content;
}

void printShaderInfoLog(GLuint obj)
{
  GLint infologLength = 0;
  GLint charsWritten  = 0;
  char *infoLog;

  glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

  if (infologLength > 0)
    {
      infoLog = (char*)malloc(infologLength);
      glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
      printf("%s\n",infoLog);
      free(infoLog);
    }
}

GLuint setShaders() {

  /* CREATE THE SHADERS */
  //1 - create objects which will act as shader containers.
  // (vertex and fragment shader)
  GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  GLchar* vertexSource = (GLchar*)readFile("translate.vert");
  GLchar* fragmentSource = (GLchar*)readFile("translate.frag");
 
	
  // 2 - associate shader and source
  glShaderSource( vshader, 1, (const GLchar**)(&vertexSource), NULL );
  glShaderSource( fshader, 1, (const GLchar**)(&fragmentSource), NULL );

  // 3 - Compile vertex and fragment shader
  glCompileShader(vshader);
  glCompileShader(fshader);

  printShaderInfoLog(vshader);
  printShaderInfoLog(fshader);

  /* CREATE THE PROGRAM */
  //1 - create the object which will act as a program container.
  GLuint shaderProgram = glCreateProgram();

  /* /\* // 2 - attach shader to the program *\/ */
  glAttachShader(shaderProgram,vshader);
  glAttachShader(shaderProgram,fshader);

  /* // 3 - link the program. For this step, the shaders must be compiled. */
  glLinkProgram(shaderProgram); 

  /* // 4 - Load and use the program */
  glUseProgram(shaderProgram); 

  /* //FREE  */
  free(vertexSource);
  free(fragmentSource);
  return shaderProgram;
}


// frappes de touches normales
void
keyboardFunc (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 'Q':
        case 27:                       // Esc
            exit (EXIT_SUCCESS);
            break;
            
    }
    glutPostRedisplay ();
}

const float rectVertex[] = {
    /*Cube 1 */
    /*Face 1*/
    -4.f, -1.f, 0.0f, 1.0f, //F
    -4.f, 1.f, 0.0f, 1.0f,  //A
    -2.f, 1.f, 0.0f, 1.0f,  // D
    -2.f, -1.f, 0.0f, 1.0f, // G

    /*Face 2*/
    -4.f, -1.f, 2.0f, 1.0f, //E
    -4.f, 1.f, 2.0f, 1.0f, //B
    -2.f, 1.f, 2.0f, 1.0f, //C
    -2.f, -1.f, 2.0f, 1.0f, //H

    /*Face 3*/
    -4.f, 1.f, 0.0f, 1.0f,  //A
    -4.f, 1.f, 2.0f, 1.0f, //B
    -2.f, 1.f, 2.0f, 1.0f, //C
    -2.f, 1.f, 0.0f, 1.0f,  // D

    /*Face 4*/
    -4.f, -1.f, 0.0f, 1.0f, //F
    -4.f, -1.f, 2.0f, 1.0f, //E
    -2.f, -1.f, 2.0f, 1.0f, //H
    -2.f, -1.f, 0.0f, 1.0f, // G

    /*Face 5*/
    -4.f, 1.f, 0.0f, 1.0f,  //A
    -4.f, 1.f, 2.0f, 1.0f, //B
    -4.f, -1.f, 2.0f, 1.0f, //E
    -4.f, -1.f, 0.0f, 1.0f, //F

    /*Face 6*/
    -2.f, 1.f, 0.0f, 1.0f,  // D
    -2.f, 1.f, 2.0f, 1.0f, //C
    -2.f, -1.f, 2.0f, 1.0f, //H
    -2.f, -1.f, 0.0f, 1.0f, // G

    /* Cube 2*/

    /*Face 1*/
    4.f, -1.f, 0.0f, 1.0f, //F
    4.f, 1.f, 0.0f, 1.0f,  //A
    2.f, 1.f, 0.0f, 1.0f,  // D
    2.f, -1.f, 0.0f, 1.0f, // G

    /*Face 2*/
    4.f, -1.f, 2.0f, 1.0f, //E
    4.f, 1.f, 2.0f, 1.0f, //B
    2.f, 1.f, 2.0f, 1.0f, //C
    2.f, -1.f, 2.0f, 1.0f, //H

    /*Face 3*/
    4.f, 1.f, 0.0f, 1.0f,  //A
    4.f, 1.f, 2.0f, 1.0f, //B
    2.f, 1.f, 2.0f, 1.0f, //C
    2.f, 1.f, 0.0f, 1.0f,  // D

    /*Face 4*/
    4.f, -1.f, 0.0f, 1.0f, //F
    4.f, -1.f, 2.0f, 1.0f, //E
    2.f, -1.f, 2.0f, 1.0f, //H
    2.f, -1.f, 0.0f, 1.0f, // G

    /*Face 5*/
    4.f, 1.f, 0.0f, 1.0f,  //A
    4.f, 1.f, 2.0f, 1.0f, //B
    4.f, -1.f, 2.0f, 1.0f, //E
    4.f, -1.f, 0.0f, 1.0f, //F

    /*Face 6*/
    2.f, 1.f, 0.0f, 1.0f,  // D
    2.f, 1.f, 2.0f, 1.0f, //C
    2.f, -1.f, 2.0f, 1.0f, //H
    2.f, -1.f, 0.0f, 1.0f // G

};

const float rectColor[6] = {
    0.0f, 0.6f, 0.0f,
    0.3f, 0.0f, 0.2f,
};

void InitializeVertexBuffer()
{
    glBindVertexArray(positionBufferObject);

    glGenBuffers(1, &rectangle); 
    glBindBuffer(GL_ARRAY_BUFFER, rectangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertex), rectVertex, GL_STATIC_DRAW);
    glColorPointer(3, GL_FLOAT, 0, &rectColor);
}

void
displayFunc (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* effacement du (z-)buffer ou s'effectuent les dessins */

  /* Transformation de projection */
  glMatrixMode (GL_PROJECTION);/* projection 3D-->2D */
  glLoadIdentity ();/*initialise la matrice a l'identite*/

  /* specification de la projection*/ 
  //glOrtho(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection parallele*/
   glFrustum(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection perspective*/

   /*  Transformation de point de vue */
   glMatrixMode (GL_MODELVIEW);/* pile courante = matrice de point de vue  */ 
   glLoadIdentity (); /*initialise la matrice a l'identite*/ 
   gluLookAt (0.0, 1.0, -5.0, 0.,0, 0, 0.0, 1.0, 0.0);   /*Visualisation de la scène */

   glUseProgram(shaderProg); 

   GLint translation = glGetUniformLocation(shaderProg, "translate");
   if (translation == -1) {
     fprintf(stderr, "Could not bind attribute %s\n","translate");
   }

   printf("\n je monte/descend de : %f\n", trans);
   if(trans >= 3.0)
     sens = 1;
   else if( trans <= 0.0)
     sens = 0;
   
   if(sens == 1){
     trans -= 0.001;
   }
   else if(sens == 0)
     trans += 0.001;
   
   glUniform1f(translation, trans);
  
    
   glBindVertexArray(positionBufferObject);
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, rectangle);
   glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0,0);

   int r = 0; int g = 0; int b = 200;

   for(int i = 0; i <= 20; i+=4){
     glColor3i(r, g, b);
     glDrawArrays(GL_QUADS, i, 4);
   }
   r+= 100; g = 0; b = 0;
   for(int i = 24; i <= 44; i+=4){
     glColor3i(r, g, b);
     glDrawArrays(GL_QUADS, i, 4);
   }

   
   glUseProgram(0);


   glDisableClientState(GL_COLOR_ARRAY);

   glutSwapBuffers (); //Echanger les buffer. Valable pour GLUT_DOUBLE
}



int
main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitWindowPosition (0, 0);/* position initiale */
    glutInitWindowSize (640, 480);/* taille initiale fenetre graphique */
    
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);/* affichage couleur */
    /* Definit le type de fenetre d'affichage par composition des constantes suivantes:
     - GLUT_RGBA ou GLUT_INDEX (vraies couleurs ou couleurs indexées),
     - GLUT_SINGLE ou GLUT_DOUBLE (simple ou double buffer),
     - GLUT_DEPTH, GLUT_STENCIL (utilisation de tampons profondeur, stencil).*/
    
    if (glutCreateWindow ("Initiation a OpenGL") <= 0)/* creation de la fenetre graphique */
    {
        fprintf (stderr, "Impossible de creer la fenetre Glut.\n");
        exit(EXIT_FAILURE);
    }
    
    // Setup GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err)
      {
	/* Problem: glewInit failed, something is seriously wrong. */
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    glClearColor (0.5, 0.5, 0.5, 1.0); /* definition de la couleur d'effacement (GL_COLOR_BUFFER_BIT) */
    
    
    shaderProg = setShaders();
    InitializeVertexBuffer(); 
    
    glutDisplayFunc (&displayFunc);/* fonction d'affichage */
    glutIdleFunc(&displayFunc);
    glutKeyboardFunc (&keyboardFunc); /* gestion du clavier */
    
    
    glutMainLoop ();/* lancement de la boucle principale */
    
    return EXIT_SUCCESS;
}
