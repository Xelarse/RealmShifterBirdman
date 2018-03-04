#pragma once
#include <Engine\OGLGame.h>

#include "LevelBlocks.h"



class BlockPool
{
	friend class LevelBlocks;

public:

	BlockPool(ASGE::Renderer * renderer);
	~BlockPool() = default;

	void blockPoolInit(ASGE::Renderer* renderer);

	LevelBlocks* getNewRWBlock();
	LevelBlocks* getNewDWBlock();


private:

	std::vector<std::unique_ptr<LevelBlocks>> rw_block_pool;
	std::vector<std::unique_ptr<LevelBlocks>> dw_block_pool;

};