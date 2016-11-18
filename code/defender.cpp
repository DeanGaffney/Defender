// ===============================================
// @file   defender.h
// @author Dean Gaffney
// @student 20067423
// @practical defender
// @brief  Header file for PSP+GLFW(OpenGL) defender game
// ===============================================

#include "defender.h"

// state for main game loop
GameState gameState = GAME_INTRO;

// frame timing information
double startTime, currentTime, previousTime, dt;
double previousBulletTime, previousBombTime, enemyFireTime, shipDamageRecoveryTime;

Level * level;
Ship ship;
bool fire, fireBomb;
BulletPool shipBullets(1000);
BulletPool enemyBullets(1000);
BombPool shipBombs(1000);
float gravity = -9.8;

int main() {
	
	initGraphics();

	bool done = false;
	string levels [] = {"awkward","test","windy"};
	int currentLevel = 0;
	const int NUMBER_OF_LEVELS = 2;
	level = new Level(levels[currentLevel]);
	cout << *level;
	cout << *level;
	cout << *level;
	if (level != NULL) { delete level; level = NULL; }
	
	while (!done) {
		
		switch (gameState) {

			// state - GAME_INTRO
			// Display game intor screen etc
			// not implemented - just switches to state START_GAME 
			case(GAME_INTRO): {
				printf ("Game state changed from GAME_INTRO to GAME_START\n");
				gameState = GAME_START;
				break;
			}
			
			// state - GAME_START
			// initialse seting for start of game and start first level
			case(GAME_START): {
				printf ("Game state changed from GAME_START to LEVEL_START\n");
				gameState = LEVEL_START;
				break;
			}

			// state - LEVEL_START
			// Create level using data in file and start playing level
			case(LEVEL_START): {
				if (level != NULL) {  delete level; level = NULL; }
				level = new Level(levels[currentLevel]);
				cout << *level;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				gameState = LEVEL_PLAY;
				break;
			}

			// state - LEVEL_PLAY
			case(LEVEL_PLAY): {
				update();
				render();
				getInput();
				if (ship.state==Entity::DEAD)gameState = LEVEL_OVER;
				// want it for when player reaches end of level
				//if player loses life restart level
				//if no lives left then go to game over do not restart level
				
				//key press '2' for second level
				if(glfwGetKey(50)){
					gameState = LEVEL_START;
					currentLevel++;
				}
				//player reaches end of level,switch level and there are still levels to play
				else if(ship.position.x >= level->ground[level->groundLength-3].x && currentLevel + 1 != NUMBER_OF_LEVELS){
					gameState = LEVEL_START;
					currentLevel++;
					ship.resetLives();
				}else if(ship.position.x >= level->ground[level->groundLength-3].x && currentLevel + 1 == NUMBER_OF_LEVELS)gameState = GAME_OVER;
				break;
			}

			// state - LEVEL_OVER
			case(LEVEL_OVER): {
				gameState = GAME_OVER;
				break;
			}

			// state - GAME_OVER
			case(GAME_OVER): {
				render();
				getInput();
				break;
			}

			// state - GAME_QUIT
			case(GAME_QUIT): {
				done = true;
				break;
			}
			
			default: {
				printf ("Game state %d is not valid.\n", gameState);				
			}
		}
		
		done = done || (currentTime-startTime>40);
				
	}
	
	//checks if there are enemies remaining in the level
/*bool levelHasEnemiesRemaining(){
	for(int enemy = 0; enemy < enemyLength; enemy++){
		if(enemies[enemy].state == Entity::AWAKE)return true;
	}
	return false;
}

// level is over if level has no enemies remaining or ship reached end of level.
bool isLevelOver(Vector2f shipPosition){
	return (!levelHasEnemiesRemaining() || shipPosition.x >= ground[groundLength-1].x);
}*/

	// free remaining resources
//	if (level != NULL) delete level;

	return 0;
}


