#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

double data[8][3];      // array containing all planetary data except colours
double colours[8][3] = {{0.9, 0.6, 0.3}, {0.9, 0.9, 0.2}, {0.1, 1.0, 0.4}, {1.0, 0.0, 0.0},
    {1.0, 0.3, 0.1}, {0.9, 0.9, 0.5}, {0.2, 0.2, 1.0}, {0.0, 0.0, 0.6}};   // array containing all planetary colour arrays

const double DIST_MULT = 1.0;   // scaling factor to adjust for camera
const double SIZE_MULT = 0.1;   // scaling factor to adjust size of drawn planets
const double SUN_SIZE = 0.2;    // size of sun (NOT TO SCALE)
const double SUN_COLOUR[3] = {1.0, 1.0, 0.1};   // colour of sun (default yellow)
const double INNER_ZOOM = 0.0;  // preset quick zoom value for inner planets
const double OUTER_ZOOM = 68.0; // preset quick zoom value for outer planets
const double MAX_ZOOM = 100.0;  // the furthest possible camera zoom

double angle = 0.0;
double position = 0.0;
double zoom = 30.0;                     // how far the camera is (initially)
double camPos[] = {5.0, 10.0, zoom};	// where the camera is
double speed = 0.25;                    // how fast planets rotate with user input

void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
		case 'q':
			exit(0);
			break;

		case 'a':
            angle += speed;
            break;

        case 'd':
            angle -= speed;
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
        glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // --- THE PLANETS ---
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotated(angle * data[i][2], 0, 1, 0);
        glTranslated(data[i][1] * DIST_MULT, 0, 0);
        glScaled(data[i][0] * SIZE_MULT, data[i][0] * SIZE_MULT, data[i][0] * SIZE_MULT);
        glRotated(angle, 0, 1, 0);
        glColor3dv(colours[i]);
        glutSolidSphere(1.0, 20, 20);
        glPopMatrix();
    }

	//switch our buffers for a smooth animation
	glutSwapBuffers();
}

void special(int key, int x, int y){
	switch (key){
	case GLUT_KEY_UP:
	    if (zoom > 0) {
            zoom--;
            gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0, 1 ,0);
            printf("ZOOMING IN: %f\n", zoom);
	    }
		break;

	case GLUT_KEY_DOWN:
	    if (zoom < MAX_ZOOM) {
            zoom++;
            gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0, 1, 0);
            printf("ZOOMING OUT: %f\n", zoom);
	    }
		break;
	}
}

void mouse(int btn, int state, int x, int y){
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	gluPerspective(45, (double)((w+0.0f)/h), 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}

void callBackInit(){
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	//glutReshapeFunc(reshape);
	glutTimerFunc(0, FPS, 0);
}


void menuProc(int value){
	if (value == 2) {exit(0);}
}

//could use a seperate menu processor for submenu!
void zoomMenuProc(int value){
    if (value == 1) {
        zoom = INNER_ZOOM;
        gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0,1,0);
    } else if (value == 2) {
        zoom = OUTER_ZOOM;
        gluLookAt(camPos[0], camPos[1], zoom, 0, 0, 0, 0,1,0);
    }
}

void createOurMenu(){
	int subMenu_id = glutCreateMenu(zoomMenuProc);
	glutAddMenuEntry("Inner Planets", 1);
	glutAddMenuEntry("Outer Planets", 2);

	int main_id = glutCreateMenu(menuProc);
	glutAddSubMenu("Quick Zoom", subMenu_id);
	glutAddMenuEntry("Black Hole (quit)", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* main function - program entry point */
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

    // planet distances from sun relative to Earth
    data[0][1] = 0.39;
    data[1][1] = 0.72;
    data[2][1] = 1.0;
    data[3][1] = 1.52;
    data[4][1] = 5.20;
    data[5][1] = 9.54;
    data[6][1] = 19.18;
    data[7][1] = 30.06;

    // planet orbital velocities in km/s
    data[0][2] = 47.4;
    data[1][2] = 35.0;
    data[2][2] = 29.8;
    data[3][2] = 24.1;
    data[4][2] = 13.1;
    data[5][2] = 9.7;
    data[6][2] = 6.8;
    data[7][2] = 5.4;

    /* planet colours
    colours[0] = {0.9, 0.6, 0.3};
    colours[1] = {1.0, 1.0, 0.5};
    colours[2] = {0.2, 1.0, 0.2};
    colours[3] = {1.0, 0.0, 0.0};*/

	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(400, 400);
	glutInitWindowPosition(250, 50);

	glutCreateWindow("Solar System");	//creates the window

	callBackInit();

	init();

	createOurMenu();
	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
