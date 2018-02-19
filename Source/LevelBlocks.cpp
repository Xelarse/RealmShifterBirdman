#include "LevelBlocks.h"

LevelBlocks::LevelBlocks(ASGE::Renderer* renderer, BlockTypes type, float dim_x, float dim_y)
{
	width = dim_x;
	height = dim_y;
	block_type = type;
	init(renderer);
}

void LevelBlocks::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();
	
	if (block_type == BlockTypes::DREAM_WORLD)
	{
		object_sprite->loadTexture("..\\..\\Resources\\ObstacleBlock.png");
	}

	else if (block_type == BlockTypes::REAL_WORLD)
	{
		object_sprite->loadTexture("..\\..\\Resources\\ObstacleBlock.png");
	}
	

	object_sprite->xPos(1500);
	object_sprite->yPos(1500);
	object_sprite->width(width);
	object_sprite->height(height);
}

void LevelBlocks::update(const ASGE::GameTime& ms)
{
	//Add update logic here if required
}
