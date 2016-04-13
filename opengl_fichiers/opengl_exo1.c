#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/* fichiers d'entetes OpenGL, GLU et GLUT */
#include <GL/glew.h> //OpenGL extension wrangler library

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>




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


void
displayFunc (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* effacement du (z-)buffer ou s'effectuent les dessins */
    
    glColor3f(0.,1.,0.);/* couleur courante (vert)*/
    glRectf(-0.3,-0.3,0.3,0.3) ; //Tracer un rectangle
    
    glutSwapBuffers (); //Echanger les buffer. Valable pour GLUT_DOUBLE
}


int
main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitWindowPosition (0, 0);/* position initiale */
    glutInitWindowSize (640, 480);/* taille initiale fenetre graphique */
    
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);/* affichage couleur */
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
    
    
    
    glutDisplayFunc (displayFunc);/* fonction d'affichage */
    glutKeyboardFunc (keyboardFunc); /* gestion du clavier */
    
    
    glutMainLoop ();/* lancement de la boucle principale */
    
    return EXIT_SUCCESS;
}

