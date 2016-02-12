#include "enemy.h"

// Enemy creation method
Enemy::Enemy(SDL_Renderer *renderer, string filePath){

	//get the path to the enemy's texture
	string enemyPath = filePath + "enemy.png";

	//Load the texture into a surface
	SDL_Surface *surface = IMG_Load(enemyPath.c_str());

	//create the texture from the passed Renderer and created surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the enemy's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;
	//"reset" the enemy
	Reset();

	//Initialize the direction vars for the enemy
	//no X movement, only Y movement (down
	xDir = 0;
	yDir = 1;

	// start with a random angle
	angle = rand() % (360);

	//calculate center pos by setting
	// ->x pos to half of width
	// ->y pos to half of height
	center.x = posRect.w / 2;
	center.y = posRect.h / 2;

}

//Enemy reset method
void Enemy::Reset(){

	//set random enemy speed
	speed = rand() % (5) + 1;
	speed *= 100;

	//generate random x position and set y back to the top of the screen
	posRect.x= rand() % (1024-posRect.w) + 1;
	posRect.y = 0 - posRect.h;

	//set the float position values of the texture for precision loss
	pos_X = posRect.x;
	pos_Y= posRect.y;

}

//Enemy update method
void Enemy::Update(float deltaTime){ // float delta

	//adjust position floats based on speed, direction ( 1 for down), and deltaTime
	pos_Y += (speed * yDir) * deltaTime;

	//update enemy position with code to account for precision loss
	posRect.y = (int) (pos_Y +0.5f);

	//check to see if the enemy is off the bottom of the screen
	// and reset if it is
	if(posRect.y > 768){

		//reset the enemy
		Reset();
	}

	///Update angleangle += .1;
}

//Enemy draw method
void Enemy::Draw(SDL_Renderer *renderer){

	SDL_RenderCopyEx(renderer, texture, NULL, &posRect, angle, &center, SDL_FLIP_NONE );
}

//enemy destruction
Enemy::~Enemy(){

}


