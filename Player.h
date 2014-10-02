#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"
#include "Entity.h"
#include "Bullet.h"

const int MAX_BULLETS = 20;


class Player : public Entity
{
public:

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);

	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);

	virtual void Update(float a_deltaTime);
	virtual void Draw();

	void SetShootKey(unsigned int a_shootKey);

	void SetSpeed(float speed);
	float GetSpeed();

	void SetScore(int a_score);
	int GetScore();

	void Shoot(unsigned int a_textureID, float a_deltaTime);

	Bullet& GetInactiveBullet();

	Bullet bullets[MAX_BULLETS];

	Player();
	~Player();

private:

	float speed;
	int score;

	unsigned int moveLeftKey;
	unsigned int moveRightKey;

	unsigned int shootKey;

	unsigned int leftExtreme;
	unsigned int rightExtreme;

	float currentReloadBulletTime;
	float maxBulletReloadTime;
};


#endif //_PLAYER_H_