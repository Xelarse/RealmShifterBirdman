#pragma once
#include "BlockPool.h"

BlockPool::BlockPool(ASGE::Renderer * renderer)
{
	rw_block_pool.reserve(100);
	dw_block_pool.reserve(100);

	blockPoolInit(renderer);
}

LevelBlocks* BlockPool::getNewDWBlock()
{
	for (auto& dw_block : dw_block_pool)
	{
		if (!dw_block.get()->getIsUsed())
		{
			dw_block.get()->setIsUsed(true);
			return dw_block.get();
		}
	}
}

void BlockPool::blockPoolInit(ASGE::Renderer * renderer)
{
	for (int i = 0; i < rw_block_pool.capacity(); i++)
	{
		std::unique_ptr<LevelBlocks> new_block = nullptr;
		new_block = std::make_unique<LevelBlocks>(renderer, BlockTypes::REAL_WORLD, 200, 50);
		rw_block_pool.push_back(std::move(new_block));
	}

	for (int i = 0; i < dw_block_pool.capacity(); i++)
	{
		std::unique_ptr<LevelBlocks> new_block = nullptr;
		new_block = std::make_unique<LevelBlocks>(renderer, BlockTypes::DREAM_WORLD, 200, 50);
		dw_block_pool.push_back(std::move(new_block));
	}
}

LevelBlocks* BlockPool::getNewRWBlock()
{
	for (auto& rw_block : rw_block_pool)
	{
		if (!rw_block.get()->getIsUsed())
		{
			rw_block.get()->setIsUsed(true);
			return rw_block.get();
		}
	}
}
