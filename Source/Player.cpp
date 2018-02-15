#include "Player.h"

bool Player::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();
	

	if (!(object_sprite->loadTexture("..\\..\\Resources\\Cloud.png")))
	{
		return false;
	}


	float width = 250;
	float height = 200;

	object_sprite->xPos(250);
	object_sprite->yPos(520);
	object_sprite->width(width);
	object_sprite->height(height);
	return true;

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
