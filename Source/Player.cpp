#include "Player.h"


Player::Player(ASGE::Renderer * renderer)
{
	init(renderer);
}

void Player::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();
	object_sprite->loadTexture("..\\..\\Resources\\Cloud.png");

	object_sprite->xPos(250);
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

	//TODO add jump update later
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
}
