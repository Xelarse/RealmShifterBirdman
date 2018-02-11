#pragma once
#include "GameObject.h"


namespace ASGE
{
	struct GameTime;
}

class Player : public GameObject
{

public:
	Player() = default;
	~Player() = default;

	bool init(ASGE::Renderer * renderer) override;

	void moveLeft(const ASGE::GameTime& ms);
	void moveRight(const ASGE::GameTime& ms);
	void jump(const ASGE::GameTime& ms);

private:
};