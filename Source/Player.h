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

	float yVelocity();
	void yVelocity(float vel);

	bool isOnFloor();
	bool getIsGrounded() const;
	void setIsGrounded(bool type);

	void setIsJumping(bool type);

private:
	Player() = default;

	float width = 75;
	float height = 100;

	float movespeed_modifier = 200;
	float gravity = 260;
	float y_velocity = 0;
	float jump_strength = 250;

	bool is_jumping = false;
	bool is_grounded = true;
};