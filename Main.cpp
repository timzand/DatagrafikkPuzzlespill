/*
 *	Puzzlegame.cpp
 *
 *  Created on: Nov 5, 2017
 *  Author: Tim Colin Sand, Fredrik Hov Nilsen, Ali Hamza
 *
 */

#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

class Camera {
public:
	float angle, lx, lz, x, z;
	Camera();
	Camera(float angle, float lx, float lz, float x, float z) {
		this->angle = angle;
		this->lx = lx;
		this->lz = lz;
		this->x = x;
		this->z = z;
	}
	~Camera();
};

Camera *cam = new Camera(0.0f, 0.0f, -1.0f, 0.0f, 5.0f);

void processSpecialKeys(int key, int xx, int yy) {
	//Speed
	float fraction = 0.3f;
	cout << cam->lx << " " << cam->lz << endl;
	cout << cam->x << " " << cam->z << endl;

	if (key == GLUT_KEY_LEFT) {
		cam->angle -= 0.03f;
		cam->lx = sin(cam->angle);
		cam->lz = -cos(cam->angle);
	}
	if (key == GLUT_KEY_RIGHT) {
		cam->angle += 0.03f;
		cam->lx = sin(cam->angle);
		cam->lz = -cos(cam->angle);
	}
	if (key == GLUT_KEY_UP) {
		cam->x += cam->lx * fraction;
		cam->z += cam->lz * fraction;

	}
	if (key == GLUT_KEY_DOWN) {
		cam->x -= cam->lx * fraction;
		cam->z -= cam->lz * fraction;
	}

	glutPostRedisplay();
}

void drawCube() {

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

void displayMe() {
	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam->x, 1.0f, cam->z, cam->x + cam->lx, 1.0f, cam->z + cam->lz,
			0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f , -2.0);
	glBegin(GL_QUADS);
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube

	glutSwapBuffers();
}

float angle = 0.0;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
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

