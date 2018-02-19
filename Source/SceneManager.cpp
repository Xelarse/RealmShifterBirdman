#include "SceneManager.h"

void SceneManager::clearScene(SCENE& scene)
{
	scene.scene_renderables.clear();
}

void SceneManager::renderScene(SCENE& scene, ASGE::Renderer * renderer)
{
	for (auto& node : scene.scene_renderables)
	{
		renderer->renderSprite(*node.node_game_object->getObjectSprite(), node.z_order);
	}
}

void SceneManager::addNodeToScene(SCENE& scene, NODE& node)
{
	scene.scene_renderables.push_back(node);
}
