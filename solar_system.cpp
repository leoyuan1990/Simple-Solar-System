#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <random>

double data[9][3];      // array containing all planetary data except colours
double colours[9][3] = {{0.9, 0.6, 0.4}, {0.9, 0.9, 0.2}, {0.1, 1.0, 0.4}, {1.0, 0.0, 0.0},
	{0.6, 0.3, 0.1}, {0.9, 0.9, 0.5}, {0.2, 0.5, 1.0}, {0.0, 0.0, 0.6}, {0.5, 0.4, 0.3}};   // array containing all planetary colour arrays

const double DIST_MULT = 0.75;   // scaling factor to adjust for camera
const double SIZE_MULT = 0.08;   // scaling factor to adjust size of drawn planets
const double SUN_SIZE = 0.15;    // size of sun (NOT TO SCALE)
const double SUN_COLOUR[3] = {1.0, 1.0, 0.1};   // colour of sun (default yellow)
const double AST_BELT_DIST = 2.3;	// distance of closest layer of asteroid belt from sun relative to earth
const double AST_BELT_OFFSET = 0.05;	// offset distance for layers of asteroid belt
const int AST_BELT_NUM_LAYERS = 10;	// number of layers of asteroid belt
const int AST_BELT_DENSITY = 30;	// number of asteroids per layer
const double AST_SIZE = 0.1;		// radii of asteroids
const double AST_ORBITAL_SPEED = 19.0;	// asteroid orbital speed (random interpolation guess)
const double AST_COLOUR[3] = {0.5, 0.5, 0.5};	// colour of asteroids
const int PLUTO_INNER_DIST = 29.5;	// closest distance of Pluto to earth due to it's eliptical orbit (random extrapolation guess)
const double INNER_ZOOM = 0.0;  // preset quick zoom value for inner planets
const double OUTER_ZOOM = 60.0; // preset quick zoom value for outer planets
const double ZOOM_INCR = 1.0;	// how much fast the camera zooms in or out
const double MAX_ZOOM = 80.0;  	// the furthest possible camera zoom
// preset speeds for quick speed menu
const double SLOW = 0.1;
const double NORMAL = 0.5;
const double FAST = 1.5;

const double SPEED_INCR = 0.01;	// how fast the user can adjust the orbital speed
const double MAX_SPEED = 3.0;	// the fastest possible orbital speed

// window size and initial position (adjust based on screen resolution; for 1920x1080 use 800, 800, 600, 150)
const int MAX_X = 800;
const int MAX_Y = 800;
const int WINDOW_POS_X = 600;
const int WINDOW_POS_Y = 150;

const float DEG_TO_RAD = M_PI/180.0;

double angle = 0.0;
double position = 0.0;
double zoom = 30.0;                     // how far the camera is (initially)
double camPos[] = {5.0, 10.0, zoom};	// where the camera is
double speed = 0.5;                    	// how fast planets rotate with user input

void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
		case 'q':				// quit if user presses 'q'
			exit(0);
			break;

		case 'a':				// rotate counterclockwise if user press 'a'
            angle += speed;
            break;

        case 'd':				// rotate clockwise if user press 'a'
            angle -= speed;
            break;
			
		case 'w':				// zoom in if possible
			if (zoom > 0) {
				zoom -= ZOOM_INCR;
				gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0, 1 ,0);
				printf("ZOOMING IN! NEW ZOOM (initial is 30): %f\n", zoom);
			}
			break;

		case 's':				// zoom out if below furthest possible camera zoom
			if (zoom < MAX_ZOOM) {
				zoom += ZOOM_INCR;
				gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0, 1, 0);
				printf("ZOOMING OUT! NEW ZOOM (initial is 30): %f\n", zoom);
			}
			break;
			
		case 'z':				// slow down orbital speed if possible
			if (speed > 0) {
				speed -= SPEED_INCR;
				printf("DECREASING ORBITAL SPEED! NEW ORBITAL SPEED (normal is 0.5): %f\n", speed);
			}
			break;

		case 'c':				// zoom out if below fastest possible orbital speed
			if (speed < MAX_SPEED) {
				speed += SPEED_INCR;
				printf("INCREASING ORBITAL SPEED! NEW ORBITAL SPEED (normal is 0.5): %f\n", speed);
			}
			break;
	
	}
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0, 1, 0);

	// --- THE SUN ---
    glPushMatrix();
        glRotated(angle, 0, 1, 0);
        glScaled(SUN_SIZE, SUN_SIZE, SUN_SIZE);
        glColor3dv(SUN_COLOUR);
        glutSolidSphere(1.0, 40, 40);
    glPopMatrix();

    // --- THE PLANETS ---
    for (int i = 7; i >= 0; i--) {
        glPushMatrix();
			glRotated(angle * data[i][2], 0, 1, 0);
			glTranslated(data[i][1] * DIST_MULT, 0, 0);
			glScaled(data[i][0] * SIZE_MULT, data[i][0] * SIZE_MULT, data[i][0] * SIZE_MULT);
			glRotated(angle, 0, 1, 0);
			glColor3dv(colours[i]);
			glutSolidSphere(1.0, 40, 40);
        glPopMatrix();
    }
	
	// --- PLUTO ---	(NEED TO MAKE ORBIT ELLIPTICAL)
	glPushMatrix();
		glRotated(angle * data[8][2], 0, 1, 0);
		glTranslated(data[8][1] * DIST_MULT, 0, 0);
		glScaled(data[8][0] * SIZE_MULT, data[8][0] * SIZE_MULT, data[8][0] * SIZE_MULT);
		glRotated(angle, 0, 1, 0);
		glColor3dv(colours[8]);
		glutSolidSphere(1.0, 40, 40);
    glPopMatrix();
	
	// --- ASTEROID BELT ---
	for (int i = 0; i < AST_BELT_DENSITY; i++) {
		for (int j = 0; j < AST_BELT_NUM_LAYERS; j++) {
			glPushMatrix();
				glRotated(angle * AST_ORBITAL_SPEED + (360.0 * (i + double(rand())/double(RAND_MAX)))/AST_BELT_DENSITY, 0, 1, 0);
				glTranslated((AST_BELT_DIST + j * AST_BELT_OFFSET) * DIST_MULT, 0, 0);
				glScaled(AST_SIZE * SIZE_MULT, AST_SIZE * SIZE_MULT, AST_SIZE * SIZE_MULT);
				glRotated(angle, 0, 1, 0);
				glColor3dv(AST_COLOUR);
				glutSolidSphere(1.0, 40, 40);
			glPopMatrix();
		}
    }
	

	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y){}

