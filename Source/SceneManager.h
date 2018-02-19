#pragma once
#include <Engine\OGLGame.h>
#include <iostream>
#include <vector>

#include "GameObject.h"

class SceneManager
{

	friend class BirdmanTheGame;

	/*Used in a scene, add multiple nodes to a single scene, z_order must be between 0 - 4.*/
	struct NODE
	{
		GameObject* node_game_object = nullptr;

		//The closer the number to 0 the higher it will be rendered into the scene
		int z_order = -1;
	};

	/*Used to render things into the game, input a Scene that is filled with nodes into the scene
	manager in order to render the items within*/
	struct SCENE
	{
		std::vector<NODE> scene_renderables;
	};



public:

	SceneManager() = default;
	~SceneManager() = default;

	void clearScene(SCENE& scene);
	void renderScene(SCENE& scene, ASGE::Renderer* renderer);
	void addNodeToScene(SCENE& scene, NODE& node);


private:

};
