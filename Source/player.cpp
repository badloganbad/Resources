#include "player.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//player creation method
Player::Player(SDL_Renderer *renderer, int pNum, string filePath,
		string audioPath, float x, float y) {

	//activate the player
	active = true;

	//set the player number 0 or 1
	playerNum = pNum;

	//set float for player speed
	speed = 500.0f;

	laser = Mix_LoadWAV((audioPath + "laser.wav").c_str());

	//init score and lives vars
	oldScore = 0;
	playerScore = 0;
	oldLives = 0;
	playerLives = 3;

	//init the font system
	TTF_Init();

	//load the font
	font = TTF_OpenFont((audioPath + "SPACEMAN.TTF").c_str(), 25);

	//see if this is player 1, or player 2, and create the correct X and Y locations
	if (playerNum == 0) {
		//Create the score texture X and Y position
		scorePos.x = scorePos.y = 10;
		livesPos.x = 10;
		livesPos.y = 40;
	} else {
		//Create the score texture X and Y position
		scorePos.x = 550;
		scorePos.y = 10;
		livesPos.x = 550;
		livesPos.y = 40;
	}

	//update score method
	UpdateScore(renderer);

	//update lives method
	UpdateLives(renderer);

	//see if this is player 1 or player 2, and create the correct file path
	if (playerNum == 0) {
		//create the player 1 texture
		playerPath = filePath + "player.png";
	} else {
		//create the player 2 texture
		playerPath = filePath + "player2.png";
	}

	//load the surface surface
	surface = IMG_Load(playerPath.c_str());

	//load the surface into the texture
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the SDL_Rect x and y for the player
	posRect.x = x;
	posRect.y = y;
	//use SDL_QueryTexture to get the W and H of the Player's texture
	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	posRect.w = w;
	posRect.h = h;

	//set the movement floats to the players original X and Y
	pos_X = x;
	pos_Y = y;

	//set the xDir and yDir for the joysticks
	xDir = 0;
	yDir = 0;

	//string to create the path to the player's bullet image
	string bulletPath;

	//see if this is player 1 or player 2, and create the correct file path
	if (playerNum == 0) {
		//create the bullet 1 texture
		bulletPath = filePath + "bullet.png";
	} else {
		//create the bullet 2 texture
		bulletPath = filePath + "bullet2.png";
	}

	//create the player's bullet pool
	for (int i = 0; i < 10; i++) {
		//create the bullet and move offscreen, out of the game play area
		Bullet tmpBullet(renderer, bulletPath, -1000, -1000);

		//add to bulletlist
		bulletList.push_back(tmpBullet);
	}

}

//reset the player method
void Player::Reset()
{
	//place the player based on player number
	if (playerNum == 0)
	{
		//set the x and y for player 1
		posRect.x = 250.0;
		posRect.y = 500.0;
	}
	else
	{
		//set the x and y for player 2
		posRect.x = 550.0;
		posRect.y = 500.0;
	}

	pos_X = posRect.x;
	pos_Y = posRect.y;
	playerLives = 3;
	playerScore = 0;
	xDir = 0;
	yDir = 0;
	active = true;
}

//update score
void Player::UpdateLives(SDL_Renderer *renderer) {

	//fix for to_string problems on linux
	string Result;	//string which will contain the result
	ostringstream convert; // stream used for the conversion
	convert << playerLives; // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream

	//create the text for the  font texture
	tempLives = "Player Lives: " + Result;

	if (playerNum == 0) {
		//place the player 1 score info into a  surface
		livesSurface = TTF_RenderText_Solid(font, tempLives.c_str(), colorP1);
	} else {
		//place the player 2 score info into a  surface
		livesSurface = TTF_RenderText_Solid(font, tempLives.c_str(), colorP2);
	}

	//create the player score texture
	livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);

	//get the width and height of the texture
	SDL_QueryTexture(livesTexture, NULL, NULL, &livesPos.w, &livesPos.h);

	//free surface
	SDL_FreeSurface(livesSurface);

	//set old score
	oldLives = playerLives;

	//if player has no more lives
	if (playerLives <= 0)
	{
		//deactivate the player
		active = false;

		//move the
		posRect.x = posRect.y = -2000;

		//set float values to location values
		pos_X = pos_Y = -2000;
	}

}

//update score
void Player::UpdateScore(SDL_Renderer *renderer) {

	//fix for to_string problems on linux
	string Result;	//string which will contain the result
	ostringstream convert; // stream used for the conversion
	convert << playerScore; // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream

	//create the text for the  font texture
	tempScore = "Player Score: " + Result;

	if (playerNum == 0) {
		//place the player 1 score info into a  surface
		scoreSurface = TTF_RenderText_Solid(font, tempScore.c_str(), colorP1);
	} else {
		//place the player 2 score info into a  surface
		scoreSurface = TTF_RenderText_Solid(font, tempScore.c_str(), colorP2);
	}

	//create the player score texture
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	//get the width and height of the texture
	SDL_QueryTexture(scoreTexture, NULL, NULL, &scorePos.w, &scorePos.h);

	//free surface
	SDL_FreeSurface(scoreSurface);

	//set old score
	oldScore = playerScore;

}

