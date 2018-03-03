#pragma once
#include "GameObject.h"

enum class BackgroundTypes
{
	DREAM_WORLD,
	REAL_WORLD
};

class Backgrounds : public GameObject
{
public:
	Backgrounds(ASGE::Renderer* renderer, BackgroundTypes type);
	~Backgrounds() = default;

	void init(ASGE::Renderer* renderer) override;
	void update(const ASGE::GameTime& ms) override;

private:
	Backgrounds() = default;
	BackgroundTypes background_type;
};