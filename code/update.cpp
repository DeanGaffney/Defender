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
	checkShipCollisionWithLevel(true);		//check collision with ceiling
	checkShipCollisionWithLevel(false);		//check collision with ground
}

//function checks ceiling and ground collision based on boolean variable
void checkShipCollisionWithLevel(bool ceilingCheck){

	Vector2f currentPoint;
	Vector2f previousPoint;
	
	if(ceilingCheck){ //if true then check ceiling
		for (int k=1; k<level->ceilingLength; ++k) {
			//get the two points the ship is between
			if(ship.position.x < level->ceiling[k].x && ship.position.x > level->ceiling[k - 1].x){
					//set the two points
    			currentPoint.x = level->ceiling[k].x;
    			currentPoint.y = level->ceiling[k].y;			// current point

    			previousPoint.x = level->ceiling[k - 1].x;		//previous point
    			previousPoint.y = level->ceiling[k - 1].y;
    			break;		
    		}
		}
	}else{				//else check ground
		for (int k=1; k<level->groundLength; ++k) {
			//get the two points the ship is between
			if(ship.position.x < level->ground[k].x && ship.position.x > level->ground[k - 1].x){
					//set the two points
    			currentPoint.x = level->ground[k].x;
    			currentPoint.y = level->ground[k].y;			// current point

    			previousPoint.x = level->ground[k - 1].x;		//previous point
    			previousPoint.y = level->ground[k - 1].y;
    			break;		
    		}
		}
	}
	
	//get slope of line
	float slope = ((previousPoint.y - currentPoint.y) / (previousPoint.x - currentPoint.x));
	//cout << "Slope is :" << slope << endl;
	
	//check and see if point is above or below ground according to boolean variable.
	if(ceilingCheck && ship.position.y > (slope * ship.position.x) + (previousPoint.y - (slope * previousPoint.x))){
		//do something in here if we hit ceiling
		cout << "We are above the ceiling" << endl;
	}else if (!ceilingCheck && ship.position.y < (slope * ship.position.x) + (previousPoint.y - (slope * previousPoint.x))){
		//do something in here if we hit ground
		cout << "We are below the ground" << endl;
	}
}
void update() {
	level->update(dt);
	ship.update(dt);
	checkCollisions();
}
