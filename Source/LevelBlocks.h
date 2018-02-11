#pragma once
#include "GameObject.h"

class LevelBlocks : public GameObject
{
public:
	LevelBlocks() = default;
	~LevelBlocks() = default;


	bool init(ASGE::Renderer * renderer) override;

private:
};
