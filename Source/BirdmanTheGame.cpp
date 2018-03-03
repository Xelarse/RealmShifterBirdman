#include <Engine\InputEvents.h>
#include <irrKlang.h>

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
	//audio_engine->stopAllSounds();
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


	//initAudioEngine();
	initiliseMenus(renderer.get());
	Level1();
	Level2();
	//Level3();
	
	return true;
}

//bool BirdmanTheGame::initAudioEngine()
//{
//	using namespace irrklang;
//	audio_engine.reset(createIrrKlangDevice());
//	
//	if (!audio_engine)
//	{
//		return false;
//	}
//	return true;
//}

void BirdmanTheGame::update(const ASGE::GameTime& ms)
{
	switch (overall_state)
	{
		case OverallState::GAMEPLAY:
		{
			player->update(ms);

			levelSelection();

			break;
		}

		case OverallState::EXIT:
		{
			exit = true;
		}
	}
	



}



void BirdmanTheGame::render(const ASGE::GameTime& ms)
{
	switch (overall_state)
	{
		case OverallState::MENU:
		{
			renderMenuState(renderer.get());
			break;
		}

		case OverallState::PAUSE:
		{
			renderPauseState(renderer.get());
			break;
		}

		case OverallState::GAMEPLAY:
		{
			renderGameState(renderer.get());
			break;
		}
		case OverallState::GAMEOVER:
		{
			renderGameOverState(renderer.get());
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


void BirdmanTheGame::initiliseMenus(ASGE::Renderer* renderer)
{
	//Main menu init
	menu_scene.scene_renderables.reserve(3);

	background_sprite = renderer->createUniqueSprite();
	background_sprite->loadTexture("..\\..\\Resources\\mainMenuBackground.jpg");
	menu_background_node.node_sprite = background_sprite.get();
	menu_background_node.z_order = 1;
	scene_manager->addNodeToScene(menu_scene, menu_background_node);

	menu_text_node.node_string = "Press enter to start! \n \n Press left or right to cycle through the menu";
	menu_text_node.string_x = 300;
	menu_text_node.string_y = 600;
	menu_text_node.string_scale = 1.5;
	menu_text_node.string_colour = ASGE::COLOURS::LIGHTGREEN;
	scene_manager->addNodeToScene(menu_scene, menu_text_node);

	//Pause menu init
	pause_scene.scene_renderables.reserve(3);

	pause_background = renderer->createUniqueSprite();
	pause_background->loadTexture("..\\..\\Resources\\pauseBackground.jpg");
	pause_background_node.node_sprite = pause_background.get();
	pause_background_node.z_order = 2;
	scene_manager->addNodeToScene(pause_scene, pause_background_node);

	pause_text_node.node_string = "Press enter to return to menu \n \n Press left or right to cycle through the menu";
	pause_text_node.string_x = 300;
	pause_text_node.string_y = 360;
	pause_text_node.string_scale = 1.5;
	pause_text_node.string_colour = ASGE::COLOURS::LIGHTGREEN;
	pause_text_node.z_order = 1;
	scene_manager->addNodeToScene(pause_scene, pause_text_node);
}

void BirdmanTheGame::levelSelection()
{
	if (level_select == LevelSelect::LEVEL1)
	{

		if (world_type_state == WorldTypeState::REALWORLD)
		{
			for (auto& node : level1_RW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}

		else if (world_type_state == WorldTypeState::DREAMWORLD)
		{
			for (auto& node : level1_DW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}
	}
	else if (level_select == LevelSelect::LEVEL2)
	{

		if (world_type_state == WorldTypeState::REALWORLD)
		{
			for (auto& node : level2_RW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}

		else if (world_type_state == WorldTypeState::DREAMWORLD)
		{
			for (auto& node : level2_DW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}
	}
	else if (level_select == LevelSelect::LEVEL3)
	{

		if (world_type_state == WorldTypeState::REALWORLD)
		{
			for (auto& node : level3_RW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}

		else if (world_type_state == WorldTypeState::DREAMWORLD)
		{
			for (auto& node : level3_DW.scene_renderables)
			{
				landOnBlockCheck(player.get(), node.node_game_object);
			}
		}
	}
}

bool BirdmanTheGame::isSpriteColliding(Player* player, GameObject * blocks)
{
	bool x_collide = false;
	bool y_collide = false;

	if (player->getSpriteX() <= (blocks->getSpriteMaxX() - collider_tolerance)
		&& player->getSpriteMaxX() >= (blocks->getSpriteX() + collider_tolerance))
	{
		x_collide = true;
	}

	if (player->getSpriteY() <= (blocks->getSpriteMaxY() - collider_tolerance)
		&& player->getSpriteMaxY() >= (blocks->getSpriteY() + collider_tolerance))
	{
		y_collide = true;
	}


	if (x_collide && y_collide)
	{
		x_collide = false;
		y_collide = false;

		if (blocks->getIsEndBlock() == true)
		{
			switch (level_select)
			{
			case LevelSelect::LEVEL1:
				{
					level_select = LevelSelect::LEVEL2;
					break;
				}
			case LevelSelect::LEVEL2:
				{
					level_select = LevelSelect::LEVEL3;
					break;
				}
			case LevelSelect::LEVEL3:
				{
					level_select = LevelSelect::LEVEL1;
					break;
				}
			}
		}
		return true;
	}

	return false;
}

void BirdmanTheGame::landOnBlockCheck(Player* player, GameObject* block)
{
	if (isSpriteColliding(player, block))
	{
		if (player->getSpriteMaxY() <= block->getSpriteY() - 1|| player->getSpriteMaxY() >= block->getSpriteY() + 1)
		{
			jump_state = PlayerJumpState::JUMP_OFF;
			player->setIsJumping(false);
			player->yVelocity(0);
		}

		else
		{
			move_state = PlayerMoveState::NONE;
		}
	}
}

void BirdmanTheGame::renderGameState(ASGE::Renderer * renderer)
{
	if (level_select == LevelSelect::LEVEL1)
	{

		switch (world_type_state)
		{
		case WorldTypeState::REALWORLD:
		{
			scene_manager->renderScene(level1_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			scene_manager->renderScene(level1_DW, renderer);
			break;
		}
		}
	}
	else if (level_select == LevelSelect::LEVEL2)
	{

		switch (world_type_state)
		{
		case WorldTypeState::REALWORLD:
		{
			scene_manager->renderScene(level2_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			scene_manager->renderScene(level2_DW, renderer);
			break;
		}
		}
	}
	else if (level_select == LevelSelect::LEVEL3)
	{

		switch (world_type_state)
		{
		case WorldTypeState::REALWORLD:
		{
			scene_manager->renderScene(level3_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			scene_manager->renderScene(level3_DW, renderer);
			break;
		}
		}
	}

	renderer->renderSprite(*player->getObjectSprite());
}

void BirdmanTheGame::renderPauseState(ASGE::Renderer * renderer)
{
	if (pause_state == PauseState::HOVER_CONTINUE)
	{
		pause_scene.scene_renderables.pop_back();
		pause_text_node.node_string = "Hit enter to jump back into the game! \n \n Press left or right to cycle through the menu";
		scene_manager->addNodeToScene(pause_scene, pause_text_node);
	}

	else if (pause_state == PauseState::HOVER_QUIT)
	{
		pause_scene.scene_renderables.pop_back();
		pause_text_node.node_string = "Hit enter to exit! \n \n Press left or right to cycle through the menu";
		scene_manager->addNodeToScene(pause_scene, pause_text_node);
	}


	scene_manager->renderScene(pause_scene, renderer);
}

void BirdmanTheGame::renderMenuState(ASGE::Renderer * renderer)
{
	if (menu_state == MenuState::HOVER_START)
	{
		menu_scene.scene_renderables.pop_back();
		menu_text_node.node_string = "Press enter to start! \n \n Press left or right to cycle through the menu";
		scene_manager->addNodeToScene(menu_scene, menu_text_node);
	}

	else if (menu_state == MenuState::HOVER_EXIT)
	{
		menu_scene.scene_renderables.pop_back();
		menu_text_node.node_string = "Press enter to exit! \n \n Press left or right to cycle through the menu";
		scene_manager->addNodeToScene(menu_scene, menu_text_node);
	}


	scene_manager->renderScene(menu_scene, renderer);
}

void BirdmanTheGame::renderGameOverState(ASGE::Renderer * renderer)
{
}


void BirdmanTheGame::Level1()
{
	lv1_block_node1.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node1.node_game_object->getObjectSprite()->xPos(200);
	lv1_block_node1.node_game_object->getObjectSprite()->yPos(620);
	lv1_block_node1.z_order = 2;

	lv1_block_node2.node_game_object = block_pool->getNewDWBlock();
	lv1_block_node2.node_game_object->getObjectSprite()->xPos(350);
	lv1_block_node2.node_game_object->getObjectSprite()->yPos(620);
	lv1_block_node2.z_order = 2;

	lv1_block_node3.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node3.node_game_object->getObjectSprite()->xPos(500);
	lv1_block_node3.node_game_object->getObjectSprite()->yPos(520);
	lv1_block_node3.node_game_object->getObjectSprite()->width(50);
	lv1_block_node3.z_order = 2;

	lv1_block_node4.node_game_object = block_pool->getNewDWBlock();
	lv1_block_node4.node_game_object->getObjectSprite()->xPos(600);
	lv1_block_node4.node_game_object->getObjectSprite()->yPos(420);
	lv1_block_node4.node_game_object->getObjectSprite()->width(50);
	lv1_block_node4.z_order = 2;

	lv1_block_node5.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node5.node_game_object->getObjectSprite()->xPos(580);
	lv1_block_node5.node_game_object->getObjectSprite()->yPos(320);
	lv1_block_node5.node_game_object->getObjectSprite()->width(500);
	lv1_block_node5.z_order = 2;

	lv1_block_node6.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node6.node_game_object->getObjectSprite()->xPos(280);
	lv1_block_node6.node_game_object->getObjectSprite()->yPos(320);
	lv1_block_node6.z_order = 2;

	lv1_block_node7.node_game_object = block_pool->getNewDWBlock();
	lv1_block_node7.node_game_object->getObjectSprite()->xPos(200);
	lv1_block_node7.node_game_object->getObjectSprite()->yPos(220);
	lv1_block_node7.z_order = 2;

	lv1_block_node8.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node8.node_game_object->getObjectSprite()->xPos(830);
	lv1_block_node8.node_game_object->getObjectSprite()->yPos(120);
	lv1_block_node8.z_order = 2;

	lv1_block_node9.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node9.node_game_object->getObjectSprite()->xPos(1080);
	lv1_block_node9.node_game_object->getObjectSprite()->yPos(220);
	lv1_block_node9.node_game_object->setIsEndBlock(true);
	lv1_block_node9.z_order = 2;


	scene_manager->addNodeToScene(level1_RW, lv1_block_node1);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node2);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node3);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node4);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node5);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node6);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node7);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node8);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node9);
}

void BirdmanTheGame::Level2()
{
	lv2_block_node1.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node1.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node1.node_game_object->getObjectSprite()->yPos(620);
	lv2_block_node1.z_order = 2;

	lv2_block_node2.node_game_object = block_pool->getNewDWBlock();
	lv2_block_node2.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node2.node_game_object->getObjectSprite()->yPos(620);
	lv2_block_node2.z_order = 2;

	lv2_block_node3.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node3.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node3.node_game_object->getObjectSprite()->yPos(520);
	lv2_block_node3.node_game_object->getObjectSprite()->width(50);
	lv2_block_node3.z_order = 2;

	lv2_block_node4.node_game_object = block_pool->getNewDWBlock();
	lv2_block_node4.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node4.node_game_object->getObjectSprite()->yPos(420);
	lv2_block_node4.node_game_object->getObjectSprite()->width(50);
	lv2_block_node4.z_order = 2;

	lv2_block_node5.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node5.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node5.node_game_object->getObjectSprite()->yPos(320);
	lv2_block_node5.node_game_object->getObjectSprite()->width(500);
	lv2_block_node5.z_order = 2;

	lv2_block_node6.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node6.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node6.node_game_object->getObjectSprite()->yPos(320);
	lv2_block_node6.z_order = 2;

	lv2_block_node7.node_game_object = block_pool->getNewDWBlock();
	lv2_block_node7.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node7.node_game_object->getObjectSprite()->yPos(220);
	lv2_block_node7.z_order = 2;

	lv2_block_node8.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node8.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node8.node_game_object->getObjectSprite()->yPos(120);
	lv2_block_node8.z_order = 2;

	lv2_block_node9.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node9.node_game_object->getObjectSprite()->xPos(1);
	lv2_block_node9.node_game_object->getObjectSprite()->yPos(220);
	lv2_block_node9.node_game_object->setIsEndBlock(true);
	lv2_block_node9.z_order = 2;


	scene_manager->addNodeToScene(level2_RW, lv1_block_node1);
	scene_manager->addNodeToScene(level2_DW, lv1_block_node2);
	scene_manager->addNodeToScene(level2_RW, lv1_block_node3);
	scene_manager->addNodeToScene(level2_DW, lv1_block_node4);
	scene_manager->addNodeToScene(level2_RW, lv1_block_node5);
	scene_manager->addNodeToScene(level2_RW, lv1_block_node6);
	scene_manager->addNodeToScene(level2_DW, lv1_block_node7);
	scene_manager->addNodeToScene(level2_RW, lv1_block_node8);
	scene_manager->addNodeToScene(level2_RW, lv1_block_node9);
}

//void BirdmanTheGame::Level3()
//{
//	lv1_block_node19.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node19.node_game_object->getObjectSprite()->xPos(300);
//	lv1_block_node19.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node19.z_order = 2;
//
//	lv1_block_node20.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node20.node_game_object->getObjectSprite()->xPos(350);
//	lv1_block_node20.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node20.z_order = 2;
//
//	lv1_block_node21.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node21.node_game_object->getObjectSprite()->xPos(500);
//	lv1_block_node21.node_game_object->getObjectSprite()->yPos(520);
//	lv1_block_node21.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node21.z_order = 2;
//
//	lv1_block_node22.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node22.node_game_object->getObjectSprite()->xPos(600);
//	lv1_block_node22.node_game_object->getObjectSprite()->yPos(420);
//	lv1_block_node22.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node22.z_order = 2;
//
//	lv1_block_node23.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node23.node_game_object->getObjectSprite()->xPos(580);
//	lv1_block_node23.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node23.node_game_object->getObjectSprite()->width(500);
//	lv1_block_node23.z_order = 2;
//
//	lv1_block_node24.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node24.node_game_object->getObjectSprite()->xPos(280);
//	lv1_block_node24.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node24.z_order = 2;
//
//	lv1_block_node25.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node25.node_game_object->getObjectSprite()->xPos(200);
//	lv1_block_node25.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node25.z_order = 2;
//
//	lv1_block_node26.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node26.node_game_object->getObjectSprite()->xPos(830);
//	lv1_block_node26.node_game_object->getObjectSprite()->yPos(120);
//	lv1_block_node26.z_order = 2;
//
//	lv1_block_node27.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node27.node_game_object->getObjectSprite()->xPos(1080);
//	lv1_block_node27.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node27.z_order = 2;
//
//
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node19);
//	scene_manager->addNodeToScene(level3_DW, lv1_block_node20);
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node21);
//	scene_manager->addNodeToScene(level3_DW, lv1_block_node22);
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node23);
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node24);
//	scene_manager->addNodeToScene(level3_DW, lv1_block_node25);
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node26);
//	scene_manager->addNodeToScene(level3_RW, lv1_block_node27);
//}
