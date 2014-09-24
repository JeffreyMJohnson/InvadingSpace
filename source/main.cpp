#include "AIE.h"
#include <iostream>

//Keyboard Enums broken, search and use GLFW keyboard keys

//Window variables
const int iScreenWidth = 672;
const int iScreenHeight = 780;
const int alienRows = 3;
const int alienColumns = 4;
const int totalAliens = alienColumns * alienRows;
const float playerWidth = 64.0f;
const float playerHeight = 32.0f;
const int alienStartX = 50;
const int alienStartY = 600;
const float alienPadding = 5.0f;

//Initialize game state functions
void UpdateMainMenu();
void DrawUI();
void UpdateGameState(float a_deltaTime);
void CreateEnemies();
void DrawEnemies();


//Player Structure
struct PlayerCannon{
	unsigned int spriteID;
	float speed = 200.f;
	float width;
	float height;

	void SetSize(float a_width, float a_height){
		width = a_width;
		height = a_height;
	}

	float x;
	float y;
	void SetPosition(float a_x, float a_y){
		x = a_x;
		y = a_y;
	}

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight){
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
	}

	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme){
		leftMovementExtreme = a_leftExtreme;
		rightMovementExtreme = a_rightExtreme;
	}

	void Move(float a_timeStep, float a_speed){
		if (IsKeyDown(moveLeftKey)){
			x -= a_timeStep * a_speed;
			if (x < (leftMovementExtreme + width * .5f)){
				x = (leftMovementExtreme + width * .5f);
			}
		}
		if (IsKeyDown(moveRightKey)){
			x += a_timeStep * a_speed;
			if (x >(rightMovementExtreme - width * .5f)){
				x = (rightMovementExtreme - width * .5f);
			}
		}
		MoveSprite(spriteID, x, y);
	}
};

enum  DIR
{
	LEFT,
	RIGHT,
	DOWN,
};

struct AlienShip{
	unsigned int spriteID;
	float speed = 50.f;
	float width = playerWidth;
	float height = playerHeight;
	float x;
	float y;
	DIR direction = RIGHT;
	void SetSize(float a_width, float a_height){
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y){
		x = a_x;
		y = a_y;
	}

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight){
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
	}

	bool Move(){
		if (direction == LEFT){
			if (x < width * 0.5f){
				return false;
			}
		}
		if (direction == RIGHT){
			if (x > iScreenWidth - (width * .5f)){
				return false;
			}
		}
		return true;
	}

};

PlayerCannon player;
AlienShip aliens[totalAliens];

//Player global veriables
unsigned int arcadeMarquee;
//unsigned int alienShips[18];
unsigned int playerLives1;
unsigned int playerLives2;

const char* invadersFont = "./fonts/invaders.fnt";

//UI variables
char scorePlayer1[10] = "00000";
char scorePlayer2[10] = "00000";
char highScore[10] = "00000";
char totalCredits[10] = "00";
char totalLives[2] = "2";
char* insertCoins = "Insert_Coins";

enum GAMESTATES{
	MAIN_MENU,
	GAMEPLAY,
	END,
};

