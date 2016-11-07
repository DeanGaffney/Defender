// ===============================================
// @file   update.cpp
// @author Dean Gaffney
// @practical update
// @brief  Update file for updating game logic.
// ===============================================

#include "defender.h"
#include "math.h"

void Ship::update(float dt)  {
	//update position
	position += dt * velocity;
	
	//restrict ship movement on the x and y axis between the screen
	position.x = clamp(position.x, level->position.x, level->position.x + ASPECT*0.66);
	position.y = clamp(position.y, level->position.y, level->position.y + ASPECT*0.52);
}


void Bullet::update(float dt)  {
	position += dt * velocity;
}
void Bomb::update(float dt)  {}
void Enemy::update(float dt)  {
	//cout << "enemies are being updated" << endl;
}

void checkCollisions(){
	
	//check all 4 corners of the ship for collision with the level
  	if((checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.1,1.0*0.08),true)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.0,0.0*0.08),false)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.6*0.08),true))  || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.4*0.08),false))){
		//do things (lose life or stuff)
		cout << "ship collided at one of the corner points" << endl;
	}
 
}

//checks distance a point is from a level
float distancePointFromLevel(const Vector2f point, bool ceilingCheck){
	Vector2f previousPoint;
	Vector2f currentPoint;
	
	int dataLength = ceilingCheck ? level->ceilingLength : level->groundLength;

	Vector2f * data = ceilingCheck ? level->ceiling : level->ground;
	
	int k = 1;
	for(k=1; k < dataLength; ++k){if(point.x > data[k-1].x && data[k].x > point.x)break;}	//get the two points the ship is between	
	
	//set up points the point is between
	previousPoint = data[k-1];
	currentPoint = data[k];
	
	//cout << "Previous point : " << previousPoint.x << "," << previousPoint.y << endl;
	//cout << "Current point : " << currentPoint.x << "," << currentPoint.y << endl;
	//get slope of line
	float slope = ((previousPoint.y - currentPoint.y) / (previousPoint.x - currentPoint.x));
	//cout << "Slope is :" << slope << endl;
	//cout << "Distance is : " << ((slope * point.x) + (previousPoint.y - (slope * previousPoint.x))) << endl;
	//return distance
	return ((slope * point.x) + (previousPoint.y - (slope * previousPoint.x)));
}

//function checks data and ground collision based on boolean variable
bool checkPointCollisionWithLevel(const Vector2f point, bool ceilingCheck){
   float distance = distancePointFromLevel(point, ceilingCheck);
   return (ceilingCheck && point.y >= distance) ? true : (!ceilingCheck && point.y <= distance) ? true : false; 
}

void cullObjects(){
	//cull ship bullets
	for(int shipBullet = 0; shipBullet < shipBullets.size(); shipBullet++){
		if(shipBullets[shipBullet].state == Entity::DEAD){			//if dead (hit enemy or out of screen then set to dead)
			shipBullets.free(shipBullet);
		}
	}
}

void update() {
	level->update(dt);
	ship.update(dt);
	for(int enemy = 0; enemy < level->enemyLength;enemy++){
		//if((int)level->enemies[enemy].position.x == (int)ship.position.x)cout << "ship and enemy are on the same x axis. Enemy number:" << enemy << endl;
		//cout << enemy << endl;
	}
	cout << "Is ship bullet pool empty?" << shipBullets.isEmpty() << endl;
	for(int bullet = 0; bullet < shipBullets.size(); bullet++)cout << shipBullets[bullet].position << "Bullet pool for ship is empty?:" << shipBullets.isEmpty() << endl;
	checkCollisions();
	// cullObjects();
}
