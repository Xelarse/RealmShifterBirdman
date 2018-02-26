#include "GameObject.h"

ASGE::Sprite* GameObject::getObjectSprite()
{
	return object_sprite.get();
}

float GameObject::getSpriteY()
{
	return object_sprite->yPos();
}

float GameObject::getSpriteX()
{
	return object_sprite->xPos();
}

float GameObject::getSpriteMaxY()
{
	return object_sprite->yPos() + object_sprite->height();
}

float GameObject::getSpriteMaxX()
{
	return object_sprite->xPos() + object_sprite->width();
}

bool GameObject::getIsRendering()
{
	return is_rendering;
}

void GameObject::setIsRendering(bool value)
{
	is_rendering = value;
}
