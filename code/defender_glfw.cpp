#ifndef PSP

#include "defender.h"
#include "Level.h"


void drawRectangle(Vector2f position, float width, float height){
glPushMatrix();
	glTranslatef(position.x,position.y,0);
	glScalef(width,height,1);
	glBegin(GL_QUADS);      
   		glVertex3f(0.0, 0.0, 0.0);
    	glVertex3f(1.0, 0.0, 0.0);
    	glVertex3f(1.0, 1.0, 0.0);
    	glVertex3f(0.0, 1.0, 0.0);
    glEnd();
glPopMatrix();
}

void drawRectangle(Vector2f position, Vector2f size){
	drawRectangle(position,size.x,size.y);
}

void drawElipse(Vector2f position, float width, float height){
	glPushMatrix();
	const int segments = 100;
	glTranslatef(position.x + width / 2, position.y + height / 2,0);
	glScalef(width * 0.5,height * 0.5,1);
	glBegin(GL_TRIANGLE_FAN);
		for(int k = 0;k <= segments;k++){
			glVertex3f(cos(2*PI/segments * k),sin(k*2*PI/segments),0);
		}
	glEnd();
	glPopMatrix();
}

void Level::render() const {
	//draw ceiling
	glColor3ub(0, 10, 100);
	glBegin(GL_QUAD_STRIP);
	for (int k=0; k<level->ceilingLength; ++k) {
    	glVertex3f(level->ceiling[k].x, level->ceiling[k].y, 0.0);
    	glVertex3f(level->ceiling[k].x, 1.0, 0.0);
	}
	glEnd();
	
	 // draw ground
	glColor3ub(0, 100, 0);
	glBegin(GL_QUAD_STRIP);
	for (int k=0; k<level->groundLength; ++k) {
    	glVertex3f(level->ground[k].x, level->ground[k].y, 0.0);
    	glVertex3f(level->ground[k].x, 0.0, 0.0);
	}
	glEnd();
}
void Ship::render() const {
	glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(0.1, 0.08, 1);
		//glColor3ub(0,200, 0);
		//make ship flicker
		if(frame % 100 <= 50){
			glColor3ub(255,0, 0);
		}else{
			glColor3ub(0,255,0);
		}
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
		
		glColor3ub(139,0,139);
				glBegin(GL_LINES);
				glVertex3f(0.1,0.1,0.0);
				glVertex3f(0.1,0.9,0.0);
				
				glVertex3f(0.1,0.1,0.0);
				glVertex3f(0.9,0.1,0.0);
				
				glVertex3f(0.9,0.1,0.0);
				glVertex3f(0.9,0.9,0.0);
				
				glVertex3f(0.9,0.9,0.0);
				glVertex3f(0.1,0.9,0.0);
			glEnd();
	glPopMatrix();
}

void Bullet::render() const {
		glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(0.03, 0.03, 1);
		glColor3ub(255,255,0);			
		glBegin(GL_LINES);      
   			glVertex3f(0.0, 0.0, 0.0);
    		glVertex3f(1.0, 0.0, 0.0);
			glEnd();
		glPopMatrix();
}

void Bomb::render() const {
	glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(0.03, 0.03, 1);
		glColor3ub(255,255,0);			//draws enemy red
		drawElipse(Vector2f(0,0),1,1);
	glPopMatrix();
}


void Enemy::render() const {
	glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(0.1, 0.08, 1);
		glColor3ub(0,0, 255);
		
		//face
		drawElipse(Vector2f(0,0),0.8,1);
		
		//eyes
		//make eyes flicker
		if(frame % 50 <= 25){
			glColor3ub(255,0, 0);
		}else{
			glColor3ub(0,255,0);
		}
		
		drawElipse(Vector2f(0.15,0.7),0.1,0.05);
		drawElipse(Vector2f(0.55,0.7),0.1,0.05);
		drawRectangle(Vector2f(0.4,0.4),0.05,0.15);
		
		//bouding box
		glColor3ub(139,0,139);
				glBegin(GL_LINES);
				glVertex3f(1.0,0.0,0.0);
				glVertex3f(0.0,1.0,0.0);
				
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(1.0,0.0,0.0);
				
				glVertex3f(1.0,0.0,0.0);
				glVertex3f(1.0,1.0,0.0);
				
				glVertex3f(1.0,1.0,0.0);
				glVertex3f(0.0,1.0,0.0);
			glEnd();
	glPopMatrix();
}

