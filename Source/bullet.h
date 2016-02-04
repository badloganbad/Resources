//needed includes for cross platform development
#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#endif

#if defined (__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

// needed includes
#include <string>
#include <iostream>
using namespace std;

class Bullet
{
public:
	
	//bool for the state of the bullet
	bool active;

	//bullet texture
	SDL_Texture *texture;

	//Bullet rectangle for position (X,Y) and size (W,H)
	SDL_Rect posRect;

	//movement direction values
	float xDir, yDir;

	//bullet speed
	float speed;

	//bullet float positions to prevent precision loss
	float pos_X, pos_Y;

	// bullet creation method requires the renderer, a path to the needed image, an X position, a Y position
	Bullet(SDL_Renderer *renderer, string filePath, float x, float y);

	//bullet update - requires deltaTime be passed
	void Update(float deltaTime);

	//bullet draw - requires renderer be passed
	void Draw(SDL_Renderer *renderer);

	//bullet deconstructer
	~Bullet();

};