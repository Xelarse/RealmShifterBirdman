#pragma once
#include "GameObject.h"


enum class BlockTypes
{
	DREAM_WORLD,
	REAL_WORLD
};

class LevelBlocks : public GameObject
{
public:
	LevelBlocks(ASGE::Renderer* renderer, BlockTypes type, float dim_x, float dim_y);
	~LevelBlocks() = default;


	void init(ASGE::Renderer * renderer) override;
	void update(const ASGE::GameTime& ms) override;

private:
	
	LevelBlocks() = default;

	float width;
	float height;
	BlockTypes block_type;
};


