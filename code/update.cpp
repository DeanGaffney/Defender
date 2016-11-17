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
	
	//automate movement
	float topDistance = distancePointFromLevel(position + Vector2f(0.0,1.0*0.08),true);
	float bottomDistance = distancePointFromLevel(position, false);
	velocity.y = (topDistance > bottomDistance) ? 0.2 : -0.2;
}


void Bullet::update(float dt)  {
	//update position
	position += dt * velocity;
}

void Bomb::update(float dt)  {
//motion for shooting bombs from enemies
   velocity += Vector2f(0,-9.8 * dt);
   position += velocity*dt;
}


void Enemy::update(float dt)  {
	position += dt* velocity;
	
	//update bounding box position
	maxPoints = Vector2f(position.x + (1.0 * 0.1),position.y + (1.0 * 0.08));
	minPoints = Vector2f(position.x,position.y);
	
	//choose behaviour based on state
	if(type == Enemy::SIMPLE){
		//For Tracking enemies
		velocity.x = -0.2;

		//moves up and down and detects when about to collide with level
  		if((checkPointCollisionWithLevel(position + Vector2f(0.2,0.1),true))){		//check collision in front and above for ceiling
  	  	 //velocity.y = (!checkPointCollisionWithLevel(position + Vector2f(0.0,0.1),false)) ? -0.3 : 0.0; //if theres space under position move down, else dont
  	  	 	if(!checkPointCollisionWithLevel(position + Vector2f(0.0,0.1),false))velocity.y = -0.3;
  		}
  	  	else if((checkPointCollisionWithLevel(position + Vector2f(0.2,-0.1),false))){ //check collision in front and below for ground
  	  	 //velocity.y = (!checkPointCollisionWithLevel(position + Vector2f(0.0,0.1),true)) ? 0.3 : 0.0; //if space under position move down,else dont
  	  	 	if(!checkPointCollisionWithLevel(position + Vector2f(0.0,0.1),true))velocity.y = 0.3;
  	  	}else{
		 	velocity.y = 0.0;		//if ship isnt going to collide then move as normal with no y velocity, probably change this to chase player
	  	}
	  	
	  	/*
	  		if(randomFLoat < chance){
	  			float theta = randFloat (0,2*M_PI);
	  			float r = randFloat (0.5,1);
	  			velocity.set = (r cos(theta),r sin(theta));
	  		}
	  		
	  		//update position
	  		
	  		//clamp position y between max and min points in level
	  	*/
	}else{
	//For Tracking enemies
	  	
	  	//get height of rectangle
		//get distance from ceiling
		//get bottom point of rectangle and get distance
		//compare distances
		// move accordingly
		
		/*float topDistance = distancePointFromLevel(position + Vector2f(0.0,1.0*0.08),true);
		float bottomDistance = distancePointFromLevel(position,false);
		velocity.y = (topDistance > bottomDistance) ? 0.2 : -0.2;*/
	}
}
	
	

//make sure game object is within width of screen
bool isInScreen(Entity &gameObject){
	return gameObject.position.x < level->position.x + ASPECT;
}

