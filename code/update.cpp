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
	
	//restrict movement
	position.x = clamp(position.x, level->position.x, level->position.x + ASPECT*0.66);
	
}


void Bullet::update(float dt)  {}
void Bomb::update(float dt)  {}
void Enemy::update(float dt)  {}

void checkCollisions(){
				//glVertex3f(0.0, 0.0, 0.0); bottom left of ship
    			//glVertex3f(1.0, 0.4, 0.0);
    			//glVertex3f(1.0, 0.6, 0.0);
    			//glVertex3f(0.0, 1.0, 0.0);
	if(checkPointCollisionWithLevel(Vector2f(ship.position.x,ship.position.y),true))cout << "ship collided with ceiling." << endl;
	if(checkPointCollisionWithLevel(Vector2f(ship.position.x,ship.position.y),false))cout << "ship collided with ground,bottom left corner" << endl;//check collision with ground
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

void update() {
	level->update(dt);
	ship.update(dt);
	checkCollisions();
}
