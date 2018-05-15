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
#include <bits/stdc++.h>
#include "imageloader.h"

using namespace std;

// Variables OpenGL id of the texture
GLuint _textureId;
long long tick = 0 ;
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

// Rotating the car
const float MODEL_SIZE = 5.0f; //The length of each side of the cube
float angleX = 0;            //The rotation of the box
float angleY = 0;

// Slider button coordinates
float x1_ambient = -8.0f;
float x2_ambient = -7.5f;
float x3_ambient = -7.5f;
float x4_ambient = -8.0f;

float x1_diffuse = -8.0f;
float x2_diffuse = -7.5f;
float x3_diffuse = -7.5f;
float x4_diffuse = -8.0f;

float x1_specular = -8.0f;
float x2_specular = -7.5f;
float x3_specular = -7.5f;
float x4_specular = -8.0f;

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

// Adjust lighting for the car
GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[] = {-2 * MODEL_SIZE, MODEL_SIZE, 4 * MODEL_SIZE, 1.0f};

void increaseAmbient() {
	for (int i = 0; i < 3; i++) {
		ambientLight[i] += 0.1f;
	}
}

void decreaseAmbient() {
	for (int i = 0; i < 3; i++) {
		ambientLight[i] -= 0.1f;
	}
}

void increaseDiffuse() {
	for (int i = 0; i < 3; i++) {
		diffuseLight[i] += 0.1f;
	}
}

void decreaseDiffuse() {
	for (int i = 0; i < 3; i++) {
		diffuseLight[i] -= 0.1f;
	}
}

void increaseSpecular() {
	for (int i = 0; i < 3; i++) {
		specularLight[i] += 0.1f;
	}
}

void decreaseSpecular() {
	for (int i = 0; i < 3; i++) {
		specularLight[i] -= 0.1f;
	}
}

// Move sliders
void slideAmbientRight() {
	x1_ambient += 0.5f;
	x2_ambient += 0.5f;
	x3_ambient += 0.5f;
	x4_ambient += 0.5f;
}

void slideAmbientLeft() {
	x1_ambient -= 0.5f;
	x2_ambient -= 0.5f;
	x3_ambient -= 0.5f;
	x4_ambient -= 0.5f;
}

void slideDiffuseRight() {
	x1_diffuse += 0.5f;
	x2_diffuse += 0.5f;
	x3_diffuse += 0.5f;
	x4_diffuse += 0.5f;
}

void slideDiffuseLeft() {
	x1_diffuse -= 0.5f;
	x2_diffuse -= 0.5f;
	x3_diffuse -= 0.5f;
	x4_diffuse -= 0.5f;
}

void slideSpecularRight() {
	x1_specular += 0.5f;
	x2_specular += 0.5f;
	x3_specular += 0.5f;
	x4_specular += 0.5f;
}

void slideSpecularLeft() {
	x1_specular -= 0.5f;
	x2_specular -= 0.5f;
	x3_specular -= 0.5f;
	x4_specular -= 0.5f;
}

int prevX = 0;
int prevY = 0;

void mouseClickHandler(int button, int state, int x, int y) {
	if(state == 0) {
		prevX = x;
		prevY = y;
	}
}

void processMouseActiveMotion(int x, int y) {
	angleX-= x-prevX;
	// angleY-= y-prevY;
	if(angleX > 360) {
		angleX -= 360;
	}
	// if(angleY > 360) {
	// 	angleY -= 360;
	// }

	// if(angleX < 0) {
	// 	angleX += 360;
	// }

	if(angleY < 0) {
		angleY += 360;
	}
	prevX = x;
	prevY = y;
	glutPostRedisplay();
}


