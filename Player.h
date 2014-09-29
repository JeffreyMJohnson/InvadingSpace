#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"



class Player
{
public:

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void Move(float a_deltaTime, float a_speed);

	void SetSpriteID(unsigned int spriteID);
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

	unsigned int leftExtreme;
	unsigned int rightExtreme;
};


#endif //_PLAYER_H_