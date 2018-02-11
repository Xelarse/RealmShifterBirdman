#include "SceneManager.h"
#include <algorithm>

void SceneManager::clearScene(SCENE scene)
{
	scene.scene_renderables.clear();
}

void SceneManager::renderScene(SCENE scene, ASGE::Renderer * renderer)
{
	if (!scene.is_sorted)
	{
		std::sort(scene.scene_renderables.begin(),
			scene.scene_renderables.end(),
			[](const NODE& lhs, const NODE& rhs) {return lhs.z_order < rhs.z_order; });

		scene.is_sorted = true;
	}

	for (auto& node : scene.scene_renderables)
	{
		renderer->renderSprite(*node.node_game_object->getObjectSprite());
	}
}

void SceneManager::addNodeToScene(SCENE scene, NODE node)
{
	scene.scene_renderables.push_back(node);
}
