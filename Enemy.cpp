#include "Enemy.h"


Enemy::Enemy()
{
	isActive = true;
}

void Enemy::SetSpriteID(unsigned int a_spriteID){
	spriteID = a_spriteID;
}

unsigned int Enemy::GetSpriteID(){
	return spriteID;
}

void Enemy::SetWidth(float width){
	this->width = width;
}

float Enemy::GetWidth(){
	return width;
}

void Enemy::SetHeight(float height){
	this->height = height;
}

float Enemy::GetHeight(){
	return height;
}

void Enemy::SetSpeed(float speed){
	this->speed = speed;
}

float Enemy::GetSpeed(){
	return speed;
}

void Enemy::SetX(float x){
	this->x = x;
}

float Enemy::GetX(){
	return x;
}

void Enemy::SetY(float y){
	this->y = y;
}

float Enemy::GetY(){
	return y;
}

void Enemy::SetSize(float a_width, float a_height){
	width = a_width;
	height = a_height;
}

void Enemy::SetPosition(float a_x, float a_y){
	x = a_x;
	y = a_y;
}

void Enemy::Move(float a_deltaTime, int a_direction, float a_speed){
	x += a_speed * a_direction * a_deltaTime;
}

void Enemy::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

Enemy::~Enemy()
{
}
