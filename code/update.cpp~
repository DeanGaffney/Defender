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
   	velocity += Vector2f(0,-9.8*dt);
    position += velocity*dt;
}
void Enemy::update(float dt)  {
	position += dt* velocity;
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
	  	
	  	/*float topDistance = distancePointFromLevel(position + Vector2f(0.0,1.0*0.08),true);
		float bottomDistance = distancePointFromLevel(position,false);
		velocity.y = (topDistance > bottomDistance) ? 0.2 : -0.2;*/
		
		
		
    
    

	}else{
	//For Tracking enemies
		/*velocity.x = -0.2;
		//velocity.y = 0;
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
	  	*/
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
	
	//check all 4 corners of the ship for collision with the level
  	if((checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.1,1.0*0.08),true)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(0.0*0.0,0.0*0.08),false)) || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.6*0.08),true))  || 
  	  (checkPointCollisionWithLevel(ship.position + Vector2f(1.0*0.1,0.4*0.08),false))){
		//do things (lose life or stuff)
		cout << "ship collided at one of the corner points" << endl;
	}
	
	//check bullet collision with enemy, checks bullet impact point with the left hand side of enemy rectangle
	for(int bullet = 0; bullet < shipBullets.size();bullet++){
		for(int enemy = 0; enemy < level->enemyLength;enemy++){
			if(isBulletCollidingWithEnemy(shipBullets[bullet].position + Vector2f(1.0 * 0.03,0.0 * 0.03), level->enemies[enemy].position) && 
			level->enemies[enemy].state != Entity::DEAD){
				//cout << "Bullet hit enemy" << endl;
				shipBullets[bullet].state = Entity::DEAD;
				level->enemies[enemy].state = Entity::DEAD;
			}
		}
	}
	
	//check player collision with bombs
}

bool isBulletCollidingWithEnemy(Vector2f bulletImpactPoint,Vector2f enemyPosition){
	//see if the impact point is ahead of the bottom point  but within the height of the rectangle
	return ((bulletImpactPoint.x >= enemyPosition.x) && 
	(bulletImpactPoint.y >= enemyPosition.y && bulletImpactPoint.y <= enemyPosition.y + 1.0*0.08)) ? true : false;
}



//checks if gameObjects point is inside rectangle, I would consider making a rectangle class, or an array of vectors to pass into this as an argument
//could also pass in 2 vector lengths height and width representing rectangle??
bool isPointInsideRectangle(Vector2f point){ //ideally pass in gameObject.hitBox here 
//r is rectangle
//m is point thats being tested
// a starts at top left and goes clock wise and ends bottom left with d coordiante.
    /*Vector2f AB = Vector2f(r.A, r.B);
    Vector2f AM = Vector2f(r.A, point);
    Vector2f BC = Vector2f(r.B, r.C);
    Vector2f BM = Vector2f(r.B, point);
    Vector2f dotABAM = Vector2f(AB, AM);
    Vector2f dotABAB = Vector2f(AB, AB);
    Vector2f dotBCBM = Vector2f(BC, BM);
    Vector2f dotBCBC = Vector2f(BC, BC);
    return 0 <= dotABAM && dotABAM <= dotABAB && 0 <= dotBCBM && dotBCBM <= dotBCBC;*/
}


//http://www.learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-Detection
bool isPointInsideCircle(Vector2f point,Vector2f center, float radius){	//ideally pass in gameObject.hitBox here 
	//get center point of circle
	//calculate half-extents and and center of rectangle being tested against Vector2f
	//get the difference between the circle center and the rectangle center Vector2
	//clamp the difference between the -half extents and positive half extent
	//closest point on rectangle to circle is then clamped vector + rectangle center
	//difference = closest - circle center
	//return difference length <= radius (if true collision,false means no collision)
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
		if(!isInScreen(shipBullets[shipBullet]))cout << "Bullet left the screen" << endl;
		if(shipBullets[shipBullet].state == Entity::DEAD){			//if dead (hit enemy or out of screen then set to dead)
			shipBullets.free(shipBullet);
		}else if(shipBullets[shipBullet].state == Entity::AWAKE && !isInScreen(shipBullets[shipBullet])){
			shipBullets[shipBullet].state = Entity::DEAD;			//set to dead
		}
	}
	
	//TO DO : cull enemy bullets && bombs
	
	
	//cull enemies
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
