#include "LevelBlocks.h"

bool LevelBlocks::init(ASGE::Renderer * renderer)
{
	ASGE::Sprite* throwaway = object_sprite.get();
	throwaway = renderer->createRawSprite();

	if (!(object_sprite->loadTexture("..\\..\\Resources\\ObstacleBlock.png")))
	{
		return false;
	}

	object_sprite->xPos(200);
	object_sprite->yPos(200);
	return true;
}
