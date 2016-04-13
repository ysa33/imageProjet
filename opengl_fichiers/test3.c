
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
GLuint coordBuffer, colorBuffer;
GLint  attributeColor;

float angle = 0;
float trans = 0;

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
  GLchar* vertexSource = (GLchar*)readFile("newshad2.vert");
  GLchar* fragmentSource = (GLchar*)readFile("newshad2.frag");
 
	
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

static const GLfloat rectVertex[] = {
  /* Cube 1*/
  -0.3f,-0.3f,0.3f,1.0f, // face sup�rieure
  0.3f,-0.3f,0.3f,1.0f,
  0.3f,0.3f,0.3f,1.0f,
  -0.3f,0.3f,0.3f,1.0f,
  
  -0.3f,-0.3f,-0.3f,1.0f, // face inf�rieure
  0.3f,-0.3f,-0.3f,1.0f,
  0.3f,0.3f,-0.3f,1.0f,
  -0.3f,0.3f,-0.3f,1.0f,  
  
  -0.3f,-0.3f,-0.3f,1.0f, // face derri�re
  -0.3f,0.3f,-0.3f,1.0f,
  -0.3f,0.3f,0.3f,1.0f,
  -0.3f,-0.3f,0.3f,1.0f,
  
  0.3f,-0.3f,-0.3f,1.0f, // face devant
  0.3f,0.3f,-0.3f,1.0f,
  0.3f,0.3f,0.3f,1.0f,
  0.3f,-0.3f,0.3f,1.0f,
  
  -0.3f,-0.3f,-0.3f,1.0f, // face gauche
  0.3f,-0.3f,-0.3f,1.0f,
  0.3f,-0.3f,0.3f,1.0f,
  -0.3f,-0.3f,0.3f,1.0f,
  
  -0.3f,0.3f,-0.3f,1.0f, // face droite
  0.3f,0.3f,-0.3f,1.0f,
  0.3f,0.3f,0.3f,1.0f,
  -0.3f,0.3f,0.3f,1.0f

};

static const GLfloat rectColor[] = {
    /* Cube 1 */
    0.583f,  0.771f,  0.014f, // face sup�rieure
    0.583f,  0.771f,  0.014f,
    0.583f,  0.771f,  0.014f,
    0.583f,  0.771f,  0.014f,

    0.609f,  0.115f,  0.436f, // face inf�rieure
    0.609f,  0.115f,  0.436f,
    0.609f,  0.115f,  0.436f,
    0.609f,  0.115f,  0.436f,
    
    0.327f,  0.483f,  0.844f, // face derri�re
    0.327f,  0.483f,  0.844f, 
    0.327f,  0.483f,  0.844f, 
    0.327f,  0.483f,  0.844f, 
    
    0.822f,  0.569f,  0.201f, // face devant
    0.822f,  0.569f,  0.201f,
    0.822f,  0.569f,  0.201f,
    0.822f,  0.569f,  0.201f,
    
    0.135f,  0.602f,  0.223f, // face gauche
    0.135f,  0.602f,  0.223f, 
    0.135f,  0.602f,  0.223f, 
    0.135f,  0.602f,  0.223f, 
    
    0.714f,  0.505f,  0.345f, // face droite
    0.714f,  0.505f,  0.345f,
    0.714f,  0.505f,  0.345f,
    0.714f,  0.505f,  0.345f
};


void InitializeVertexBuffer()
{
  glBindVertexArray(positionBufferObject);

  glGenBuffers(1, &coordBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);    
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertex), rectVertex, GL_STATIC_DRAW);

  glGenBuffers(1, &colorBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectColor), rectColor, GL_STATIC_DRAW); 

  attributeColor = glGetAttribLocation(shaderProg,"v_color");
  if (attributeColor == -1) {
    fprintf(stderr, "Could not bind attribute %s\n","color");
  }

}

void
displayFunc (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* effacement du (z-)buffer ou s'effectuent les dessins */

  /* activation du z-buffer */
  glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);

    /* Transformation de projection */
    glMatrixMode (GL_PROJECTION);/* projection 3D-->2D */
    glLoadIdentity ();/*initialise la matrice a l'identite*/
    gluPerspective(45,(double) 640/480, 0.1, 100.0);
    
    /* specification de la projection*/ 
    //glOrtho(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection parallele*/
    //glFrustum(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection perspective*/ 

    /*  Transformation de point de vue */
    glMatrixMode (GL_MODELVIEW);/* pile courante = matrice de point de vue  */ 
    glLoadIdentity(); /*initialise la matrice a l'identite*/ 
    gluLookAt(1.0, 0.0, 3.0, 0.0 ,0.0, 0.0, 0.0, 1.0, 0.0);   /*Visualisation de la sc�ne */ 
  
  glPushMatrix();

  GLfloat Light0[] = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat lightPos[] = {0.0f, 0.0f, 2.0f, 1.0f};
  GLfloat Light[] = {1.0f, 1.0f, 1.0f, 1.0f};
 
   

  glLightfv(GL_LIGHT0, GL_AMBIENT, Light0 );
  glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
  glLightfv(GL_LIGHT0,GL_SPECULAR,Light);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,Light);

  GLfloat Ambient[]={0.4,0.4,0.4,1.0};  	          
  GLfloat Diffus[]={0.1,0.5,0.3,1.0};  	          
  GLfloat Specular[]={1.0,0.0,0.0,1.0};  	             
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Ambient);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Diffus);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Specular);
  glMateriali(GL_FRONT,GL_SHININESS,10.0);
 
  glTranslatef(-0.7f, 0.0f, 0.0f);

  /* operations avec le shader */
  glUseProgram(shaderProg);
  GLint rotation = glGetUniformLocation(shaderProg, "rotangle");
  GLint translation = glGetUniformLocation(shaderProg, "translate");
  GLint ordre = glGetUniformLocation(shaderProg, "ordre");
  if (rotation == -1) {
    fprintf(stderr, "Could not bind attribute %s\n","rotate");
  }
  if (ordre == -1) {
    fprintf(stderr, "Could not bind attribute %s\n","ordre");
  }
  if(translation == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", "translate");
  }

  glUniform1i(translation, trans);
  glUniform1i(rotation, angle);
  glUniform1i(ordre, 1); // quoi faire d'abord ? 1=rotation, autre=rotation
  trans += 0.1;
  angle += 0.1; // mise � jour de la variable globale
    
  glBindVertexArray(positionBufferObject);

  // 1er buffer d'attributes (positions)
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  //2�me buffer d'attributes (couleurs)
  glEnableVertexAttribArray(attributeColor);
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glDrawArrays(GL_QUADS, 0, 4*6);

  glPopMatrix();

  glPushMatrix();

  glTranslatef(0.7f, 0.0f, 0.0f);

  glDrawArrays(GL_QUADS, 0, 4*6);

  glPopMatrix();

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
