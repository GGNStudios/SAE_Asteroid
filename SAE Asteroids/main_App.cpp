#include <iostream>
#include <GL\glew.h>
#include "freeglut\include\GL\freeglut.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

# define M_PI           3.14159265358979323846

#include "Shader.h"
#include "Mesh.h"
#include "ObjLoader.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"
#include "Entity.h"
#include "Player.h"
#include "shot.h"

#define		RES_X		1024
#define		RES_Y		960

GLuint program;
void Display();

Camera cam;

ObjLoader object = ObjLoader("./res/models/cube.obj");
Shader s;

Transform transform;

//Entity battleCruiser;
Player battleCruiser;

std::vector <Shot> shots;
Shot shot;

Vertex v[] = { Vertex(glm::vec3(0.5,-0.5,0.0) , glm::vec2(1.0,0.0)),
				Vertex(glm::vec3(-0.5,-0.5,0.0), glm::vec2(0.0,0.0)),
				Vertex(glm::vec3(0.0,0.5,0.0)  , glm::vec2(0.5,1.0)),
				Vertex(glm::vec3(0.5,-0.5,0.0) , glm::vec2(1.0,0.0)),
				Vertex(glm::vec3(0.5, 0.5,0.0), glm::vec2(0.0,0.0)),
				Vertex(glm::vec3(0.0,0.5,0.0)  , glm::vec2(0.5,1.0)) };


Mesh model;
Mesh cube = Mesh();
Entity c;

GLuint vbo_coords, vbo_triangle_colors, vbo_triangle;

double counter = 0;


void GL_Init_Frame(void) {
	glBegin(GL_MODELVIEW);
	glLoadIdentity();

	s.Update(transform, cam);
	Display();

	battleCruiser.PlayerMovement();
	
	battleCruiser.MeshRasterization(cam);

	for (unsigned int i = 0; i < shots.size(); i++) {
		shots[i].ShotUpdate(cam);
		if (shots[i].OutOfBounds())
			shots.erase(shots.begin() + i);
	}

	battleCruiser.UpdateBoundingBox(battleCruiser.transform.GetRot().z);
	battleCruiser.Update();
	battleCruiser.transform.GetScale() = glm::vec3(0.2, 0.2, 0.2);
	c.EntityMovementR(glm::vec3(counter / 3, counter / 2, counter));

	glutSwapBuffers();
	glutPostRedisplay();
	counter += 0.01;
}

void ClearScreen() {
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display()
{
	ClearScreen();
	//model.Draw();
}

void resize(int w, int h)
{
	ClearScreen();
	double ratio = w / (double)h;

	glViewport(0, 0, w, h); //NEW
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -100, 1000);
	//glFrustum(-10.0, 10.0, -10.0, 10.0, -100.0, 1000.0);
	gluLookAt(0, 0, -100, 0, 0, 0, 0, 1, 0);
	gluPerspective(80, ratio, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		battleCruiser.IsMovingForward(false);
		break;
	case 's':
		battleCruiser.IsMovingBackward(false);
		break;
	case 'd':
		battleCruiser.IsMovingRightward(false);
		break;
	case 'a':
		battleCruiser.IsMovingLeftward(false);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		battleCruiser.IsMovingForward(true);
		break;
	case 's':
		battleCruiser.IsMovingBackward(true);
		break;
	case 'd':
		battleCruiser.IsMovingRightward(true);
		break;
	case 'a':
		battleCruiser.IsMovingLeftward(true);
		break;
	default:
		break;
	}
	//glutPostRedisplay();
}

void mousePassive( int x, int y) {
	glm::vec2 realPosition((float)((x) - (RES_X/2)) * 2 * 3 / RES_X, (float)((y) - (RES_Y/2)) * 2 * 3 / RES_Y);

	float angle = (float) atan2(- realPosition.y - battleCruiser.transform.GetPos().y, realPosition.x - battleCruiser.transform.GetPos().x) - M_PI/2;

	battleCruiser.EntityMovementR(glm::vec3(-M_PI / 2, battleCruiser.GetVelocity(), angle));

}

void mouse(int key, int state, int x, int y) 
{
	glm::vec2 realPosition((float)((x)-(RES_X / 2)) * 2 * 3 / RES_X, (float)((y)-(RES_Y / 2)) * 2 * 3 / RES_Y);

	float angle = (float)atan2(realPosition.x - battleCruiser.transform.GetPos().x ,-realPosition.y - battleCruiser.transform.GetPos().y) - M_PI / 2;

	if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Shot *s = new Shot();
		*s = shot;
		s->transform.GetPos() = battleCruiser.transform.GetPos();
		s->transform.GetRot() = battleCruiser.transform.GetRot();
		s->transform.GetRot().z += M_PI / 2;
		shots.push_back(*s);
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(RES_X, RES_Y);               // window size
	glutInitWindowPosition(300, 50);               // distance from the top-left screen
	glutCreateWindow("SAE Asteroids");				// message displayed on top bar window

	GLint glewInitRes = glewInit();

	//Init Camera
	//Camera camera(glm::vec3(0,0,-3), 70.0f, RES_X/(double)RES_Y,0.01f,1000f);

	if (glewInitRes != GLEW_OK)
	{
		std::cerr << "Error: Cannot Initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	ClearScreen();
	glEnable(GL_DEPTH_TEST);
	
	Vertex cube = Vertex(glm::vec3(0,0,0));
	c = Entity("./res/models/cube.obj", "./res/shaders/basicShader", program, 2);
	c.MeshDiffuseTextureLoader("./res/textures/body-dif_2.jpg");

	Player temp("./res/models/battle.obj", "./res/shaders/basicShader", program, 1);
	battleCruiser = temp;
	battleCruiser.MeshDiffuseTextureLoader("./res/textures/body-dif.jpg");

	Shot *tempShot = new Shot(vec3(0,0,0),vec3(0,0,0), vec3(0.1,0.1,0.1),false,"./res/models/cube.obj","./res/shaders/basicShader",program, 3);
	shot = *tempShot;

	Camera *tempCam = new Camera(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	cam = *tempCam;
	cam.view = glm::lookAt(glm::vec3(0.0, 0.0f,2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	cam.projection = glm::perspective(45.0f, (GLfloat)RES_X / (GLfloat)RES_Y,0.1f, 100.0f);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousePassive);
	glutDisplayFunc(GL_Init_Frame);
	glutMainLoop();
	return 0;
}