void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0);
}

void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutTimerFunc(0, FPS, 0);
}

void mainMenuProc(int value){
	if (value == 3) {exit(0);}
}

void zoomMenuProc(int value){
    if (value == 1) {
        zoom = INNER_ZOOM;
        gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0,1,0);
		printf("ZOOMING ON INNER PLANETS! ZOOM: %f\n", zoom);
    } else if (value == 2) {
        zoom = OUTER_ZOOM;
        gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0,1,0);
		printf("ZOOMING ON OUTER PLANETS! ZOOM: %f\n", zoom);
    }
}

void speedMenuProc(int value){
    if (value == 1) {
        speed = SLOW;
		printf("SLOWING DOWN! NEW ORBITAL SPEED: %f\n", speed);
    } else if (value == 2) {
        speed = NORMAL;
		printf("RESETING SPEED! NEW ORBITAL SPEED: %f\n", speed);
    } else if (value == 3) {
        speed = FAST;
		printf("SPEEDING UP! NEW ORBITAL SPEED: %f\n", speed);
    }
}

void createOurMenu(){
	int zoomMenu_id = glutCreateMenu(zoomMenuProc);
	glutAddMenuEntry("Inner Planets", 1);
	glutAddMenuEntry("Outer Planets", 2);
	
	int speedMenu_id = glutCreateMenu(speedMenuProc);
	glutAddMenuEntry("Slow", 1);
	glutAddMenuEntry("Normal", 2);
	glutAddMenuEntry("Fast", 3);

	int main_id = glutCreateMenu(mainMenuProc);
	glutAddSubMenu("Quick Zoom", zoomMenu_id);
	glutAddSubMenu("Quick Speed", speedMenu_id);
	glutAddMenuEntry("Black Hole", 3);			// if you don't get this joke...
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    // planet radii relative to Earth
    data[0][0] = 0.38;  // Mercury
    data[1][0] = 0.95;  // Venus
    data[2][0] = 1.0;   // Earth
    data[3][0] = 0.53;  // Mars
    data[4][0] = 11.19; // Jupiter
    data[5][0] = 9.41;  // Saturn
    data[6][0] = 4.11;  // Uranus
    data[7][0] = 3.81;  // Neptune
	data[8][0] = 0.54;  // Pluto (dwarf planet, triple actual radius)

    // planet distances from sun relative to Earth
    data[0][1] = 0.39;
    data[1][1] = 0.72;
    data[2][1] = 1.0;
    data[3][1] = 1.52;
    data[4][1] = 5.20;
    data[5][1] = 9.54;
    data[6][1] = 19.18;
    data[7][1] = 30.06;
	data[8][1] = 39.53;

    // planet orbital speeds in km/s
    data[0][2] = 47.4;
    data[1][2] = 35.0;
    data[2][2] = 29.8;
    data[3][2] = 24.1;
    data[4][2] = 13.1;
    data[5][2] = 9.7;
    data[6][2] = 6.8;
    data[7][2] = 5.4;
	data[8][2] = 4.74;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(MAX_X, MAX_Y);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);

	glutCreateWindow("Solar System");

	callBackInit();

	init();

	createOurMenu();
	glutMainLoop();
	return 0;
}
