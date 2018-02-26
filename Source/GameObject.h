#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

class GameObject
{
public:

	GameObject() = default;
	~GameObject() = default;

	virtual void init(ASGE::Renderer * renderer) = 0;
	virtual void update(const ASGE::GameTime& ms) = 0;

	ASGE::Sprite* getObjectSprite();
	float getSpriteY();
	float getSpriteX();
	float getSpriteMaxY();
	float getSpriteMaxX();
	bool getIsRendering();

	void setIsRendering(bool value);

protected:
	std::unique_ptr<ASGE::Sprite> object_sprite = nullptr;
	bool is_rendering = false;
};
