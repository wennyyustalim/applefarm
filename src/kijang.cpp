/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Putting It All Together" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;

const float BOX_SIZE = 5.0f; //The length of each side of the cube
float angleX = 0;            //The rotation of the box
float angleY = 0;
GLuint _textureId;           //The OpenGL id of the texture

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

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
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
	
	glRotatef(-angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(-angleY, 1.0f, 0.0f, 0.0f);

	glColor3f(1,0,0);
	//Front Face
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2,-BOX_SIZE/2,BOX_SIZE);
	glVertex3f(BOX_SIZE/2,-BOX_SIZE/2,BOX_SIZE);
	glVertex3f(BOX_SIZE/2,-BOX_SIZE/5,BOX_SIZE);
	glVertex3f(-BOX_SIZE/2,-BOX_SIZE/5,BOX_SIZE);
	glEnd();

	glColor3f(1,1,0);
	//Kap Mobil
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/5,BOX_SIZE); 
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/5,BOX_SIZE); 
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glEnd();


	//KacaDepan Mobil
	glColor3f(1,0.5,0);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, 0,BOX_SIZE/3); 
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glEnd();

	//Atap Mobil
	glColor3f(0.5,1,0);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2,BOX_SIZE/5);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glEnd();

	//KacaBelakangMobil
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE*1.2);
	glVertex3f(-BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glEnd();

	//Bagasi Mobil
	glColor3f(0.5,0,0.8);
	glBegin(GL_POLYGON);
	glVertex3f(-BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, 0, -BOX_SIZE*1.4);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glEnd();

	//Kolong Mobil
	glColor3f(0.8,0,0.8);
	glBegin(GL_POLYGON);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE*1.4);
	glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE);
	glEnd();


	//Sisi Kanan Mobil
	glColor3f(0.8,1,0.8);
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

	glColor3f(0.2,0,0.2);
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
	// glutTimerFunc(25wwupdate, 0);
	
	glutMainLoop();
	return 0;
}









