
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
  GLchar* vertexSource = (GLchar*)readFile("first.vert");
  GLchar* fragmentSource = (GLchar*)readFile("first.frag");
 
	
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
  -0.3f,-0.3f,0.0f,1.0f,
  0.3f,-0.3f,0.0f,1.0f,
  0.3f,0.3f,0.0f,1.0f,
  -0.3f,0.3f,0.0f,1.0f
};

void InitializeVertexBuffer()
{
  glBindVertexArray(positionBufferObject);

  glGenBuffers(1, &rectangle); 
  glBindBuffer(GL_ARRAY_BUFFER, rectangle);    
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertex), rectVertex, GL_STATIC_DRAW);

}

void
displayFunc (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* effacement du (z-)buffer ou s'effectuent les dessins */
    
  glUseProgram(shaderProg);

  glColor3f(0.,1.,0.);/* couleur courante (vert)*/    
  glBindVertexArray(positionBufferObject);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, rectangle);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0,0);
  glDrawArrays(GL_QUADS, 0, 4);

  glUseProgram(0);

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
