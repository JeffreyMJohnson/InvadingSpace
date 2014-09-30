#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

//Keyboard Enums broken, search and use GLFW keyboard keys

//Window variables
const int TOTAL_ALIENS = 18;
const float PLAYER_WIDTH = 64.0f;
const float PLAYER_HEIGHT = 32.0f;
float enemySpeed = 100.f;

//Initialize game state functions
void UpdateMainMenu();
void DrawUI();
void UpdateGameState(float a_deltaTime);
void CreateEnemies();
void EnemiesLoad();
void MoveEnemies(int a_direction, float a_deltaTime, float a_speed);
void DrawEnemies();

Player player1;
Enemy aliens[TOTAL_ALIENS];
int enemiesDirection = 1;

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
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, "Psuedo-Invaders");

	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	GAMESTATES eCurrentState = MAIN_MENU;

	//Initialize player
	player1.SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	player1.SetSpriteID(CreateSprite("./images/cannon.png", player1.GetWidth(), player1.GetHeight(), true));
	player1.SetX(SCREEN_WIDTH * 0.5f);
	player1.SetY(140);
	player1.SetMovementKeys('A', 'D');
	player1.SetMovementExtremes(0, SCREEN_WIDTH);
	player1.SetSpeed(200.f);
	//Initialize font
	AddFont(invadersFont);

	//Initialize UI sprites
	playerLives1 = CreateSprite("./images/cannon.png", player1.GetWidth() * 0.5f, player1.GetHeight() * 0.5f, true);
	playerLives2 = CreateSprite("./images/cannon.png", player1.GetWidth() * 0.5f, player1.GetHeight() * 0.5f, true);
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 755, 780, true);

	//Initialize sprite position
	MoveSprite(player1.GetSpriteID(), player1.GetX(), player1.GetY());
	MoveSprite(playerLives1, SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT - 715);
	MoveSprite(playerLives2, SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 715);
	MoveSprite(arcadeMarquee, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	EnemiesLoad();

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
			UpdateGameState(deltaT);

			if (IsKeyDown(256)){
				eCurrentState = MAIN_MENU;
			}
			break;

		default:
			break;
		}
	} while (!FrameworkUpdate());

	DestroySprite(player1.GetSpriteID());
	DestroySprite(playerLives1);
	DestroySprite(playerLives2);
	DestroySprite(arcadeMarquee);
	Shutdown();

	return 0;
}

void UpdateMainMenu(){
	DrawSprite(arcadeMarquee);
	DrawString(insertCoins, SCREEN_WIDTH * 0.37f, SCREEN_HEIGHT * 0.5f);
	DrawString(totalCredits, SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.4f);
}

void UpdateGameState(float a_deltaTime){

	player1.Move(a_deltaTime, player1.GetSpeed());
	DrawSprite(player1.GetSpriteID());
	DrawUI();


	bool down = false;

	for (int i = 0; i < TOTAL_ALIENS; i++){
		//Collision Right
		if (aliens[i].GetX() > SCREEN_WIDTH * .9f){
			aliens[i].SetX(SCREEN_WIDTH * 0.9f);
			enemiesDirection = -1;
			down = true;
			break;
		}
		//Collision Left
		else if (aliens[i].GetX() < SCREEN_WIDTH * .1f){
			aliens[i].SetX(SCREEN_WIDTH * 0.1f);
			enemiesDirection = 1;
			down = true;
			break;
		}
	}

	if (down){
		for (int i = 0; i < TOTAL_ALIENS; i++){
			aliens[i].SetY(aliens[i].GetY() - .05f * SCREEN_HEIGHT);
		}
	}

	MoveEnemies(enemiesDirection, a_deltaTime, enemySpeed);
	DrawEnemies();


}

void EnemiesLoad(){

	//Initial position
	float enemyX = SCREEN_WIDTH * .2f;
	float enemyY = SCREEN_HEIGHT * .7f;

	for (int i = 0; i < TOTAL_ALIENS; i++){

		//Initialize Sprite
		aliens[i].SetSize(player1.GetWidth(), player1.GetHeight());
		aliens[i].SetSpriteID(CreateSprite("./images/invaders/invaders_1_00.png", player1.GetWidth(), player1.GetHeight(), true));

		if (enemyX > SCREEN_WIDTH * .8f){
			enemyX = SCREEN_WIDTH * .2f;
			enemyY -= .08f * SCREEN_HEIGHT;
		}

		//initialize position
		aliens[i].SetPosition(enemyX, enemyY);

		//Increment position
		enemyX += .12*SCREEN_WIDTH;
	}
}

void MoveEnemies(int a_direction, float a_deltaTime, float a_speed){

	for (int i = 0; i < TOTAL_ALIENS; i++){
		aliens[i].Move(a_deltaTime, a_direction, a_speed);
	}
}

void DrawEnemies(){
	for (int i = 0; i < TOTAL_ALIENS; i++){
		aliens[i].Draw();
	}
}



void DrawUI(){
	//Draw UI elements
	DrawString("Score < 1 >", SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT - 2);
	DrawString(scorePlayer1, SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 35);
	DrawString("High-Score", SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT - 2);
	DrawString(highScore, SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT - 35);
	DrawString("Score < 2 >", SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT - 2);
	DrawString(scorePlayer2, SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 35);
	DrawString("Credit(s)", SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT - 700);
	DrawString(totalCredits, SCREEN_WIDTH * 0.92f, SCREEN_HEIGHT - 700);
	DrawString("2", SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 700);
	DrawLine(0, 100, 672, 100, SColour(255, 255, 255, 255));
	DrawSprite(playerLives1);
	DrawSprite(playerLives2);
}