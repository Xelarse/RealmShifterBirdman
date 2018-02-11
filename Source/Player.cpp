#include "Player.h"

bool Player::init(ASGE::Renderer * renderer)
{
	ASGE::Sprite* throwaway = object_sprite.get();
	throwaway = renderer->createRawSprite();

	if (!(object_sprite->loadTexture("..\\..\\Resources\\Cloud.png")))
	{
		return false;
	}

	object_sprite->xPos(200);
	object_sprite->yPos(200);
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
