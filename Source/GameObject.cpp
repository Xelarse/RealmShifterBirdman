#include "GameObject.h"

ASGE::Sprite* GameObject::getObjectSprite()
{
	return object_sprite.get();
}

bool GameObject::getIsRendering()
{
	return is_rendering;
}

void GameObject::setIsRendering(bool value)
{
	is_rendering = value;
}
