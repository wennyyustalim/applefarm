#include <iostream>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define PI 3.1415927

#include "imageloader.h"

using namespace std;

// Variables OpenGL id of the texture
GLuint _textureId;

void draw_cylinder(GLfloat x,
				   GLfloat y,
				   GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B) {
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}



const float BOX_SIZE = 5.0f; //The length of each side of the cube
float angleX = 0;            //The rotation of the box
float angleY = 0;

void incrementAngle(float& angle) {
	angle+=3.0f;
	if(angle > 360) {
		angle-=360;
	}
}

void decrementAngle(float& angle) {
	angle-=3.0f;
	if(angle < 0) {
		angle+=360;
	}
}

int prevX = 0;
int prevY = 0;

void mouseClickHandler(int button, int state, int x, int y) {
	// printf("%d %d %d %d\n",button,state,x,y ); 
	if(state == 0) {
		prevX = x;
		prevY = y;
	}
}

void processMouseActiveMotion(int x, int y) {
	angleX-= x-prevX;
	angleY-= y-prevY;
	if(angleX > 360) {
		angleX -= 360;
	}
	if(angleY > 360) {
		angleY -= 360;
	}

	if(angleX < 0) {
		angleX += 360;
	}

	if(angleY < 0) {
		angleY += 360;
	}
	prevX = x;
	prevY = y;
	glutPostRedisplay();
	// printf("%d %d\n",x,y ); 	
}