//create a bullet
void Player::CreateBullet() {
	//see if there is a bullet active to fire
	for (int i = 0; i < bulletList.size(); i++) {
		//see if the bullet is not active
		if (bulletList[i].active == false) {
			//Play the Over Sound - plays fine through levels, must pause for QUIT
			Mix_PlayChannel(-1, laser, 0);

			//set bullet to active
			bulletList[i].active = true;

			//use some math in the x position to get the bullet close to
			// the center of the player using player width
			bulletList[i].posRect.x = (pos_X + (posRect.w / 2));

			//finishing aligning to the player center using the texture width
			bulletList[i].posRect.x = (bulletList[i].posRect.x
					- (bulletList[i].posRect.w / 2));
			bulletList[i].posRect.y = posRect.y;

			//set the x and y positions of the bullet's float positions
			bulletList[i].pos_X = pos_X;
			bulletList[i].pos_Y = pos_Y;

			//once bullet is found, break out of loop
			break;
		}
	}
}

//Player Joystick button method
void Player::OnControllerButton(const SDL_ControllerButtonEvent event) {
	//if the player's number is 0 and the joystick button is from joystick 0
	if (event.which == 0 && playerNum == 0) {
		//if a button
		if (event.button == 0) {
			//cout << "Player 1 - Button A" << endl;

			//create a bullet
			CreateBullet();
		}
	}

	//if the player's number is 1 and the joystick button is from joystick 1
	if (event.which == 1 && playerNum == 1) {
		//if A button
		if (event.button == 0) {
			//cout << "Player 2 - Button A" << endl;

			//create a bullet
			CreateBullet();
		}
	}
}

//Plyaer Joystick Axis Method
void Player::OnControllerAxis(const SDL_ControllerAxisEvent event) {
	//axis movements and button presses both sent here as SDL_ControllerAxisEvent structures

	//if the player's number is 0 and the joystick axis is from joystick 0
	if (event.which == 0 && playerNum == 0) {
		//X axis
		if (event.axis == 0) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				xDir = -1.0f; // left
			} else if (event.value > JOYSTICK_DEAD_ZONE) {
				xDir = 1.0f; // right
			} else {
				xDir = 0.0f; // none
			}
		}

		//Y axis
		if (event.axis == 1) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				yDir = -1.0f; // down
			} else if (event.value > JOYSTICK_DEAD_ZONE) {
				yDir = 1.0f; // up
			} else {
				yDir = 0.0f; // none
			}
		}
	}

	//if the player's number is 1 and the joystick axis is from joystick 0
	if (event.which == 1 && playerNum == 1) {
		//X axis
		if (event.axis == 0) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				xDir = -1.0f; // left
			} else if (event.value > JOYSTICK_DEAD_ZONE) {
				xDir = 1.0f; // right
			} else {
				xDir = 0.0f; // none
			}
		}

		//Y axis
		if (event.axis == 1) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				yDir = -1.0f; // down
			} else if (event.value > JOYSTICK_DEAD_ZONE) {
				yDir = 1.0f; // up
			} else {
				yDir = 0.0f; // none
			}
		}
	}
}

//Player update method
void Player::Update(float deltaTime, SDL_Renderer *renderer) {
	//Adjust position flaots based on speed, direction of joystick axis and deltaTime
	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;

	//update player position with code to account for precision loss
	posRect.x = (int) (pos_X + 0.5f);
	posRect.y = (int) (pos_Y + 0.5f);

	if (posRect.x < 0) {
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if (posRect.x > 1024 - posRect.w) {
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if (posRect.y < 0) {
		posRect.y = 0;
		pos_Y = posRect.y;
	}

	if (posRect.y > 768 - posRect.h) {
		posRect.y = 768 - posRect.h;
		pos_Y = posRect.y;
	}

	//update the player's bullets
	for (int i = 0; i < bulletList.size(); i++) {
		//check to see if the bullet is active
		if (bulletList[i].active) {
			//update bullet
			bulletList[i].Update(deltaTime);
		}
	}

	//should the score be updated?
	if (playerScore != oldScore) {
		UpdateScore(renderer);
	}

	//should the lives be updated?
	if (playerLives != oldLives) {
		UpdateLives(renderer);
	}

}

//player draw method
void Player::Draw(SDL_Renderer *renderer) {
	//draw the player texture using the vars texture and posRect
	SDL_RenderCopy(renderer, texture, NULL, &posRect);

	//draw the player's bullets
	for (int i = 0; i < bulletList.size(); i++) {
		//check to see if the bullet is active
		if (bulletList[i].active) {
			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}

	//Draw the player score
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scorePos);

	//Draw the player lives
	SDL_RenderCopy(renderer, livesTexture, NULL, &livesPos);

}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

