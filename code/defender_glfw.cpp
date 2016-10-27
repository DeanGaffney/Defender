#ifndef PSP

#include "defender.h"
#include "Level.h"

void Level::render() const {}
void Ship::render() const {

glPushMatrix();
	glScalef(0.1, 0.08, 1);
		glColor3ub(0,200, 0);
		glBegin(GL_QUADS);      
   			glVertex3f(0.0, 0.0, 0.0);
    			glVertex3f(1.0, 0.4, 0.0);
    			glVertex3f(1.0, 0.6, 0.0);
    			glVertex3f(0.0, 1.0, 0.0);

			glColor3ub(0, 0, 200);  

    			glVertex3f(0.0, 0.47, 0.0);
    			glVertex3f(1.1, 0.47, 0.0);
   			glVertex3f(1.1, 0.53, 0.0);
    			glVertex3f(0.0, 0.53, 0.0);
		glEnd();
	glPopMatrix();
}
void Bullet::render() const {}
void Bomb::render() const {}
void Enemy::render() const {}

int initGraphics() {
	
	glfwInit(); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if ( !glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0,0,0,0,0,0, GLFW_WINDOW) ) { 
		glfwTerminate(); 
		std::cerr <<"glfwOpenWindow failed" <<endl;
		return 1; 
	}
	
	glfwSetWindowPos(100, 100);
	glfwSetWindowTitle("Defender");

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0, ASPECT, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();							// reset the model view matrix

	// timing information
    startTime = currentTime = glfwGetTime();
	previousBulletTime = 0.0;

	return 0;		// success
	
}

int deinitGraphics() {
	glfwTerminate();
	return 0;		// success
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
	ship.render();
    glfwSwapBuffers(); 
}
void getInput() {}
#endif

