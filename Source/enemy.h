#if defined (_WIN32) || (_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#endif

#if defined (__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>

class Enemy{

public:

	//boolean for the state of the enemy
	bool active;
	// enemy texture
	SDL_Texture * texture;

	// Enemy rectangle for position (X,Y) and size (W,H)
	SDL_Rect posRect;

	//movement direct values
	float xDir, yDir;

	//Enemy speed
	float speed;

	//enemy float positions to prevent precision loss
	float pos_X, pos_Y;

	//enemy angle
	float angle;

	//point for the center of the object. used for rotation
	SDL_Point center;

	//Enemy creation mehtod. Requires the renderer, a path to the needed image
	Enemy(SDL_Renderer *renderer, string filePath);

	//ENemy update - requires deltaTime be passed
	void Update(float deltaTime);

	//EnemyDraw - requires renderer be passed
	void Draw(SDL_Renderer * renderer);

	//Enemy Reset
	void Reset();

	//Enemy destruction method
	~Enemy();

};