void renderRadar(){
	glPushMatrix();
		glTranslatef(RADAR_X,RADAR_Y,0.0f);
		glScalef(RADAR_WIDTH,RADAR_HEIGHT,1);
		glColor3ub(0,0,0);
		//radar box
			glBegin(GL_QUADS);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(1.0,0.0,0.0);
				glVertex3f(1.0,1.0,0.0);
				glVertex3f(0.0,1.0,0.0);
			glEnd();
			glColor3ub(0,255,0);
		//radar guide lines for scaling
			glBegin(GL_LINES);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(1.0,1.0,0.0);
				
				glVertex3f(1.0,0.0,0.0);
				glVertex3f(0.0,1.0,0.0);
			glEnd();
		
		//scale level and draw it in radar
		glScalef(0.05,1,1);
			level->render();
	glPopMatrix();
}

void renderHealthBar(){
	glPushMatrix();
	glColor3ub(0,0,0);
	drawRectangle(Vector2f(0,0.0),HEALTH_BAR_WIDTH,0.05);

	glColor3ub(255,0, 0);
	drawRectangle(Vector2f(0,0.0),(HEALTH_BAR_WIDTH * ship.health) / 100,0.05);
	glPopMatrix();
}

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
	enemyFireTime = 0.0;
	return 0;		// success
}

int deinitGraphics() {
	glfwTerminate();
	return 0;		// success
}

void render() {
    // update frame timer
	previousTime = currentTime;
	currentTime = glfwGetTime();
	dt = currentTime - previousTime;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
    glPushMatrix();
    	glTranslatef(-level->position.x, 0, 0);	//move game objects relative to level movement
    	level->render();
    	ship.render();
    	for(int enemy = 0;enemy < level->enemyLength;++enemy)if(level->enemies[enemy].state != Entity::DEAD)level->enemies[enemy].render();
    	for(int bullet = 0;bullet < shipBullets.size();++bullet)shipBullets[bullet].render();
    	for(int bomb = 0; bomb < shipBombs.size();++bomb)shipBombs[bomb].render();
    	for(int bullet = 0;bullet < enemyBullets.size();++bullet)enemyBullets[bullet].render();
	glPopMatrix();
	renderRadar();
	renderHealthBar();
    glfwSwapBuffers(); 
}

void getInput() {
	//quits the game
	if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {
    	gameState = GAME_QUIT;
    	return;
	}
	
	//move ship commands
	ship.velocity = Vector2f::ZERO;
	if (glfwGetKey(GLFW_KEY_UP)) {
    	ship.velocity.y = 0.7;
	} else if (glfwGetKey(GLFW_KEY_DOWN)) {
    	ship.velocity.y = -0.7;
	}
	if (glfwGetKey(GLFW_KEY_LEFT)) {
    	ship.velocity.x = level->velocity.x-0.5;
	} else if (glfwGetKey(GLFW_KEY_RIGHT)) {
    	ship.velocity.x = level->velocity.x + 0.5;
	}
	
	//fire bullets from ship
	if(glfwGetKey(GLFW_KEY_SPACE) && previousBulletTime <= 0){
		Bullet & bullet = shipBullets.allocate();
		bullet.reset();
		bullet.position = (ship.position + Vector2f(1.0*0.1,0.5*0.08));	//front of ship
		bullet.velocity.x = 2;
		previousBulletTime = 0.1;
	}else{
		previousBulletTime -= dt;
	}
	
	//fire bombs from ship using 'E' as key press for firing bombs
	if(glfwGetKey(69) && previousBombTime <= 0){
		Bomb & bomb = shipBombs.allocate();
		bomb.reset();
		bomb.position = (ship.position + Vector2f(1.0*0.1,0.5*0.08));	//front of ship
		previousBombTime = 0.5;
	}else{
		previousBombTime -= dt;
	}
}
#endif

