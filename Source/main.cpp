#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#endif

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#endif

#include <stdio.h>
#include <iostream>
using namespace std;

// variables for the background movement and position
//int for the background
int bkgdSpeed = 100;

// create the SDL Rectangle for the background texture's position and size - background 1 and 2
SDL_Rect bkgd1Pos, bkgd2Pos;

// Background float vars for movement
float b1pos_X = 0, b1pos_Y = 0;
float b2pos_X = 0, b2pos_Y = -768;

// code for frame rate independence - deltaTime var initialization
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

// move the background
void UpdateBackground() {
	//Update background 1's float position values
	b1pos_Y += (bkgdSpeed * 1) * deltaTime;

	// set the new bkgd1 position
	bkgd1Pos.y = (int) (b1pos_Y + 0.5f);

	// reset the float position values of Bkgd1 when off the bottom of the screen
	if (bkgd1Pos.y >= 768) {
		bkgd1Pos.y = -768;
		b1pos_Y = bkgd1Pos.y;
	}

	//Update background 2
	b2pos_Y += (bkgdSpeed * 1) * deltaTime;

	// set the new bkgd2 position
	bkgd2Pos.y = (int) (b2pos_Y + 0.5f);

	// reset the float position values of Bkgd1 when off the bottom of the screen
	if (bkgd2Pos.y >= 768) {
		bkgd2Pos.y = -768;
		b2pos_Y = bkgd2Pos.y;
	}
}

