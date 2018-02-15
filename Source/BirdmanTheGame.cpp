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

	player = std::make_unique<Player>();
	player->init(renderer.get());
	player_node.node_game_object = player.get();
	player_node.z_order = 1;

	block = std::make_unique<LevelBlocks>();
	block->init(renderer.get());
	block_node.node_game_object = block.get();
	block_node.z_order = 2;

	scene_manager->addNodeToScene(test_scene, player_node);
	scene_manager->addNodeToScene(test_scene, block_node);

	return true;
}

void BirdmanTheGame::update(const ASGE::GameTime& ms)
{

}

void BirdmanTheGame::render(const ASGE::GameTime& ms)
{
	switch (overall_state)
	{
		case OverallState::MENU:
		{
			//default start state
			scene_manager->renderScene(test_scene, renderer.get());
			break;
		}

		case OverallState::PAUSE:
		{
			break;
		}

		case OverallState::GAMEPLAY:
		{
			break;
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
}
