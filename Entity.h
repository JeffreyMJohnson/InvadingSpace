#pragma once
class Entity
{
public:
	Entity();

	void SetSize(float width, float height);
	void SetPosition(float x, float y);

	virtual void Update(float a_deltaTime) = 0;
	virtual void Draw() = 0;

	void SetSpriteID(unsigned int a_spriteID);
	unsigned GetSpriteID();

	void SetWidth(float a_width);
	void SetHeight(float a_height);

	float GetWidth();
	float GetHeight();

	void SetX(float x);
	void SetY(float y);

	float GetX();
	float GetY();

	~Entity();

protected:

	unsigned int spriteID;

	float width;
	float height;

	float x;
	float y;

};

