/*
 * Time-stamp: <Wed Apr 13 13:47:53 2016 (ysaemery)>
 * Created: Tue Apr 12 11:35:16 2016
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* fichiers d'entetes OpenGL, GLU, GLUT et GLEW */
#include <GL/glew.h> //OpenGL extension wrangler library
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


GLuint shaderProg;

GLuint positionBufferObject;
GLuint cube;


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
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
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
    GLchar* vertexSource = (GLchar*)readFile("illumination.vert");
    GLchar* fragmentSource = (GLchar*)readFile("illumination.frag");

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

const float cube1Vertex[] = {
    /* face 1 */
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    /* face 2 */
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    /* face 3 */
    1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    /* face 4 */
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,-1.0f, 1.0f,
    /* face 5 */
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    /* face 6 */
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f
};

void InitializeVertexBuffer()
{
    glBindVertexArray(positionBufferObject);

    glGenBuffers(1, &cube);
    glBindBuffer(GL_ARRAY_BUFFER, cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube1Vertex), cube1Vertex, GL_STATIC_DRAW);

}
void
displayFunc (void)
{
    glEnable(GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Transformation de projection */
    glMatrixMode(GL_PROJECTION);/* projection 3D-->2D */
    glLoadIdentity ();/*initialise la matrice a l'identite*/
    //gluPerspective(45.0, (float) 640/480, 1.0, 10.0);
    /* specification de la projection*/
    //   glOrtho(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection parallele*/
    glFrustum(-2.0,2.0,-2.0,2.0,1.0,10.0);  /*Projection perspective*/

    /*  Transformation de point de vue */
    glMatrixMode (GL_MODELVIEW);/* pile courante = matrice de point de vue  */
    glLoadIdentity (); /*initialise la matrice a l'identite*/
    gluLookAt (4.0, 6.0, 3.0, 0.,0, 0, 0.0, 1.0, 0.0);   /*Visualisation de la scène */

    glColor3i(50,0,100);

    glBegin(GL_QUADS);
    glVertex3i(1,1,1);
    glVertex3i(1,-1,1);
    glVertex3i(-1,-1,1);
    glVertex3i(-1,1,1);
    glVertex3i(1,1,-1);
    glVertex3i(1,-1,-1);
    glVertex3i(-1,-1,-1);
    glVertex3i(-1,1,-1);
    glVertex3i(1,1,1);
    glVertex3i(1,-1,1);
    glVertex3i(1,-1,-1);
    glVertex3i(1,1,-1);
    glVertex3i(-1,1,1);
    glVertex3i(-1,-1,1);
    glVertex3i(-1,-1,-1);
    glVertex3i(-1,1,-1);
    glVertex3i(-1,1,-1);
    glVertex3i(-1,1,1);
    glVertex3i(1,1,1);
    glVertex3i(1,1,-1);
    glVertex3i(-1,-1,-1);
    glVertex3i(-1,-1,1);
    glVertex3i(1,-1,1);
    glVertex3i(1,-1,-1);
    glEnd();

    glColor3i(0,0,100);

    glBegin(GL_QUADS);
    glVertex3f(1.5,1.5,1.5);
    glVertex3f(1.5,-1.5,1.5);
    glVertex3f(-1.5,-1.5,1.5);
    glVertex3f(-1.5,1.5,1.5);
    glVertex3f(1.5,1.5,-1.5);
    glVertex3f(1.5,-1.5,-1.5);
    glVertex3f(-1.5,-1.5,-1.5);
    glVertex3f(-1.5,1.5,-1.5);
    glVertex3f(1.5,1.5,1.5);
    glVertex3f(1.5,-1.5,1.5);
    glVertex3f(1.5,-1.5,-1.5);
    glVertex3f(1.5,1.5,-1.5);
    glVertex3f(-1.5,1.5,1.5);
    glVertex3f(-1.5,-1.5,1.5);
    glVertex3f(-1.5,-1.5,-1.5);
    glVertex3f(-1.5,1.5,-1.5);
    glVertex3f(-1.5,1.5,-1.5);
    glVertex3f(-1.5,1.5,1.5);
    glVertex3f(1.5,1.5,1.5);
    glVertex3f(1.5,1.5,-1.5);
    glVertex3f(-1.5,-1.5,-1.5);
    glVertex3f(-1.5,-1.5,1.5);
    glVertex3f(1.5,-1.5,1.5);
    glVertex3f(1.5,-1.5,-1.5);
    glEnd();

    glFlush();
    glutSwapBuffers ();
}


int
main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (640, 480);

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
    glClearColor (0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    shaderProg = setShaders();

    glutDisplayFunc (&displayFunc);/* fonction d'affichage */
    glutIdleFunc(&displayFunc);
    glutKeyboardFunc (&keyboardFunc); /* gestion du clavier */


    glutMainLoop ();/* lancement de la boucle principale */

    return EXIT_SUCCESS;
}
