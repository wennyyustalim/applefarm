#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <string.h>

GLint WINDOW_SIZE_X = 1000;
GLint WINDOW_SIZE_Y = 800;
GLint WINDOW_START_X = 0;
GLint WINDOW_START_Y = 0;

// GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0;   /* x,y,z translation */
// GLfloat tx=295,ty=62;
// GLfloat xs=1.0,ys=1.0,zs=1.0;

// GLfloat xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0;    axis angles 

// GLfloat r=0,g=0,b=1;
// GLint light=1;
// int count=1,flg=1;
// int view=0;
// int flag1=0,aflag=1;            //to switch car driving mode
// int flag2=0,wheelflag=0;   //to switch fog effect
GLUquadricObj *t;


GLvoid DrawGLScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f( 1, 1, 0 ); // red
	glVertex2f( -0.8, -0.8 );
	glColor3f( 0.3, 0.4, 0 ); // green
	glVertex2f( 0.8, -0.8 );
	glColor3f( 0, 0, 1 ); // blue
	glVertex2f( 0, 0.9 );
	glEnd(); 

	glutSwapBuffers();
}

GLvoid Transform(GLfloat Width, GLfloat Height) {
  glViewport(0, 0, Width, Height);              /* Set the viewport */
  glMatrixMode(GL_PROJECTION);                  /* Select the projection matrix */
  glLoadIdentity();				/* Reset The Projection Matrix */
  gluPerspective(45.0,Width/Height,0.1,100.0);  /* Calculate The Aspect Ratio Of The Window */
  glMatrixMode(GL_MODELVIEW);                   /* Switch back to the modelview matrix */
}

GLvoid InitGL(GLfloat Width, GLfloat Height) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(2.0);              /* Add line width,   ditto */
	Transform( Width, Height ); /* Perform the transformation */
	//newly added
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA |
						GLUT_DOUBLE |
						GLUT_DEPTH);
	glutInitWindowSize(WINDOW_SIZE_X,WINDOW_SIZE_Y);
	glutInitWindowPosition(WINDOW_START_X, WINDOW_START_Y);

	glutCreateWindow("AppleFarm Kijang");
	glutDisplayFunc(DrawGLScene);
	InitGL(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutMainLoop();
	return 1;
}