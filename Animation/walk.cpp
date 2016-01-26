#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include "SimpleAnim.h"
using namespace std;

int RunMode = 0;

int boxleft = 50, boxbottom = 50;
int boxwidth = 50, boxheight = 50;
int screenwidth = 720,
    screenheight = 720;

float leftb   = -1,
      rightb  = -0.9,
      bottomb = -1,
      topb   = -0.9;


float AnimateStep = 0.1;


void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 'd':
			RunMode = 1;
			drawScene();
			RunMode = 0;
			break;
		case 'a':
			RunMode = 2;
			drawScene();
			RunMode = 0;
			break;
		case 'w':
			RunMode = 3;
			drawScene();
			RunMode = 0;
			break;
		case 's':
			RunMode = 4;
			drawScene();
			RunMode = 0;
			break;
		case 27:	// Escape key
			exit(1);
	}
}

void initRendering()
{
    glShadeModel( GL_FLAT );
    glEnable( GL_DEPTH_TEST );
}

void drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (RunMode==1) {
		leftb += AnimateStep;
     	rightb += AnimateStep;
     	if ( rightb > 1) {
			rightb = -0.9;
			leftb = -1;
		}
	}
	if (RunMode==2) {
		leftb -= AnimateStep;
      	rightb -= AnimateStep;
      	if ( leftb < -1 ) {
			leftb = 0.9;
			rightb = 1;
		}
	}
	if (RunMode==3) {
		topb += AnimateStep;
      	bottomb += AnimateStep;
      	if(topb > 1){
      		topb = -0.9;
      		bottomb = -1;
      	}
	}
	if (RunMode==4) {
		topb -= AnimateStep;
      	bottomb -= AnimateStep;
      	if(bottomb < -1 ){
      		topb = 1;
      		bottomb = 0.9;
      	}
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	

	glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(leftb,  topb);
        glVertex2f(rightb, topb);
        glVertex2f(rightb, bottomb);
        glVertex2f(leftb,  bottomb);
    glEnd();	
    glFlush();
    glutSwapBuffers();

	if ( RunMode==1 || RunMode == 2 ) {
		glutPostRedisplay();
	}

}


int main( int argc, char** argv )
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );


	glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 720, 720 );
    glutCreateWindow( "SimpleAnim" );

    initRendering();

   	glutKeyboardFunc( myKeyboardFunc );	

   	glutDisplayFunc( drawScene );

	glutMainLoop(  );
}