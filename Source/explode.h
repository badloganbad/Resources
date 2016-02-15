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

#include <string>
#include <iostream>
using namespace std;

class Explode
{
public:

	//boolean for the state of the explosion
	bool active;

	//explosion texture
	SDL_Texture *texture;

	//explosion rectangle for position (X,Y) and size (W,H)
	SDL_Rect posRect;

	//explosion rectangle for position (X,Y) and size (W,H)
	SDL_Rect drawRect;

	//width and height of each frame plus width and height of the entire image
	int frameWidth, frameHeight, textureWidth, textureHeight;

	//flaot values to track time until next fram of animatin
	float frameCounter;

	//Explode creation method. Requires the renderer, a path to the needed image, on x pos, and y pos
	Explode(SDL_Renderer *renderer, string filePath, float x, float y);

	//Explode update - requires deltaTime be passed
	void Update(float deltaTime);

	//Explode Draw - requires the renderer be passed
	void Draw(SDL_Renderer *renderer);

	// Explode reset
	void Reset();

	//Explode destruction method
	~Explode();
};