#include <Engine\InputEvents.h>

#include "BirdmanTheGame.h"
#include "GameFont.h"

namespace {
	const float BACKGROUND_LAYER = 0.0f;
	const float FOREGROUND_LAYER = 1.0f;
};

BirdmanTheGame::~BirdmanTheGame()
{
	this->inputs->unregisterCallback(key_handler_id);
	LoadedGameFont::loaded_fonts.clear();
}

bool BirdmanTheGame::init()
{
	game_width = 1280;
	game_height = 720;

	if (!initAPI(ASGE::Renderer::WindowMode::WINDOWED))
	{
		return false;
	}

	renderer->setWindowTitle("Realm Shifter");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::BACK_TO_FRONT);
	toggleFPS();

	this->inputs->use_threads = false;

	key_handler_id = this->inputs->addCallbackFnc(
		ASGE::EventType::E_KEY, &BirdmanTheGame::keyHandler, this);

	LoadedGameFont::loaded_fonts.reserve(5);

	backdrop = renderer->createUniqueSprite();
	if (!backdrop->loadTexture(".\\Resources\\Textures\\Backdrop.jpg"))
	{
		return false;
	}

	//----------------------------- OUR STUFF GOES BELOW HERE ---------------------------

	scene_manager = std::make_unique<SceneManager>();
	state_machine = std::make_unique<StateMachine>();
	block_pool = std::make_unique<BlockPool>(renderer.get());

	player = std::make_unique<Player>(renderer.get());
	player_node.node_game_object = player.get();
	player_node.z_order = 1;

	Level1();


	scene_manager->addNodeToScene(test_scene, player_node);
	

	return true;
}

void BirdmanTheGame::update(const ASGE::GameTime& ms)
{
	player->update(ms);


}

void BirdmanTheGame::render(const ASGE::GameTime& ms)
{
	switch (overall_state)
	{
	case OverallState::MENU:
	{

		break;
	}

	case OverallState::PAUSE:
	{
		break;
	}

	case OverallState::GAMEPLAY:
	{
		//default start state
		switch (world_type_state)
		{
		case WorldTypeState::REALWORLD:
		{
			scene_manager->renderScene(level1_RW, renderer.get());
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			scene_manager->renderScene(level1_DW, renderer.get());
			break;
		}
		break;
		}
	}
	case OverallState::GAMEOVER:
	{
		break;
	}
	}
	
}

void BirdmanTheGame::keyHandler(const ASGE::SharedEventData data)
{
	const ASGE::KeyEvent* key_event =
		static_cast<const ASGE::KeyEvent*>(data.get());

	auto key = key_event->key;
	auto action = key_event->action;

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		state_machine->passInInputToStateMachine(key);
	}

	if (action == ASGE::KEYS::KEY_RELEASED && move_state != PlayerMoveState::NONE)
	{
		if (key == ASGE::KEYS::KEY_LEFT || key == ASGE::KEYS::KEY_RIGHT)
		{
			move_state = PlayerMoveState::NONE;
		}
	}
}



void BirdmanTheGame::Level1()
{
	block_node1.node_game_object = block_pool->getNewRWBlock();
	block_node1.node_game_object->getObjectSprite()->xPos(200);
	block_node1.node_game_object->getObjectSprite()->yPos(620);
	block_node1.z_order = 2;

	block_node2.node_game_object = block_pool->getNewDWBlock();
	block_node2.node_game_object->getObjectSprite()->xPos(350);
	block_node2.node_game_object->getObjectSprite()->yPos(620);
	block_node2.z_order = 2;

	block_node3.node_game_object = block_pool->getNewRWBlock();
	block_node3.node_game_object->getObjectSprite()->xPos(500);
	block_node3.node_game_object->getObjectSprite()->yPos(520);
	block_node3.node_game_object->getObjectSprite()->width(50);
	block_node3.z_order = 2;

	block_node4.node_game_object = block_pool->getNewDWBlock();
	block_node4.node_game_object->getObjectSprite()->xPos(600);
	block_node4.node_game_object->getObjectSprite()->yPos(420);
	block_node4.node_game_object->getObjectSprite()->width(50);
	block_node4.z_order = 2;

	block_node5.node_game_object = block_pool->getNewRWBlock();
	block_node5.node_game_object->getObjectSprite()->xPos(580);
	block_node5.node_game_object->getObjectSprite()->yPos(320);
	block_node5.node_game_object->getObjectSprite()->width(500);
	block_node5.z_order = 2;

	block_node6.node_game_object = block_pool->getNewRWBlock();
	block_node6.node_game_object->getObjectSprite()->xPos(280);
	block_node6.node_game_object->getObjectSprite()->yPos(320);

	block_node6.z_order = 2;

	block_node7.node_game_object = block_pool->getNewDWBlock();
	block_node7.node_game_object->getObjectSprite()->xPos(200);
	block_node7.node_game_object->getObjectSprite()->yPos(220);

	block_node7.z_order = 2;

	block_node8.node_game_object = block_pool->getNewRWBlock();
	block_node8.node_game_object->getObjectSprite()->xPos(830);
	block_node8.node_game_object->getObjectSprite()->yPos(120);

	block_node8.z_order = 2;

	block_node9.node_game_object = block_pool->getNewRWBlock();
	block_node9.node_game_object->getObjectSprite()->xPos(1080);
	block_node9.node_game_object->getObjectSprite()->yPos(220);

	block_node9.z_order = 2;



	scene_manager->addNodeToScene(level1_RW, player_node);
	scene_manager->addNodeToScene(level1_DW, player_node);


	scene_manager->addNodeToScene(level1_RW, block_node1);
	scene_manager->addNodeToScene(level1_DW, block_node2);
	scene_manager->addNodeToScene(level1_RW, block_node3);
	scene_manager->addNodeToScene(level1_DW, block_node4);
	scene_manager->addNodeToScene(level1_RW, block_node5);
	scene_manager->addNodeToScene(level1_RW, block_node6);
	scene_manager->addNodeToScene(level1_DW, block_node7);
	scene_manager->addNodeToScene(level1_RW, block_node8);
	scene_manager->addNodeToScene(level1_RW, block_node9);


}