
#include "defender.h"
#include "Level.h"

void Level::render() const {}
void Ship::render() const {}
void Bullet::render() const {}
void Bomb::render() const {}
void Enemy::render() const {}

void Ship::update(float dt)  {}
void Bullet::update(float dt)  {}
void Bomb::update(float dt)  {}
void Enemy::update(float dt)  {}

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

    glfwSwapBuffers(); 
}
void update() {}
void getInput() {}