void handleKeypress(unsigned char key, int x, int y) {
	// printf("key: %c\n", key);
	switch (key) {
		case 27: //Escape key
			exit(0);
		case 'A':
		case 'a':
			decrementAngle(angleX);
			break;
		case 'D':
		case 'd':
			incrementAngle(angleX);
			break;
		case 'W':
		case 'w':
			decrementAngle(angleY);
			break;
		case 'S':
		case 's':
			incrementAngle(angleY);
			break;
	}
	glutPostRedisplay();
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("images/right.bmp");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// make it transparent 
	_textureId = loadTexture(image);
	
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawCar(int _textureId) {
	glRotatef(-angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(-angleY, 1.0f, 0.0f, 0.0f);

	// glColor3f(0.459084,0.184313,0.184313);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	//Front Face
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE/2,-BOX_SIZE/2,BOX_SIZE);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(BOX_SIZE/2,-BOX_SIZE/2,BOX_SIZE);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE/2,-BOX_SIZE/5,BOX_SIZE);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-BOX_SIZE/2,-BOX_SIZE/5,BOX_SIZE);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/2+1.2f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/2+1.2f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/5,BOX_SIZE+0.1f);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/5,BOX_SIZE+0.1f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/2+1.0f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/2+1.0f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/5-0.83f,BOX_SIZE+0.1f);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/5-0.83f,BOX_SIZE+0.1f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/2+0.5f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/2+0.5f,BOX_SIZE+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f,-BOX_SIZE/5-1.3f,BOX_SIZE+0.1f);
	glVertex3f(-BOX_SIZE/2+0.5f,-BOX_SIZE/5-1.3f,BOX_SIZE+0.1f);
	glEnd();

	glColor3f(0.459084,0.184313,0.184313);
	//Kap Mobil
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/5,BOX_SIZE); 
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/5,BOX_SIZE); 
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glEnd();


	//KacaDepan Mobil
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glEnd();

	//kaca hitam mobil
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2-0.5f, 0,BOX_SIZE/3+0.1f); 
	glVertex3f(-BOX_SIZE/2+0.5f, 0,BOX_SIZE/3+0.1f); 
	glVertex3f(-BOX_SIZE/2+0.5f, BOX_SIZE/2-0.35f,BOX_SIZE/5+0.1f);
	glVertex3f(BOX_SIZE/2-0.5f, BOX_SIZE/2-0.35f,BOX_SIZE/5+0.1f);
	glEnd();

	//Atap Mobil
    //texture for atap image 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	// glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glEnd();

	//KacaBelakangMobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glEnd();

	//kaca hitam belakang mobil
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2-0.5f, BOX_SIZE/2-0.03f, -BOX_SIZE*1.2-0.01f);
	glVertex3f(-BOX_SIZE/2+0.5f, BOX_SIZE/2-0.03f, -BOX_SIZE*1.2-0.01f);
	glVertex3f(-BOX_SIZE/2+0.5f, 0, -BOX_SIZE*1.4-0.01f);
	glVertex3f(BOX_SIZE/2-0.5f, 0, -BOX_SIZE*1.4-0.01f);
	glEnd();

	//Bagasi Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glEnd();

	//Kolong Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glEnd();


	//Sisi Kanan Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/5, BOX_SIZE);
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2,BOX_SIZE/3); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2,BOX_SIZE/3); 
	glEnd();

	// kaca kanan
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2+0.01f, 0.1f,BOX_SIZE/3-0.35f); 
	glVertex3f(BOX_SIZE/2+0.01f, BOX_SIZE/2-0.35f,BOX_SIZE/5-0.35f);
	glVertex3f(BOX_SIZE/2+0.01f, BOX_SIZE/2-0.35f, -BOX_SIZE*1.2+0.35f);
	glVertex3f(BOX_SIZE/2+0.01f, 0.1f, -BOX_SIZE*1.4+0.35f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2+0.01f, -0.5f,BOX_SIZE/8-1.5f); 
	glVertex3f(BOX_SIZE/2+0.01f, -0.5f, -BOX_SIZE/8-1.5f);
	glVertex3f(BOX_SIZE/2+0.01f, -0.8f, -BOX_SIZE/8-1.5f);
	glVertex3f(BOX_SIZE/2+0.01f, -0.8f,BOX_SIZE/8-1.5f); 
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2+0.01f, -0.5f,BOX_SIZE/8-4.5f); 
	glVertex3f(BOX_SIZE/2+0.01f, -0.5f, -BOX_SIZE/8-4.5f);
	glVertex3f(BOX_SIZE/2+0.01f, -0.8f, -BOX_SIZE/8-4.5f);
	glVertex3f(BOX_SIZE/2+0.01f, -0.8f,BOX_SIZE/8-4.5f); 
	glEnd();


	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/5, BOX_SIZE);
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2,BOX_SIZE/3); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2,BOX_SIZE/3); 
	glEnd();

	// kaca kiri
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2-0.01f, 0,BOX_SIZE/3-0.35f); 
	glVertex3f(-BOX_SIZE/2-0.01f, BOX_SIZE/2-0.35f,BOX_SIZE/5-0.35f);
	glVertex3f(-BOX_SIZE/2-0.01f, BOX_SIZE/2-0.35f, -BOX_SIZE*1.2+0.35f);
	glVertex3f(-BOX_SIZE/2-0.01f, 0, -BOX_SIZE*1.4+0.35f);
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.5f,BOX_SIZE/8-1.5f); 
	glVertex3f(-BOX_SIZE/2-0.01f, -0.5f, -BOX_SIZE/8-1.5f);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.8f, -BOX_SIZE/8-1.5f);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.8f,BOX_SIZE/8-1.5f); 
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.5f,BOX_SIZE/8-4.5f); 
	glVertex3f(-BOX_SIZE/2-0.01f, -0.5f, -BOX_SIZE/8-4.5f);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.8f, -BOX_SIZE/8-4.5f);
	glVertex3f(-BOX_SIZE/2-0.01f, -0.8f,BOX_SIZE/8-4.5f); 
	glEnd();

	glColor3f(1,1,1);
	// Roda kiri depan
	GLUquadricObj *quadratic;
	glTranslatef((BOX_SIZE/2)-.5,-BOX_SIZE/2,BOX_SIZE/3);
	quadratic = gluNewQuadric();
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic,1.0f,1.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,1);
	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,-1);
	glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

	// Roda kanan depan
	glTranslatef(-BOX_SIZE,0,0);
	GLUquadricObj *quadratic2;
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	quadratic2 = gluNewQuadric();
	gluCylinder(quadratic2,1.0f,1.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic2);

	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,1);
	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,-1);

	glRotated(-90.0f, 0.0f, 1.0f, 0.0f);


	glTranslatef(0,0,-BOX_SIZE*1.2);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	quadratic2 = gluNewQuadric();
	gluCylinder(quadratic2,1.0f,1.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic2);

	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,1);
	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,-1);

	glRotated(-90.0f, 0.0f, 1.0f, 0.0f);

	glTranslatef(BOX_SIZE,0,0);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	quadratic2 = gluNewQuadric();
	gluCylinder(quadratic2,1.0f,1.0f,1.0f,32,32);

	gluDeleteQuadric(quadratic2);

	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,1);
	quadratic = gluNewQuadric();
	gluDisk(quadratic,0.0f,1.0f,32,32);
	gluDeleteQuadric(quadratic);
	glTranslatef(0,0,-1);

	
	glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -20.0f);
	
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	//draw cube
	glPushMatrix();
	glTranslatef(0, BOX_SIZE, -10);
	drawCar(_textureId);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow("AppleFarm - Kijang");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(mouseClickHandler);
	glutMotionFunc(processMouseActiveMotion);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}









