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

float leftb   = 0,
      rightb  = 0.1,
      bottomb = 0,
      topb   = 0.1;


float AnimateStep = 0.1f;

const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 'a':
		RunMode = 2;
		drawScene();
		cout << leftb << " , " << rightb << endl;
		RunMode = 0;
		break;
	case 'd':
		RunMode = 1;
		drawScene();
		cout << leftb << " , " << rightb << endl;
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
		if ( rightb == 1 ) {
			rightb = 0.1;
			leftb = 0;
		}
        leftb += AnimateStep;
        rightb += AnimateStep;
	}
	if (RunMode==2) {
		if ( leftb == 0 ) {
			leftb = 0.9;
			rightb = 1.0;
		} else {
			leftb -= AnimateStep;
      	    rightb -= AnimateStep;
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
void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport( 0, 0, w, h );

	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {
		scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
		center = (Xmax+Xmin)/2;
		windowXmin = center - (center-Xmin)*scale;
		windowXmax = center + (Xmax-center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
		center = (Ymax+Ymin)/2;
		windowYmin = center - (center-Ymin)*scale;
		windowYmax = center + (Ymax-center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}
	
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, -1, 1 );

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

   	glutReshapeFunc( resizeWindow );

   	glutDisplayFunc( drawScene );

	glutMainLoop(  );
}