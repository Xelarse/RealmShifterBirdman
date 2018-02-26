#include "Player.h"


Player::Player(ASGE::Renderer * renderer)
{
	init(renderer);
}

void Player::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();
	object_sprite->loadTexture("..\\..\\Resources\\Cloud.png");

	object_sprite->xPos(-10);
	object_sprite->yPos(520);
	object_sprite->width(width);
	object_sprite->height(height);
}

void Player::update(const ASGE::GameTime& ms)
{
	switch (move_state)
	{
		case PlayerMoveState::MOVE_LEFT:
		{
			moveLeft(ms);
			break;
		}

		case PlayerMoveState::MOVE_RIGHT:
		{
			moveRight(ms);
			break;
		}
	}

	if (jump_state == PlayerJumpState::JUMP_ON)
	{
		jump(ms);
	}

	if (is_jumping && isGrounded())
	{
		y_velocity = 0;
		is_jumping = false;
		is_grounded = true;
		jump_state = PlayerJumpState::JUMP_OFF;
	}
}

void Player::moveLeft(const ASGE::GameTime & ms)
{
	float delta_time = ms.delta_time.count() / 1000;
	object_sprite->xPos(object_sprite->xPos() - movespeed_modifier * delta_time);
}

void Player::moveRight(const ASGE::GameTime & ms)
{
	float delta_time = ms.delta_time.count() / 1000;
	object_sprite->xPos(object_sprite->xPos() + movespeed_modifier * delta_time);
}

void Player::jump(const ASGE::GameTime & ms)
{
	if (!is_jumping)
	{
		is_jumping = true;
		is_grounded = false;
		y_velocity = -jump_strength;
	}

	object_sprite->yPos(object_sprite->yPos() + y_velocity * (ms.delta_time.count() /1000));

	y_velocity += gravity * ms.delta_time.count() / 1000;
}

bool Player::isGrounded()
{
	if (object_sprite->yPos() >= 720 - (height))
	{
		object_sprite->yPos(720 - height);
		return true;
	}

	else
	{
		return false;
	}
}

void Player::setIsGrounded(bool type)
{
	is_grounded = type;
}
