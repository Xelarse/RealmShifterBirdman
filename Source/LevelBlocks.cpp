#include "LevelBlocks.h"

bool LevelBlocks::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();

	if (!(object_sprite->loadTexture("..\\..\\Resources\\ObstacleBlock.png")))
	{
		return false;
	}

	float width = 200;
	float height = 400;

	object_sprite->xPos(600);
	object_sprite->yPos(320);
	object_sprite->width(width);
	object_sprite->height(height);
	return true;
}