void handleKeypress(unsigned char key, int x, int y) {
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

		// Sliders
		case 'U':
		case 'u':
			if(x1_ambient > -8.0f) {
				slideAmbientLeft();
				decreaseAmbient();
			}
			break;
		case 'I':
		case 'i':
			if(x2_ambient < 8.0f) {
				slideAmbientRight();
				increaseAmbient();
			}
			break;
		case 'J':
		case 'j':
			if (x1_diffuse > -8.0f) {
				slideDiffuseLeft();
				decreaseDiffuse();				
			}
			break;
		case 'K':
		case 'k':
			if (x2_diffuse < 8.0f) {
				slideDiffuseRight();
				increaseDiffuse();				
			}
			break;
		case 'M':
		case 'm':
			if (x2_specular < 8.0f) {
				slideSpecularRight();
				increaseSpecular();
			}
			break;
		case 'N':
		case 'n':
			if (x1_specular > -8.0f) {
				slideSpecularLeft();
				decreaseSpecular();				
			}
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

void drawSlider() {

	// //Ambience slider
	// glBegin(GL_POLYGON);
	// glColor3f(0.7f, 0.7f, 0.7f);
	// glVertex3f(x1_ambient, -9.5f, 6.0f);
	// glVertex3f(x2_ambient, -9.5f, 6.0f);
	// glVertex3f(x3_ambient, -8.0f, 6.0f);
	// glVertex3f(x4_ambient, -8.0f, 6.0f);
	// glEnd();

	// //Diffuse Button
	// glBegin(GL_POLYGON);
	// glColor3f(0.5f, 0.5f, 0.5f);
	// glVertex3f(x1_diffuse, -11.5f, 6.0f);
	// glVertex3f(x2_diffuse, -11.5f, 6.0f);
	// glVertex3f(x3_diffuse, -10.0f, 6.0f);
	// glVertex3f(x4_diffuse, -10.0f, 6.0f);
	// glEnd();

	// //Specular Button
	// glBegin(GL_POLYGON);
	// glColor3f(0.5f, 0.5f, 0.5f);
	// glVertex3f(x1_specular, -13.5f, 6.0f);
	// glVertex3f(x2_specular, -13.5f, 6.0f);
	// glVertex3f(x3_specular, -12.0f, 6.0f);
	// glVertex3f(x4_specular, -12.0f, 6.0f);
	// glEnd();

	// //Ambience slider
	// glBegin(GL_POLYGON);
	// glColor3f(0.7f, 1.0f, 0.3f);
	// glVertex3f(-8.0f, -9.0f, 6.0f);
	// glVertex3f(8.0f, -9.0f, 6.0f);
	// glVertex3f(8.0f, -8.5f, 6.0f);
	// glVertex3f(-8.0f, -8.5f, 6.0f);
	// glEnd();
	
	// //Diffuse slider
	// glBegin(GL_POLYGON);
	// glColor3f(0.5f, 0.5f, 0.5f);
	// glVertex3f(-8.0f, -11.0f, 6.0f);
	// glVertex3f(8.0f, -11.0f, 6.0f);
	// glVertex3f(8.0f, -10.5f, 6.0f);
	// glVertex3f(-8.0f, -10.5f, 6.0f);
	// glEnd();

	// //Specular Slider
	// glBegin(GL_POLYGON);
	// glColor3f(1.0f, 0.9f, 0.2f);
	// glVertex3f(-8.0f, -13.0f, 6.0f);
	// glVertex3f(8.0f, -13.0f, 6.0f);
	// glVertex3f(8.0f, -12.5f, 6.0f);
	// glVertex3f(-8.0f, -12.5f, 6.0f);
	// glEnd();
}

void drawCar(int _textureId) {
	glRotatef(-angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(-angleY, 1.0f, 0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0.0f, -12.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-30,-MODEL_SIZE,30);
	glVertex3f(30,-MODEL_SIZE,30);
	glVertex3f(30,-MODEL_SIZE,-30);
	glVertex3f(-30,-MODEL_SIZE,-30);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	//Front Face
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-MODEL_SIZE/2,-MODEL_SIZE/2,MODEL_SIZE);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(MODEL_SIZE/2,-MODEL_SIZE/2,MODEL_SIZE);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(MODEL_SIZE/2,-MODEL_SIZE/5,MODEL_SIZE);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-MODEL_SIZE/2,-MODEL_SIZE/5,MODEL_SIZE);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/2+1.2f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/2+1.2f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/5,MODEL_SIZE+0.1f);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/5,MODEL_SIZE+0.1f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/2+1.0f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/2+1.0f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/5-0.83f,MODEL_SIZE+0.1f);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/5-0.83f,MODEL_SIZE+0.1f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/2+0.5f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/2+0.5f,MODEL_SIZE+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f,-MODEL_SIZE/5-1.3f,MODEL_SIZE+0.1f);
	glVertex3f(-MODEL_SIZE/2+0.5f,-MODEL_SIZE/5-1.3f,MODEL_SIZE+0.1f);
	glEnd();

	glColor3f(0.459084,0.184313,0.184313);

	//Kap Mobil
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/5,MODEL_SIZE); 
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/5,MODEL_SIZE); 
	glVertex3f(MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(-MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glEnd();


	//KacaDepan Mobil
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(-MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glEnd();

	//kaca hitam mobil
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2-0.5f, 0,MODEL_SIZE/3+0.1f); 
	glVertex3f(-MODEL_SIZE/2+0.5f, 0,MODEL_SIZE/3+0.1f); 
	glVertex3f(-MODEL_SIZE/2+0.5f, MODEL_SIZE/2-0.35f,MODEL_SIZE/5+0.1f);
	glVertex3f(MODEL_SIZE/2-0.5f, MODEL_SIZE/2-0.35f,MODEL_SIZE/5+0.1f);
	glEnd();

	//Atap Mobil
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glEnd();

	//KacaBelakangMobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glVertex3f(-MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glVertex3f(MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glEnd();

	//kaca hitam belakang mobil
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2-0.5f, MODEL_SIZE/2-0.03f, -MODEL_SIZE*1.2-0.01f);
	glVertex3f(-MODEL_SIZE/2+0.5f, MODEL_SIZE/2-0.03f, -MODEL_SIZE*1.2-0.01f);
	glVertex3f(-MODEL_SIZE/2+0.5f, 0, -MODEL_SIZE*1.4-0.01f);
	glVertex3f(MODEL_SIZE/2-0.5f, 0, -MODEL_SIZE*1.4-0.01f);
	glEnd();

	//Bagasi Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glVertex3f(MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glEnd();

	//Kolong Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2, MODEL_SIZE);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2, MODEL_SIZE);
	glEnd();


	//Sisi Kanan Mobil
	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2, MODEL_SIZE);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/5, MODEL_SIZE);
	glVertex3f(MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2,MODEL_SIZE/3); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glVertex3f(MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glVertex3f(MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glVertex3f(MODEL_SIZE/2, -MODEL_SIZE/2,MODEL_SIZE/3); 
	glEnd();

	// kaca kanan
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2+0.01f, 0.1f,MODEL_SIZE/3-0.35f); 
	glVertex3f(MODEL_SIZE/2+0.01f, MODEL_SIZE/2-0.35f,MODEL_SIZE/5-0.35f);
	glVertex3f(MODEL_SIZE/2+0.01f, MODEL_SIZE/2-0.35f, -MODEL_SIZE*1.2+0.35f);
	glVertex3f(MODEL_SIZE/2+0.01f, 0.1f, -MODEL_SIZE*1.4+0.35f);
	glEnd();

	glColor3f(0.158824, 0.158824, 0.158824);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.5f,MODEL_SIZE/8-1.5f); 
	glVertex3f(MODEL_SIZE/2+0.01f, -0.5f, -MODEL_SIZE/8-1.5f);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.8f, -MODEL_SIZE/8-1.5f);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.8f,MODEL_SIZE/8-1.5f); 
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.5f,MODEL_SIZE/8-4.5f); 
	glVertex3f(MODEL_SIZE/2+0.01f, -0.5f, -MODEL_SIZE/8-4.5f);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.8f, -MODEL_SIZE/8-4.5f);
	glVertex3f(MODEL_SIZE/2+0.01f, -0.8f,MODEL_SIZE/8-4.5f); 
	glEnd();

	glColor3f(0.459084,0.184313,0.184313);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2, MODEL_SIZE);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/5, MODEL_SIZE);
	glVertex3f(-MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2,MODEL_SIZE/3); 
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2, 0,MODEL_SIZE/3); 
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2,MODEL_SIZE/5);
	glVertex3f(-MODEL_SIZE/2, MODEL_SIZE/2, -MODEL_SIZE*1.2);
	glVertex3f(-MODEL_SIZE/2, 0, -MODEL_SIZE*1.4);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2, -MODEL_SIZE*1.4);
	glVertex3f(-MODEL_SIZE/2, -MODEL_SIZE/2,MODEL_SIZE/3); 
	glEnd();

	// kaca kiri
	glColor3f(0.258824, 0.258824, 0.258824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2-0.01f, 0,MODEL_SIZE/3-0.35f); 
	glVertex3f(-MODEL_SIZE/2-0.01f, MODEL_SIZE/2-0.35f,MODEL_SIZE/5-0.35f);
	glVertex3f(-MODEL_SIZE/2-0.01f, MODEL_SIZE/2-0.35f, -MODEL_SIZE*1.2+0.35f);
	glVertex3f(-MODEL_SIZE/2-0.01f, 0, -MODEL_SIZE*1.4+0.35f);
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.5f,MODEL_SIZE/8-1.5f); 
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.5f, -MODEL_SIZE/8-1.5f);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.8f, -MODEL_SIZE/8-1.5f);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.8f,MODEL_SIZE/8-1.5f); 
	glEnd();

	glColor3f(0.155824, 0.155824, 0.155824);
	glBegin(GL_POLYGON);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.5f,MODEL_SIZE/8-4.5f); 
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.5f, -MODEL_SIZE/8-4.5f);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.8f, -MODEL_SIZE/8-4.5f);
	glVertex3f(-MODEL_SIZE/2-0.01f, -0.8f,MODEL_SIZE/8-4.5f); 
	glEnd();

	glColor3f(1,1,1);
	// Roda kiri depan
	GLUquadricObj *quadratic;
	glTranslatef((MODEL_SIZE/2)-.5,-MODEL_SIZE/2,MODEL_SIZE/3);
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
	glTranslatef(-MODEL_SIZE,0,0);
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

	glTranslatef(0,0,-MODEL_SIZE*1.2);
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

	glTranslatef(MODEL_SIZE,0,0);
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