int main(int argc, char* argv[])
{
	Initialise(iScreenWidth, iScreenHeight, false, "Psuedo-Invaders");

	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	GAMESTATES eCurrentState = MAIN_MENU;

	//Initialize player
	player.SetSize(playerWidth, playerHeight);
	player.spriteID = CreateSprite("./images/cannon.png", player.width, player.height, true);
	player.x = iScreenWidth * 0.5f;
	player.y = 140;
	player.SetMovementKeys('A', 'D');
	player.SetMovementExtremes(0, iScreenWidth);

	aliens[1].SetMovementKeys('A', 'D');
	//Initialize font
	AddFont(invadersFont);

	//Initialize UI sprites
	playerLives1 = CreateSprite("./images/cannon.png", player.width * 0.5f, player.height * 0.5f, true);
	playerLives2 = CreateSprite("./images/cannon.png", player.width * 0.5f, player.height * 0.5f, true);
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 755, 780, true);

	//Initialize sprite position
	MoveSprite(player.spriteID, player.x, player.y);
	MoveSprite(playerLives1, iScreenWidth * 0.1f, iScreenHeight - 715);
	MoveSprite(playerLives2, iScreenWidth * 0.15f, iScreenHeight - 715);
	MoveSprite(arcadeMarquee, iScreenWidth * 0.5f, iScreenHeight * 0.5f);

	//Initialize alien sprites

	CreateEnemies();
	DrawEnemies();

	do{

		ClearScreen();
		float deltaT = GetDeltaTime();
		SetFont(invadersFont);

		switch (eCurrentState){

		case MAIN_MENU:
			UpdateMainMenu();


			if (IsKeyDown(257)){
				eCurrentState = GAMEPLAY;
			}
			if (IsKeyDown(290)){
				Shutdown();
				exit(0);
			}

			break;

		case GAMEPLAY:
			DrawEnemies();
			UpdateGameState(deltaT);

			if (IsKeyDown(256)){
				eCurrentState = MAIN_MENU;
			}
			break;

		default:
			break;
		}
	} while (!FrameworkUpdate());

	DestroySprite(player.spriteID);
	DestroySprite(playerLives1);
	DestroySprite(playerLives2);
	DestroySprite(arcadeMarquee);
	Shutdown();

	return 0;
}

void UpdateMainMenu(){
	DrawSprite(arcadeMarquee);
	DrawString(insertCoins, iScreenWidth * 0.37f, iScreenHeight * 0.5f);
	DrawString(totalCredits, iScreenWidth * 0.25f, iScreenHeight * 0.4f);
}

void UpdateGameState(float a_deltaTime){
	DrawUI();
	player.SetMovementExtremes(0, iScreenWidth);
	player.Move(a_deltaTime, player.speed);
	DrawSprite(player.spriteID);

}

void CreateEnemies(){
	//Initialize alien ships
	for (int i = 0; i < totalAliens; i++){
		aliens[i].spriteID = CreateSprite("./images/invaders/invaders_1_00.png", aliens[i].width, aliens[i].height, true);
	}

}

void DrawEnemies(){
	int xPos;
	int yPos = alienStartY;
	int i = 0;

	for (int row = 0; row < alienRows; row++){
		xPos = alienStartX;
		for (int col = 0; col < alienColumns; col++, i++){
			aliens[i].SetPosition(xPos, yPos);
			MoveSprite(aliens[i].spriteID, aliens[i].x, aliens[i].y);
			DrawSprite(aliens[i].spriteID);
			xPos += aliens[i].width + alienPadding;

			std::cout << aliens[i].x << " " << aliens[i].y << std::endl;
		}
		yPos -= playerHeight + alienPadding;
	}
}

void DrawUI(){
	//Draw UI elements
	DrawString("Score < 1 >", iScreenWidth * 0.1f, iScreenHeight - 2);
	DrawString(scorePlayer1, iScreenWidth * 0.15f, iScreenHeight - 35);
	DrawString("High-Score", iScreenWidth * 0.4f, iScreenHeight - 2);
	DrawString(highScore, iScreenWidth * 0.45f, iScreenHeight - 35);
	DrawString("Score < 2 >", iScreenWidth * 0.7f, iScreenHeight - 2);
	DrawString(scorePlayer2, iScreenWidth * 0.75f, iScreenHeight - 35);
	DrawString("Credit(s)", iScreenWidth * 0.7f, iScreenHeight - 700);
	DrawString(totalCredits, iScreenWidth * 0.92f, iScreenHeight - 700);
	DrawString("2", iScreenWidth * 0.05f, iScreenHeight - 700);
	DrawLine(0, 100, 672, 100, SColour(255, 255, 255, 255));
	DrawSprite(playerLives1);
	DrawSprite(playerLives2);
}