void checkCollisions(){
	
	//check all 4 corners of the player ship for collision with the level
  	if((checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.1,1.0*0.08),true)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.0,0.0*0.08),false)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.6*0.08),true))  || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.4*0.08),false))){
		//do things (lose life or stuff)
		cout << "ship collided at one of the corner points" << endl;
	}
	
	//check player collision with enemies
	for(int enemy = 0; enemy < level->enemyLength; enemy++){
		if(isPointInsideRectangle(ship.position + Vector2f(0.0*0.1,1.0*0.08),level->enemies[enemy].maxPoints,level->enemies[enemy].minPoints) ||
			isPointInsideRectangle(ship.position + Vector2f(0.0*0.1,1.0*0.08),level->enemies[enemy].maxPoints,level->enemies[enemy].minPoints) ||
			isPointInsideRectangle(ship.position + Vector2f(0.0*0.1,1.0*0.08),level->enemies[enemy].maxPoints,level->enemies[enemy].minPoints) ||
			isPointInsideRectangle(ship.position + Vector2f(0.0*0.1,1.0*0.08),level->enemies[enemy].maxPoints,level->enemies[enemy].minPoints)){
				cout << "Player hit enemy" << endl;
				//do something kill player or lose life
		}
	}
	
	//check player bullets collision with enemy
	for(int bullet = 0; bullet < shipBullets.size();bullet++){
		for(int enemy = 0; enemy < level->enemyLength;enemy++){
			//send in impact point of bullet and enemy rectangle
			if(isPointInsideRectangle(shipBullets[bullet].position + Vector2f(1.0 * 0.03,0.0), level->enemies[enemy].maxPoints, level->enemies[enemy].minPoints) && 
				level->enemies[enemy].state != Entity::DEAD){
					cout << "Bullet hit enemy" << endl;
					shipBullets[bullet].state = Entity::DEAD;
					level->enemies[enemy].state = Entity::DEAD;
			}
		}
	}
	
	//check enemy collision with bombs
	for(int bomb = 0; bomb < shipBombs.size();bomb++){
		for(int enemy = 0; enemy < level->enemyLength;enemy++){
				//glScalef(0.03, 0.03, 1);
				//bomb goes at an upward arc so it will never hit left side or top
				//only check 2 bottom corners and top right corner of the bomb for impact
			if(isPointInsideRectangle(shipBombs[bomb].position,level->enemies[enemy].maxPoints, level->enemies[enemy].minPoints) ||	//bottom left corner
			   isPointInsideRectangle(shipBombs[bomb].position,level->enemies[enemy].maxPoints, level->enemies[enemy].minPoints) ||	//bottom right corner
			   isPointInsideRectangle(shipBombs[bomb].position,level->enemies[enemy].maxPoints, level->enemies[enemy].minPoints) && 
			   level->enemies[enemy].state != Entity::DEAD){	//top right corner
			   		cout << "Bomb hit enemy" << endl;
			   		shipBombs[bomb].state = Entity::DEAD;
			   		level->enemies[enemy].state = Entity::DEAD;
			   }	
		}
	}
}

/*
	Function takes a point to test if it's in rectangle
	maxPoint is a vector used to hold maximum X value and maximum Y value of rectangle
	minPoint holds min X value and min y Value of rectangle
	returns true if point is inside, false otherwise
*/
bool isPointInsideRectangle(Vector2f point,Vector2f maxPoint, Vector2f minPoint){
	return (point.x > minPoint.x && point.x < maxPoint.x && point.y > minPoint.y && point.y < maxPoint.y);
}

//http://www.learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-Detection
bool isPointInsideCircle(Vector2f point,Vector2f center, float radius){	//ideally pass in gameObject.hitBox here 
	return(point-center).lengthSqr() <= radius*radius;
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
	for(int shipBullet = shipBullets.size();--shipBullet >= 0;){
		if(!isInScreen(shipBullets[shipBullet])){
			cout << "Bullet left the screen" << endl;
			shipBullets[shipBullet].state = Entity::DEAD;
			shipBullets.free(shipBullet);
		}
	}
	
	//cull ship bombs
	for(int shipBomb = shipBombs.size();--shipBomb >= 0;){
		if(!isInScreen(shipBombs[shipBomb])){
			cout << "Bomb left the screen" << endl;
			shipBombs[shipBomb].state = Entity::DEAD;
			shipBombs.free(shipBomb);
		}
	}
}

void update() {
	level->update(dt);
	ship.update(dt);
	for(int enemy = 0; enemy < level->enemyLength;enemy++)level->enemies[enemy].update(dt);
	//cout << "Is ship bullet pool empty?" << shipBullets.isEmpty() << endl;
	for(int bullet = 0; bullet < shipBullets.size(); bullet++)shipBullets[bullet].update(dt);
	for(int bomb = 0; bomb < shipBombs.size(); bomb++)shipBombs[bomb].update(dt);
	checkCollisions();
	//cout << "Bullet pool size " << shipBullets.size() << endl;
	cullObjects();
}
