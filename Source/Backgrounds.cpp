#include "Backgrounds.h"

Backgrounds::Backgrounds(ASGE::Renderer * renderer, BackgroundTypes type)
{
	background_type = type;
	init(renderer);
}

void Backgrounds::init(ASGE::Renderer * renderer)
{
	object_sprite = renderer->createUniqueSprite();

	if (background_type == BackgroundTypes::DREAM_WORLD)
	{
		object_sprite->loadTexture("..\\..\\Resources\\DreamWorldBkg.png");
	}

	else if (background_type == BackgroundTypes::REAL_WORLD)
	{
		object_sprite->loadTexture("..\\..\\Resources\\RealWorldBkg.png");
	}


	object_sprite->xPos(0);
	object_sprite->yPos(0);
	object_sprite->width(1280);
	object_sprite->height(720);
}

void Backgrounds::update(const ASGE::GameTime & ms)
{
	//if needed
}
