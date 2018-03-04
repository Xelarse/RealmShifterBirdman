#include "SceneManager.h"

void SceneManager::clearScene(SCENE& scene)
{
	scene.scene_renderables.clear();
}

void SceneManager::renderScene(SCENE& scene, ASGE::Renderer * renderer)
{
	for (auto& node : scene.scene_renderables)
	{
		if (node.node_game_object != nullptr)
		{
			renderer->renderSprite(*node.node_game_object->getObjectSprite(), node.z_order);
		}

		else if (node.node_sprite != nullptr)
		{
			renderer->renderSprite(*node.node_sprite, node.z_order);
		}

		else if (node.node_string != "")
		{
			renderer->renderText(node.node_string, node.string_x, node.string_y, node.string_scale, node.string_colour, node.z_order);
		}
	}
}

void SceneManager::addNodeToScene(SCENE& scene, NODE& node)
{
	scene.scene_renderables.push_back(node);
}
