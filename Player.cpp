#include "Player.h"



Player::Player()
{

	currentReloadBulletTime = 0.0f;
	maxBulletReloadTime = .25f;

}

//
void Player::SetScore(int a_score){
	score = a_score;
}

int Player::GetScore(){
	return score;
}

void Player::SetSpriteID(unsigned int a_spriteID){
	spriteID = a_spriteID;
}

unsigned int Player::GetSpriteID(){
	return spriteID;
}

void Player::SetWidth(float width){
	this->width = width;
}

float Player::GetWidth(){
	return width;
}

void Player::SetHeight(float height){
	this->height = height;
}

float Player::GetHeight(){
	return height;
}

void Player::SetSpeed(float speed){
	this->speed = speed;
}

float Player::GetSpeed(){
	return speed;
}

void Player::SetX(float x){
	this->x = x;
}

float Player::GetX(){
	return x;
}

void Player::SetY(float y){
	this->y = y;
}

float Player::GetY(){
	return y;
}

void Player::SetSize(float a_width, float a_height){
	width = a_width;
	height = a_height;
}

void Player::SetPosition(float a_x, float a_y){
	x = a_x;
	y = a_y;
}

void Player::SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight){
	moveLeftKey = a_moveLeft;
	moveRightKey = a_moveRight;
}

void Player::SetShootKey(unsigned int a_shootKey){
	shootKey = a_shootKey;
}

void Player::SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme){
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
}

void Player::Move(float a_deltaTime, float a_speed){
	if (IsKeyDown(moveLeftKey)){
		x -= a_deltaTime * a_speed;
		if (x < (leftExtreme + width * .5f)){
			x = (leftExtreme + width * .5f);
		}
	}
	if (IsKeyDown(moveRightKey)){
		x += a_deltaTime * a_speed;
		if (x > rightExtreme - width * .5f){
			x = (rightExtreme - width * .5f);
		}
	}
	MoveSprite(spriteID, x, y);
}

void Player::Shoot(unsigned int a_textureID, float a_deltaTime){
	if (IsKeyDown(shootKey) && currentReloadBulletTime >= maxBulletReloadTime){
		GetInactiveBullet().InitializeBullet(x, y, 0, 300, a_textureID);
		currentReloadBulletTime = 0.0f;
	}
	currentReloadBulletTime += a_deltaTime;
}

Bullet& Player::GetInactiveBullet(){
	for (int i = 0; i < MAX_BULLETS; i++){
		if (!bullets[i].isActive){
			return bullets[i];
		}
	}
	return bullets[0];
}

Player::~Player()
{
}