int main(int argc, char* argv[]) {

#if defined(__linux__)
	cout << "Running on Linux" << endl;
	cout << "Added on Linux" << endl;
#endif

#if defined(__APPLE__)
	cout << "Running on Apple" << endl;
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	// create a sting linking to the mac's images folder
	string s_cwd_images = s_cwd + "/Resources/Images";

	//test
	cout << s_cwd_images << endl;
#endif

#if defined(_WIN32) || (_WIN64)
	cout << "Running on Windows" << endl;
	cout << "Added on Windows" << endl;
#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			1024,                               // width, in pixels
			768,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//declare renderer
	SDL_Renderer *renderer = NULL;

	//create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//***** Create Background - START ******
	string BKGDpath = s_cwd_images + "/bkgd.png";

	// create a SDL surface to hold the background image
	SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	// create a SDL texture
	SDL_Texture *bkgd1;

	// place surface into the texture bkgd1
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	// create a SDL texture
	SDL_Texture *bkgd2;

	// place surface into the texture bkgd1
	bkgd2 = SDL_CreateTextureFromSurface(renderer, surface);

	// free the SDL surface
	// SDL_FreeSurface(surface);

	// create the SDL_Rectangel for the texture's position and size -x,y,w,h
	//  SDL_Rect bkgd1Pos;

	// set the X, Y, W, and H for the Rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;

	// create the SDL_Rectangel for the texture's position and size -x,y,w,h
	// SDL_Rect bkgd2Pos;

	// set the X, Y, W, and H for the Rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;

	// set speed for background
	// int bkgdSpeed = 100;

	// set temp variables to hold movement - background 1
	// float BG1pos_X = 0, BG1pos_Y = 0;

	// set temp variables to hold movement - background 2
	// float BG2pos_X = 0, BG2pos_Y = -768;

	// **************CREATE BACKGROUNDS - END ***************

	//***** Create Main Menu - START ******

	//*******TITLE - START**************

	// create a SDL surface to hold the background image
	surface = IMG_Load((s_cwd_images + "/title.png").c_str());

	// create a SDL texture
	SDL_Texture *title;

	// place surface into the texture bkgd1
	title = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the title graphic
	SDL_Rect titlePos;

	// set the X, Y, W, and H for the Rectangle - title
	titlePos.x = 264;
	titlePos.y = 73;
	titlePos.w = 532;
	titlePos.h = 71;

	//*******Title end*********

	//******* 1 Player - START**************

	// create a SDL surface to hold the 1 player button
	surface = IMG_Load((s_cwd_images + "/one_n.png").c_str());

	// create a SDL texture
	SDL_Texture *players1N;

	// place surface into the 1 player button
	players1N = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the 1 player button
	surface = IMG_Load((s_cwd_images + "/one_o.png").c_str());

	// create a SDL texture
	SDL_Texture *players1O;

	// place surface into the 1 player button
	players1O = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the 1 player button
	SDL_Rect players1NPos;

	// set the X, Y, W, and H for the Rectangle - 1 player button
	players1NPos.x = 380;
	players1NPos.y = 261;
	players1NPos.w = 311;
	players1NPos.h = 42;

	//******* 1 Player end*********

	//******* 2 Player - START**************

	// create a SDL surface to hold the 2 player button
	surface = IMG_Load((s_cwd_images + "/two_n.png").c_str());

	// create a SDL texture
	SDL_Texture *players2N;

	// place surface into the 2 player button
	players2N = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the 2 player button
	surface = IMG_Load((s_cwd_images + "/two_o.png").c_str());

	// create a SDL texture
	SDL_Texture *players2O;

	// place surface into the 2 player button
	players2O = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the 2 player button graphic
	SDL_Rect players2NPos;

	// set the X, Y, W, and H for the Rectangle - 2 player button
	players2NPos.x = 360;
	players2NPos.y = 343;
	players2NPos.w = 352;
	players2NPos.h = 42;

	//******* 2 Player end*********

	//******* Instructions - START**************

	// create a SDL surface to hold the Instructions button
	surface = IMG_Load((s_cwd_images + "/instruct_n.png").c_str());

	// create a SDL texture
	SDL_Texture *instructN;

	// place surface into the Instructions button
	instructN = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the Instructions button
	surface = IMG_Load((s_cwd_images + "/instruct_o.png").c_str());

	// create a SDL texture
	SDL_Texture *instructO;

	// place surface into the Instructions button
	instructO = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the Instructions button
	SDL_Rect instructNPos;

	// set the X, Y, W, and H for the Rectangle - Instructions button
	instructNPos.x = 351;
	instructNPos.y = 424;
	instructNPos.w = 374;
	instructNPos.h = 42;

	//******* Instructions end*********

	//******* Quit GAME - START**************

	// create a SDL surface to hold the quit game button
	surface = IMG_Load((s_cwd_images + "/2quit_n.png").c_str());

	// create a SDL texture
	SDL_Texture *quitN;

	// place surface into the Instructions button
	quitN = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the Instructions button
	surface = IMG_Load((s_cwd_images + "/2quit_o.png").c_str());

	// create a SDL texture
	SDL_Texture *quitO;

	// place surface into the Instructions button
	quitO = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the Instructions button
	SDL_Rect quitNPos;

	// set the X, Y, W, and H for the Rectangle - Instructions button
	quitNPos.x = 391;
	quitNPos.y = 503;
	quitNPos.w = 288;
	quitNPos.h = 42;

	//******* Instructions end*********

	//********************* Create Main Menu - END ***************

	//***** Create Instructions Menu - START ******

	//*******INSTRUCTIONS GRAPHIC - START**************

	// create a SDL surface to hold the instructions image
	surface = IMG_Load((s_cwd_images + "/instructions.png").c_str());

	// create a SDL texture
	SDL_Texture *instructionsText;

	// place surface into the texture bkgd1
	instructionsText = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the title graphic
	SDL_Rect instructionsTextPos;

	// set the X, Y, W, and H for the Rectangle - title
	instructionsTextPos.x = 120;
	instructionsTextPos.y = 271;
	instructionsTextPos.w = 781;
	instructionsTextPos.h = 258;

	//*******INSTRUCTIONS GRAPHIC end*********

	//*********Create Instructions Menu - start

	//*******Small menu button - START**************

	// create a SDL surface to hold the instructions image
	surface = IMG_Load((s_cwd_images + "/menu_n.png").c_str());

	// create a SDL texture
	SDL_Texture *menuN;

	// place surface into the texture bkgd1
	menuN = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the instructions image
	surface = IMG_Load((s_cwd_images + "/menu_o.png").c_str());

	// create a SDL texture
	SDL_Texture *menuO;

	// place surface into the texture bkgd1
	menuO = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	//create SDL Rectangle for the title graphic
	SDL_Rect menuNPos;

	// set the X, Y, W, and H for the Rectangle - title
	menuNPos.x = 22;
	menuNPos.y = 702;
	menuNPos.w = 145;
	menuNPos.h = 41;

	//*******small Menu button end*********

	//********Create Instructions Menu - END *************

	//***************CREATE CURSOR*****************
	//Create Cursor
	string CURSORpath = s_cwd_images + "/cursor3.png";

	// create a SDL surface to hold the background image
	surface = IMG_Load(CURSORpath.c_str());

	// create a SDL texture
	SDL_Texture *cursor;

	// place surface into the texture bkgd1
	cursor = SDL_CreateTextureFromSurface(renderer, surface);

	//Release the surface for later use
	SDL_FreeSurface(surface);

	// create the SDL_Rectangel for the texture's position and size -x,y,w,h
	SDL_Rect cursorPos, activePos;

	// set the X, Y, W, and H for the Rectangle - for the cursor graphic
	cursorPos.x = 0;
	cursorPos.y = 0;
	cursorPos.w = 64;
	cursorPos.h = 64;

	// set the X, Y, W, and H for the Rectangle - for the cursor hitbox
	activePos.x = 10;
	activePos.y = 10;
	activePos.w = 10;
	activePos.h = 10;

	// var from the cursor speed
	int cursorSpeed = 400;

	//************* Create Cursor - END ******************

	//****** Set up a Game Controller Variable *****
	SDL_GameController* gGameController = NULL;

	//***** Open Game Controller ******
	gGameController = SDL_GameControllerOpen(0);

	//***** Turn on Game Controller Events *****
	SDL_GameControllerEventState(SDL_ENABLE);

	//***** SDL Event to handle event input *****
	SDL_Event event;

	// set up variables for the games states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	// set up the initial state
	GameState gameState = MENU;

	//boolean values to control movement through the states
	bool menu, instructions, players1, players2, win, lose, quit = false;

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		case MENU:
			menu = true;
			cout << "The Game State is Menu" << endl;
			cout << "Press the A Button for Instructions" << endl;
			cout << "Press the B Button for 1 Player Game" << endl;
			cout << "Press the X Button for 2 Player Game" << endl;
			cout << "Press the Y Button for Quit Game" << endl;
			cout << endl;

			while (menu) {
				// Create deltaTime - for frame rate independence
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						menu = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								menu = false;
								gameState = INSTRUCTIONS;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								menu = false;
								gameState = PLAYERS1;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								menu = false;
								gameState = PLAYERS2;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								cout << "Y button pressed";
								menu = false;
								quit = true;
							}
						}
						break;
					}
				}

				// Update
				UpdateBackground();

				// Start Drawing

				// Clear SDL renderer - clear the old screen buffer
				SDL_RenderClear(renderer);

				// Draw the Bkgd1 image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				// Draw the Bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				// Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);

				// Draw the 1 player button
				SDL_RenderCopy(renderer, players1N, NULL, &players1NPos);

				// Draw the 2 player button
				SDL_RenderCopy(renderer, players2N, NULL, &players2NPos);

				// Draw the instruct button
				SDL_RenderCopy(renderer, instructN, NULL, &instructNPos);

				// Draw the quit game button
				SDL_RenderCopy(renderer, quitN, NULL, &quitNPos);

				// Draw the cursor image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				// SDL Render present - draw new, updated screen
				SDL_RenderPresent(renderer);

			}
			break; //end main menu case

		case INSTRUCTIONS:
			instructions = true;
			cout << "The Game State is Instructions" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << endl;

			while (instructions) {

				// Create deltaTime - for frame rate independence
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						instructions = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								instructions = false;
								gameState = MENU;
							}
						}
						break;
					}
				}

				// Update
				UpdateBackground();

				// Start Drawing

				// Clear SDL renderer - clear the old screen buffer
				SDL_RenderClear(renderer);

				// Draw the Bkgd1 image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				// Draw the Bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				// Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);

				// Draw the instructions Graphic
				SDL_RenderCopy(renderer, instructionsText, NULL,
						&instructionsTextPos);

				// Draw the instructions Graphic
				SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);

				// Draw the cursor image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				// SDL Render present - draw new, updated screen
				SDL_RenderPresent(renderer);

			}
			break; //end instructions case

		case PLAYERS1:
			players1 = true;
			cout << "The Game State is 1 Player Game" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;

			while (players1) {
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players1 = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								players1 = false;
								gameState = WIN;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								players1 = false;
								gameState = LOSE;
							}
						}
						break;
					}
				}
			}
			break; //end players1 case

		case PLAYERS2:
			players2 = true;
			cout << "The Game State is 2 Player Game" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;

			while (players2) {
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players2 = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								players2 = false;
								gameState = WIN;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								players2 = false;
								gameState = LOSE;
							}
						}
						break;
					}
				}
			}
			break; //end players2 case

		case WIN:
			win = true;
			cout << "The Game State is Win" << endl;
			cout << "Press the A Button for Main Menu Screen" << endl;
			cout << "Press the B Button for Quit Game" << endl;
			cout << endl;

			while (win) {
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						win = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								win = false;
								gameState = MENU;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								win = false;
								quit = true;
							}
						}
						break;
					}
				}
			}
			break; //end win case

		case LOSE:
			lose = true;
			cout << "The Game State is Lose" << endl;
			cout << "Press the A Button for Main Menu Screen" << endl;
			cout << "Press the B Button for Quit Game" << endl;
			cout << endl;

			while (lose) {
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						lose = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								lose = false;
								gameState = MENU;
							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								lose = false;
								quit = true;
							}
						}
						break;
					}
				}
			}
			break; //end lose case

		}
	}

	// SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
