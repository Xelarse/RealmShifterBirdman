#pragma once
#include "GameObject.h"
#include "StateMachine.h"


namespace ASGE
{
	struct GameTime;
}

class StateMachine;

class Player : public GameObject
{

public:
	Player(ASGE::Renderer* renderer);
	~Player() = default;

	void init(ASGE::Renderer * renderer) override;
	void update(const ASGE::GameTime& ms) override;

	void moveLeft(const ASGE::GameTime& ms);
	void moveRight(const ASGE::GameTime& ms);
	void jump(const ASGE::GameTime& ms);

private:
	Player() = default;

	float width = 250;
	float height = 200;

	float movespeed_modifier = 100;
};