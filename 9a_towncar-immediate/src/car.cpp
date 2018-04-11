#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
# define PI 3.14159265358979323846  /* pi */

typedef struct {
	GLfloat x;
	GLfloat y;
} point;

double offset = 0;
double daytime = 0;
bool inc = true;

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 80; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for(i = 0; i <= triangleAmount;i++) { 
		glVertex2f(
	            x + (radius * cos(i *  twicePi / triangleAmount)), 
		    y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void drawCarSkeleton() {
	glBegin(GL_POLYGON);
	glVertex3f(-0.6,-0.5,0);
	glVertex3f(0.8,-0.5,0);
	glVertex3f(0.8,-0.2,0);
	glVertex3f(0.6,-0.2,0);
	glVertex3f(0.4,0,0);
	glVertex3f(-.4,0,0);
	glVertex3f(-.6,-0.2,0);
	glEnd();
}

point makePoint(GLfloat x, GLfloat y) {
	point p;
	p.x = x;
	p.y = y;
	return p;
}

void drawSquare(point p1, point p2, point p3, point p4) {
	glBegin(GL_POLYGON);
	glVertex3f(p1.x, p1.y, 0);
	glVertex3f(p2.x, p2.y, 0);
	glVertex3f(p3.x, p3.y, 0);
	glVertex3f(p4.x, p4.y, 0);
	glEnd();
}

void drawRoad() {
	glColor3f(0.6, 0.6, 0.6);
	drawSquare(makePoint(-1, -0.8), makePoint(-1, -0.4), makePoint(1, -0.4), makePoint(1, -0.8));
	glColor3f(1, 1, 1);
	
	double l1 = -1-offset;
	double r1 = -.6-offset;
	if(l1 < -2) {
		l1+=4;
		r1+=4;
	}
	
	double l2 = -.5-offset;
	double r2 = -.1-offset;
	if(l2 < -2) {
		l2+=4;
		r2+=4;
	}

	double l3 = 0-offset;
	double r3 = 0.4-offset;
	if(l3 < -2) {
		l3 +=4 ;
		r3 += 4;
	}

	double l4 = 0.5-offset;
	double r4 = 0.9-offset;
	if(l4 < -2) {
		l4 +=4 ;
		r4 += 4;
	}

	drawSquare(makePoint(l1, -0.55), makePoint(l1, -0.65), makePoint(r1, -0.65), makePoint(r1, -0.55));
	drawSquare(makePoint(l2, -0.55), makePoint(l2, -0.65), makePoint(r2, -0.65), makePoint(r2, -0.55));
	drawSquare(makePoint(l3, -0.55), makePoint(l3, -0.65), makePoint(r3, -0.65), makePoint(r3, -0.55));
	drawSquare(makePoint(l4, -0.55), makePoint(l4, -0.65), makePoint(r4, -0.65), makePoint(r4, -0.55));

	double l5 = 2-1-offset;
	double r5 = 2-.6-offset;
	if(l1 < -2) {
		l1+=4;
		r1+=4;
	}
	
	double l6 = 2-.5-offset;
	double r6 = 2-.1-offset;
	if(l2 < -2) {
		l2+=4;
		r2+=4;
	}

	double l7 = 2+0-offset;
	double r7 = 2+0.4-offset;
	if(l3 < -2) {
		l3 +=4 ;
		r3 += 4;
	}

	double l8 = 2+0.5-offset;
	double r8 = 2+0.9-offset;
	if(l4 < -2) {
		l4 +=4 ;
		r4 += 4;
	}

	drawSquare(makePoint(l5, -0.55), makePoint(l5, -0.65), makePoint(r5, -0.65), makePoint(r5, -0.55));
	drawSquare(makePoint(l6, -0.55), makePoint(l6, -0.65), makePoint(r6, -0.65), makePoint(r6, -0.55));
	drawSquare(makePoint(l7, -0.55), makePoint(l7, -0.65), makePoint(r7, -0.65), makePoint(r7, -0.55));
	drawSquare(makePoint(l8, -0.55), makePoint(l8, -0.65), makePoint(r8, -0.65), makePoint(r8, -0.55));
}

void drawBuilding() {	
	// Draw Building
	glColor3f(0.45329, 0.2588244, 0.258824);
	
	double l1 = -1-offset;
	double r1 = -.6-offset;
	if(l1 < -2) {
		l1+=4;
		r1+=4;
	}
	drawSquare(makePoint(l1, -0.4), makePoint(l1, 0.2), makePoint(r1, 0.2), makePoint(r1, -0.4));

	glColor3f(0.4, 0.2, 0.5);

	double l2 = -.6-offset;
	double r2 = -.2-offset;
	if(l2 < -2) {
		l2+=4;
		r2+=4;
	}
	drawSquare(makePoint(l2, -0.4), makePoint(l2, 0.6), makePoint(r2, 0.6), makePoint(r2, -0.4));

	glColor3f(0.7, 0.4, 0.5);

	double l3 = -.2-offset;
	double r3 = .2-offset;
	if(l3 < -2) {
		l3+=4;
		r3+=4;
	}
	glBegin(GL_POLYGON);
		glVertex2f(l3,-0.4	);
		glVertex2f(l3,0.6);
		glVertex2f((l3+r3)/2, 1);
		glVertex2f(r3,0.6);
		glVertex2f(r3,-.4);
	glEnd();

	glColor3f(0, 0.2, 0);

	double l4 = .2-offset;
	double r4 = 1-offset;
	if(l4 < -2) {
		l4+=4;
		r4+=4;
	}

	glBegin(GL_POLYGON);
		glVertex2f(l4,-0.4	);
		glVertex2f(l4,0.1);
		glVertex2f((l4+r4	)/2,-.2);
		glVertex2f(r4,0.1);
		glVertex2f(r4,-.4);
	glEnd();
	
	glColor3f(0.45329, 0.2588244, 0.258824);
	
	double l5 = 2-1-offset;
	double r5 = 2-.6-offset;
	if(l5 < -2) {
		l5+=4;
		r5+=4;
	}
	drawSquare(makePoint(l5, -0.4), makePoint(l5, 0.2), makePoint(r5, 0.2), makePoint(r5, -0.4));

	glColor3f(0.4, 0.2, 0.5);

	double l6 = 2-.6-offset;
	double r6 = 2-.2-offset;
	if(l6 < -2) {
		l6+=4;
		r6+=4;
	}
	drawSquare(makePoint(l6, -0.4), makePoint(l6, 0.6), makePoint(r6, 0.6), makePoint(r6, -0.4));


	glColor3f(0.7, 0.4, 0.5);

	double l7 = 2-.2-offset;
	double r7 = 2+.2-offset;
	if(l7 < -2) {
		l7+=4;
		r7+=4;
	}
	glBegin(GL_POLYGON);
		glVertex2f(l7,-0.4	);
		glVertex2f(l7,0.6);
		glVertex2f((l7+r7)/2, 1);
		glVertex2f(r7,0.6);
		glVertex2f(r7,-.4);
	glEnd();


	glColor3f(0, 0.2, 0);

	double l8 = 2+.2-offset;
	double r8 = 2+1-offset;
	if(l8 < -2) {
		l8+=4;
		r8+=4;
	}

	glBegin(GL_POLYGON);
		glVertex2f(l8,-0.4	);
		glVertex2f(l8,0.1);
		glVertex2f((l8+r8)/2,-.2);
		glVertex2f(r8,0.1);
		glVertex2f(r8,-.4);
	glEnd();

}

void DrawGLScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// printf("1\n");
	// Draw Background
	glColor3f(0.74902-daytime, 0.847059-daytime, 0.847059-daytime);
	drawSquare(makePoint(-1, 1), makePoint(-1, -1), makePoint(1, -1), makePoint(1, 1));
	drawBuilding();
	// Draw road
	drawRoad();

	// Draw car skeleton
	glColor3f(0, 0, 1);
	drawCarSkeleton();


	glColor3f(0.3, 0.3, 0.3);
	drawFilledCircle(-0.45, -.5, 0.1);
	drawFilledCircle(0.45, -.5, 0.1);
	glColor3f(0.9, 0.9, 0.9);

	drawFilledCircle(-0.45, -.5, 0.06);
	drawFilledCircle(0.45, -.5, 0.06);

	glBegin(GL_POLYGON);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(0.1,-0.2	);
		glVertex2f(0.55,-0.2);
		glVertex2f(0.4,-0.04);
		glVertex2f(0.1,-0.04);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(-0.08,-0.2	);
		glVertex2f(-0.45,-0.2);
		glVertex2f(-0.3,-0.04);
		glVertex2f(-0.08,-0.04);
	glEnd();

	glutSwapBuffers();
}

void timerController(int) {
	if(inc) {
		daytime += 0.001;
	} else {
		daytime -= 0.001;
	}

	if(inc && daytime > 0.8) {
		printf("here\n");
		inc = false;
	} 
	else if(!inc && daytime < 0) {
		printf("here2\n");
		inc = true;
	}
	offset += 0.01;
	if(offset > 2){
		offset = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(16, timerController, 0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("AppleFarm Town Car");
	glutDisplayFunc(&DrawGLScene);
	timerController(0);
	glutMainLoop();
	return 1;
}

