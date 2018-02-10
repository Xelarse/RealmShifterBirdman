#pragma once
#include <Engine\OGLGame.h>
#include <iostream>
#include <vector>

class SceneManager
{
	/*Used in a scene, add multiple nodes to a single scene, z_order must be between 0 - 4.
	when creating a sprite for use in node ensure you use a unique smart pointer!*/
	struct NODE
	{
		ASGE::Sprite* node_sprite = nullptr;
		int z_order = -1;
	};

	/*Used to render things into the game, input a Scene that is filled with nodes into the scene
	manager in order to render the items within*/
	struct SCENE
	{
		std::vector<NODE> scene_renderables;
		bool is_sorted = false;
	};



public:

	SceneManager() = default;
	~SceneManager() = default;

	void clearScene(SCENE scene);
	void renderScene(SCENE scene, ASGE::Renderer* renderer);
	void addNodeToScene(SCENE scene, NODE node);


private:





};
