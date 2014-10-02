#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_
#include "AIE.h"

class Bullet
{
public:
	
	float x;
	float y;

	float width;
	float height;

	unsigned int textureID;

	float velocityX;
	float velocityY;

	void Update(float a_deltaTime);
	void Draw();
	void InitializeBullet(float a_x, float a_y, float a_velocityX, float a_velocityY, unsigned int a_textureID);

	bool isActive;

	Bullet();
	~Bullet();

private:

};

#endif //_BULLET_H_