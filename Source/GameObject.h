#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

class GameObject
{
public:

	GameObject() = default;
	~GameObject() = default;

	virtual bool init(ASGE::Renderer * renderer) = 0;

	ASGE::Sprite* getObjectSprite();
	bool getIsRendering();

	void setIsRendering(bool value);

protected:
	std::unique_ptr<ASGE::Sprite> object_sprite = nullptr;
	bool is_rendering = false;
};
