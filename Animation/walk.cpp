#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include "SimpleAnim.h"

int RunMode = 0;
int boxleft = 100, boxbottom = 100;
int boxwidth = 100, boxheight = 100;
int screenwidth = 720,
    screenheight = 720;

float left   = (float)boxleft / screenwidth,
      right  = left + (float)boxwidth / screenwidth,
      bottom = (float)boxbottom / screenheight,
      top    = bottom + (float)boxheight / screenheight;


float AnimateStep = 0.1;

const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 'a':
		RunMode = 1;
		drawRScene();
		RunMode = 0;
		break;
	case 'd':
		RunMode = 1;
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
        left += AnimateStep;
        right += AnimateStep;
		if ( right > 360.0 ) {
			right -= 360.0;
		}
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	

	glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(left,  top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left,  bottom);
    glEnd();	
    glFlush();
    glutSwapBuffers();

	if ( RunMode==1 ) {
		glutPostRedisplay();
	}

}
void drawRScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (RunMode==1) {
        left -= AnimateStep;
        right -= AnimateStep;
		if ( left > 360.0 ) {
			left += 360.0;
		}
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(left,  top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left,  bottom);
    glEnd();
    glFlush();
    glutSwapBuffers();

	if ( RunMode==1 ) {
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