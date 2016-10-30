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
	checkShipCollisionWithLevel(true);		//check collision with data
	checkShipCollisionWithLevel(false);		//check collision with ground
}

//function checks data and ground collision based on boolean variable
void checkShipCollisionWithLevel(bool ceilingCheck){
	Vector2f previousPoint;
	Vector2f currentPoint;
	int dataLength = ceilingCheck ? level->ceilingLength : level->groundLength;

	Vector2f * data = ceilingCheck ? level->ceiling : level->ground;
	
	for(int k=1; k < dataLength; ++k) {
			//get the two points the ship is between
		if(ship.position.x < data[k].x && ship.position.x > data[k - 1].x){
				previousPoint.x = data[k-1].x;
				previousPoint.y = data[k-1].y;
				
				currentPoint.x = data[k].x;
				currentPoint.y = data[k].y;
    			break;		
    	}
	}
	
	//get slope of line
	float slope = ((previousPoint.y - currentPoint.y) / (previousPoint.x - currentPoint.x));
	//cout << "Slope is :" << slope << endl;
	
	//check and see if point is above or below ground according to boolean variable.
	if(ceilingCheck && ship.position.y > (slope * ship.position.x) + (previousPoint.y - (slope * previousPoint.x))){
		//do something in here if we hit data
		cout << "We are above the ceiling" << endl;
	}else if (!ceilingCheck && ship.position.y < (slope * ship.position.x) + (previousPoint.y - (slope * previousPoint.x))){
		//do something in here if we hit ground
		cout << "We are below the ground" << endl;
	}
	
	//checking branches
	
}
void update() {
	level->update(dt);
	ship.update(dt);
	checkCollisions();
}
