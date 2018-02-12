#include "LevelBlocks.h"

bool LevelBlocks::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();

	if (!(object_sprite->loadTexture("..\\..\\Resources\\ObstacleBlock.png")))
	{
		return false;
	}

	object_sprite->xPos(200);
	object_sprite->yPos(200);
	return true;
}