void timerController(int) {
	// printf("%d", tick);
	glutPostRedisplay();
	glutTimerFunc(16, timerController, 0);
}
// float speed = 0.2;

class Raindrop {
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
		float speed = 0.2;
		bool gravitate() {
			if(y < -18.0f) {
				return true;
			}
			y-= speed;
			return false; 
		}
};
vector<Raindrop> raindrops;


void drawRain() {
	glColor3f(.306f, .408f, .506f);
	// glColor3f(0.8,0.8,0.8);
	glRotatef(-angleX, 0.0f, 1.0f, 0.0f);
	// glRotatef(-angleY, 1.0f, 0.0f, 0.0f);
	if(rand()%4 == 3) {
		Raindrop raindrop;
		raindrop.x = rand()%26 - 12.5;
		raindrop.y = 15;
		raindrop.z = rand()%40 - 20;		
		int speed = rand()%10;
		raindrop.speed = (speed*.01) + .1;

		raindrops.push_back(raindrop);
	}
	for(vector<Raindrop>::iterator it = raindrops.begin(); it!= raindrops.end();) {
		if(it->gravitate()) {
			it = raindrops.erase(it);
		} else {
			glBegin(GL_LINES);
				glVertex3f(it->x, it->y,it->z);
				glVertex3f(it->x, it->y+0.5,it->z);
			glEnd();
			++it;
		}
		
	}
	// for(int i=0; i<150; i++) {
			
	// }

}


void drawScene() {
	glClearColor(.5294f, .8078f,  .9216f, 1.0f);	// White Background
		glClearColor(.027f, .0f,  .345f, 1.0f);	// White Background

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -20.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	//draw cube
	glPushMatrix();
	glTranslatef(0, MODEL_SIZE, -10);
	// drawSlider();
	drawRain();
	drawCar(_textureId);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	srand((unsigned)time(0)); 

	glutCreateWindow("AppleFarm - Kijang");
	initRendering();
	timerController(0);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(mouseClickHandler);
	glutMotionFunc(processMouseActiveMotion);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}