#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"
#include "Bullet.h"

const int MAX_BULLETS = 20;


class Player
{
public:

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void SetShootKey(unsigned int a_shootKey);
	void Move(float a_deltaTime, float a_speed);

	void SetSpriteID(unsigned int a_spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float width);
	void SetHeight(float height);

	float GetWidth();
	float GetHeight();

	void SetX(float x);
	void SetY(float y);

	float GetX();
	float GetY();

	void SetSpeed(float speed);
	float GetSpeed();

	void Shoot(unsigned int a_textureID, float a_deltaTime);

	Bullet& GetInactiveBullet();

	Bullet bullets[MAX_BULLETS];

	Player();
	~Player();

private:

	unsigned int spriteID;
	float width;
	float height;
	float speed;
	float x;
	float y;

	unsigned int moveLeftKey;
	unsigned int moveRightKey;

	unsigned int shootKey;

	unsigned int leftExtreme;
	unsigned int rightExtreme;

	float currentReloadBulletTime;
	float maxBulletReloadTime;
};


#endif //_PLAYER_H_