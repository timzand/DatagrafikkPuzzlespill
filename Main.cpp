/*
 * Puzzlegame.cpp
 *
 *  Created on: Nov 5, 2017
 *  Author: Tim Colin Sand, Fredrik Hov Nilsen, Ali Hamza
 */
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <Camera.h>

using namespace std;



Camera cam;

void processSpecialKeys(int key, int xx, int yy) {
	//Speed
	float fraction = 0.7f;
	cout << cam.lx << " " << cam.lz << endl;
	cout << cam.x << " " << cam.z << endl;

	switch (key) {
	case GLUT_KEY_LEFT:
		cam.angle -= 0.01f;
		cam.lx = sin(cam.angle);
		cam.lz = -cos(cam.angle);
		break;
	case GLUT_KEY_RIGHT:
		cam.angle += 0.01f;
		cam.lx = sin(cam.angle);
		cam.lz = -cos(cam.angle);
		break;
	case GLUT_KEY_UP:
		cam.x += cam.lx * fraction;
		cam.z += cam.lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		cam.x -= cam.lx * fraction;
		cam.z -= cam.lz * fraction;
		break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void displayMe(void) {
	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam.x, 1.0f, cam.z, cam.x + cam.lx, 1.0f, cam.z + cam.lz, 0.0f, 1.0f, 0.0f);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

	glutSwapBuffers();
}

float angle = 0.0;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

int main(int argc, char** argv) {
	cam = new Camera(0.0, 0.0f, -1.0f, 0.0f, 5.0f);
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Datagrafikk");

	// register callbacks
	glutDisplayFunc(displayMe);
	glutReshapeFunc(reshape);

	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

/*
 * Sources:
 * http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
 *
 *
 *
 */

