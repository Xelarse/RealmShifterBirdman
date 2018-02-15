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

void Player::moveLeft(const ASGE::GameTime & ms)
{
}

void Player::moveRight(const ASGE::GameTime & ms)
{
}

void Player::jump(const ASGE::GameTime & ms)
{
}
