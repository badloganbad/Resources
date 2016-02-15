#include "explode.h"

//Explode creation method
Explode::Explode(SDL_Renderer *renderer, string filePath, float x, float y)
{
	//Set the explosion inital state
	active = false;

	//get the directory to the explosion graphic
	string explodePath = filePath + "explode.png";

	//init frame counter
	frameCounter = 0.0f;

	//load the texture into a surface
	SDL_Surface *surface = IMG_Load(explodePath.c_str());

	//create the texture from the passed Renderer and created surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the bullet's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	//getting the width and height of the entire image
	textureWidth = w;
	textureHeight = h;

	//setting the individual image size
	posRect.w = 64;
	posRect.h = 64;

	//set the x and y positions of the explosion rectangle
	posRect.x = x;
	posRect.y = y;

	//frame width and height of each animation image
	frameWidth = 64;
	frameHeight = 64;

	//original draw rectangle
	//used to draw one frame of the animation strip
	drawRect.x = 64;
	drawRect.y - 0;
	drawRect.w = frameWidth;
	drawRect.h = frameHeight;


}

//Reset the explosion method
void Explode::Reset()
{
	// deactivate the bullet
	active = false;
}

//Bullet update method
void Explode::Update(float deltaTime) // float delta
{
	//check to see if the bullet is active
	if (active)
	{
		//add to frame counter
		frameCounter += deltaTime;

		//check to see if enough time has passed
		if (frameCounter >= .035f)
		{
			//reset frame counter
			frameCounter = 0.0f;

			//add to the drawRect the width of an individual frame
			// to move the drawing area over one
			drawRect.x += frameWidth;

			//see if we have gone past the edge of the image - width
			if (drawRect.x >= textureWidth)
			{
				//if so, go back to the first - 0
				drawRect.x = 0;
				
				//set active set to face
				active = false;

				//move off screen until needed again
				posRect.x = -1000;
				posRect.y = -1000;
			}
		}
	}
}

//explosion draw method
void Explode::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer, texture, &drawRect, &posRect);
}

//Explosion Destruction
Explode::~Explode()
{
	//SDL_DestroyTexture(texture);
}