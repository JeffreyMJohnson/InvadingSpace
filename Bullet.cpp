#include "Bullet.h"


Bullet::Bullet()
{
}

void Bullet::Draw(){
	if (isActive){
		MoveSprite(textureID, x, y);
		DrawSprite(textureID);
	}
}

void Bullet::Update(float a_deltaTime){
	if (isActive){
		x += velocityX * a_deltaTime;
		y += velocityY * a_deltaTime;
	}

	if (y > 1000){
		isActive = false;
	}
}

void Bullet::InitializeBullet(float a_x, float a_y, float a_velocityX, float a_velocityY, unsigned int a_textureID){
	x = a_x;
	y = a_y;
	velocityX = a_velocityX;
	velocityY = a_velocityY;
	textureID = a_textureID;

	isActive = true;
}

Bullet::~Bullet()
{
}
