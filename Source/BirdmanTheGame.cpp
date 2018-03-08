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

	dream_background = std::make_unique<Backgrounds>(renderer.get(), BackgroundTypes::DREAM_WORLD);
	real_background = std::make_unique<Backgrounds>(renderer.get(), BackgroundTypes::REAL_WORLD);

	initHighScore();

	scene_manager = std::make_unique<SceneManager>();
	state_machine = std::make_unique<StateMachine>();
	block_pool = std::make_unique<BlockPool>(renderer.get());

	player = std::make_unique<Player>(renderer.get());
	player_node.node_game_object = player.get();
	player_node.z_order = 1;

	initiliseMenus(renderer.get());
	Level1();
	Level2();
	Level3();
	
	return true;
}

void BirdmanTheGame::update(const ASGE::GameTime& ms)
{
	switch (overall_state)
	{
		case OverallState::GAMEPLAY:
		{
			player->update(ms);
			levelSelection();

			game_timer += ms.delta_time.count() / 1000;
			break;
		}

		case OverallState::GAMEOVER:
		{
			saveHighScore();
			break;
		}

		case OverallState::MENU:
		{
			gameReset();
			break;
		}

		case OverallState::EXIT:
		{
			exit = true;
			break;
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

void BirdmanTheGame::initHighScore()
{
	std::ifstream InputFile("..\\..\\Resources\\Score.txt");
	if (InputFile.is_open())
	{
		InputFile >> high_score;
		InputFile.close();
	}
}

void BirdmanTheGame::saveHighScore()
{
	std::ofstream OutputFile("..\\..\\Resources\\Score.txt");
	if (game_timer < high_score)
	{
		OutputFile << game_timer;
		high_score = game_timer;
	}

	else
	{
		OutputFile << high_score;
	}

	OutputFile.close();
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

void BirdmanTheGame::gameReset()
{
	player->getObjectSprite()->xPos(-10);
	player->getObjectSprite()->yPos(520);
	level_select = LevelSelect::LEVEL1;
	game_timer = 0;

	if (!state_machine->isGameActionStateDefault())
	{
		state_machine->resetGameActionState();
	}
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
		if (level_1_to_2)
		{
			move_state = PlayerMoveState::NONE;
			player->getObjectSprite()->xPos(30);
			player->getObjectSprite()->yPos(50);
			level_1_to_2 = false;
		}

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
		if (level_2_to_3)
		{
			move_state = PlayerMoveState::NONE;
			player->getObjectSprite()->xPos(30);
			player->getObjectSprite()->yPos(50);
			level_2_to_3 = false;
		}

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
					level_1_to_2 = true;
					break;
				}
			case LevelSelect::LEVEL2:
				{
					level_select = LevelSelect::LEVEL3;
					level_2_to_3 = true;
					break;
				}
			case LevelSelect::LEVEL3:
				{
				overall_state = OverallState::GAMEOVER;
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
	float jump_tollerance = 20;

	if (isSpriteColliding(player, block))
	{
		if (player->getSpriteMaxY() > block->getSpriteY() - jump_tollerance && 
			player->getSpriteMaxY() < block->getSpriteY() + jump_tollerance)
		{
			jump_state = PlayerJumpState::JUMP_OFF;
			player->setIsJumping(false);
			player->yVelocity(0);
			off_block = false;
		}

		else
		{
			off_block = true;
		}

		if (player->getSpriteX() <= (block->getSpriteMaxX() - collider_tolerance) ||
			player->getSpriteMaxX() >= (block->getSpriteX() + collider_tolerance))
		{
			if (off_block)
			{
				if (player->getSpriteOriginX() < block->getSpriteOriginX())
				{
					float new_pos = block->getObjectSprite()->xPos() - player->getObjectSprite()->width();
					move_state = PlayerMoveState::NONE;
					player->getObjectSprite()->xPos(new_pos);
				}

				else if (player->getSpriteOriginX() > block->getSpriteOriginX())
				{
					float new_pos = block->getSpriteMaxX();
					move_state = PlayerMoveState::NONE;
					player->getObjectSprite()->xPos(new_pos);
				}
			}
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
			renderer->renderSprite(*RW_background.node_game_object->getObjectSprite(), RW_background.z_order);
			scene_manager->renderScene(level1_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			renderer->renderSprite(*DW_background.node_game_object->getObjectSprite(), RW_background.z_order);
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
			renderer->renderSprite(*RW_background.node_game_object->getObjectSprite(), RW_background.z_order);
			scene_manager->renderScene(level2_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			renderer->renderSprite(*DW_background.node_game_object->getObjectSprite(), RW_background.z_order);
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
			renderer->renderSprite(*RW_background.node_game_object->getObjectSprite(), RW_background.z_order);
			scene_manager->renderScene(level3_RW, renderer);
			break;
		}
		case WorldTypeState::DREAMWORLD:
		{
			renderer->renderSprite(*DW_background.node_game_object->getObjectSprite(), RW_background.z_order);
			scene_manager->renderScene(level3_DW, renderer);
			break;
		}
		}
	}

	std::string score = "Current Time: " + std::to_string(int(game_timer));
	renderer->renderText(score, 500, 50, 2.0, ASGE::COLOURS::GREEN, -1);
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
		pause_text_node.node_string = "Hit enter to go back to menu! \n \n Press left or right to cycle through the menu";
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
	std::string score = "Highscore : " + std::to_string(int(high_score));
	renderer->renderText(score, 10, 50, 2.0, ASGE::COLOURS::GREEN, -1);
}

void BirdmanTheGame::renderGameOverState(ASGE::Renderer * renderer)
{
	renderer->renderSprite(*pause_background.get(), 3);
	
	std::string score = "You finished in :" + std::to_string(int(game_timer));

	renderer->renderText(score, 500, 400, 2.0, ASGE::COLOURS::GREEN, -1);

	if (game_timer < high_score)
	{
		renderer->renderText("NEW HIGH SCORE!", 500, 440, 2.0, ASGE::COLOURS::GREEN, -1);
	}

	renderer->renderText("Press enter to go back to the main menu", 400, 480, 2.0, ASGE::COLOURS::GREEN, -1);
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
	lv1_block_node8.node_game_object->getObjectSprite()->xPos(530);
	lv1_block_node8.node_game_object->getObjectSprite()->yPos(120);
	lv1_block_node8.z_order = 2;

	lv1_block_node9.node_game_object = block_pool->getNewRWBlock();
	lv1_block_node9.node_game_object->getObjectSprite()->xPos(1060);
	lv1_block_node9.node_game_object->getObjectSprite()->yPos(220);
	lv1_block_node9.z_order = 2;

	lv1_block_node10.node_game_object = block_pool->getNewRWBlock(); //door
	lv1_block_node10.node_game_object->getObjectSprite()->xPos(1210);
	lv1_block_node10.node_game_object->getObjectSprite()->yPos(170);
	lv1_block_node10.node_game_object->getObjectSprite()->width(50);
	lv1_block_node10.node_game_object->getObjectSprite()->height(100);
	lv1_block_node10.node_game_object->setIsEndBlock(true);
	lv1_block_node10.z_order = 2;

	scene_manager->addNodeToScene(level1_RW, lv1_block_node1);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node2);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node3);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node4);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node5);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node6);
	scene_manager->addNodeToScene(level1_DW, lv1_block_node7);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node8);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node9);
	scene_manager->addNodeToScene(level1_RW, lv1_block_node10);
}

void BirdmanTheGame::Level2()
{
	lv2_block_node1.node_game_object = block_pool->getNewRWBlock(); //start
	lv2_block_node1.node_game_object->getObjectSprite()->xPos(0);
	lv2_block_node1.node_game_object->getObjectSprite()->yPos(170);
	lv2_block_node1.node_game_object->getObjectSprite()->width(100);
	lv2_block_node1.z_order = 2;

	lv2_block_node2.node_game_object = block_pool->getNewDWBlock(); //wall
	lv2_block_node2.node_game_object->getObjectSprite()->xPos(200);
	lv2_block_node2.node_game_object->getObjectSprite()->yPos(0);
	lv2_block_node2.node_game_object->getObjectSprite()->height(600);
	lv2_block_node2.node_game_object->getObjectSprite()->width(50);
	lv2_block_node2.z_order = 2;

	lv2_block_node3.node_game_object = block_pool->getNewRWBlock(); //wall
	lv2_block_node3.node_game_object->getObjectSprite()->xPos(200);
	lv2_block_node3.node_game_object->getObjectSprite()->yPos(0);
	lv2_block_node3.node_game_object->getObjectSprite()->width(50);
	lv2_block_node3.node_game_object->getObjectSprite()->height(600);
	lv2_block_node3.z_order = 2;

	lv2_block_node4.node_game_object = block_pool->getNewDWBlock(); // lowest DW block
	lv2_block_node4.node_game_object->getObjectSprite()->xPos(850);
	lv2_block_node4.node_game_object->getObjectSprite()->yPos(620);
	lv2_block_node4.node_game_object->getObjectSprite()->width(50);
	lv2_block_node4.z_order = 2;

	lv2_block_node5.node_game_object = block_pool->getNewRWBlock(); 
	lv2_block_node5.node_game_object->getObjectSprite()->xPos(1180);
	lv2_block_node5.node_game_object->getObjectSprite()->yPos(420);
	lv2_block_node5.z_order = 2;

	lv2_block_node6.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node6.node_game_object->getObjectSprite()->xPos(700);
	lv2_block_node6.node_game_object->getObjectSprite()->yPos(320);
	lv2_block_node6.z_order = 2;

	lv2_block_node7.node_game_object = block_pool->getNewDWBlock();
	lv2_block_node7.node_game_object->getObjectSprite()->xPos(400);
	lv2_block_node7.node_game_object->getObjectSprite()->yPos(420);
	lv2_block_node7.z_order = 2;

	lv2_block_node8.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node8.node_game_object->getObjectSprite()->xPos(500);
	lv2_block_node8.node_game_object->getObjectSprite()->yPos(400);
	lv2_block_node8.z_order = 2;

	lv2_block_node9.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node9.node_game_object->getObjectSprite()->xPos(1250);
	lv2_block_node9.node_game_object->getObjectSprite()->yPos(370);
	lv2_block_node9.node_game_object->getObjectSprite()->height(100);
	lv2_block_node9.node_game_object->getObjectSprite()->width(50);
	lv2_block_node9.node_game_object->setIsEndBlock(true);
	lv2_block_node9.z_order = 2;

	lv2_block_node10.node_game_object = block_pool->getNewRWBlock();
	lv2_block_node10.node_game_object->getObjectSprite()->xPos(600);
	lv2_block_node10.node_game_object->getObjectSprite()->yPos(500);
	lv2_block_node9.z_order = 2;

	scene_manager->addNodeToScene(level2_RW, lv2_block_node1);
	scene_manager->addNodeToScene(level2_DW, lv2_block_node2);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node3);
	scene_manager->addNodeToScene(level2_DW, lv2_block_node4);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node5);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node6);
	scene_manager->addNodeToScene(level2_DW, lv2_block_node7);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node8);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node9);
	scene_manager->addNodeToScene(level2_RW, lv2_block_node10);
}

void BirdmanTheGame::Level3()
{
	// new shit
	DW_background.node_game_object = dream_background.get();
	DW_background.z_order = 3;

	RW_background.node_game_object = real_background.get();
	RW_background.z_order = 3;

	lv3_block_node1.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node1.node_game_object->getObjectSprite()->xPos(1180);
	lv3_block_node1.node_game_object->getObjectSprite()->yPos(620);
	lv3_block_node1.z_order = 2;

	lv3_block_node2.node_game_object = block_pool->getNewDWBlock();
	lv3_block_node2.node_game_object->getObjectSprite()->xPos(350);
	lv3_block_node2.node_game_object->getObjectSprite()->yPos(620);
	lv3_block_node2.z_order = 2;

	lv3_block_node3.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node3.node_game_object->getObjectSprite()->xPos(500);
	lv3_block_node3.node_game_object->getObjectSprite()->yPos(520);
	lv3_block_node3.node_game_object->getObjectSprite()->width(50);
	lv3_block_node3.z_order = 2;

	lv3_block_node4.node_game_object = block_pool->getNewDWBlock();
	lv3_block_node4.node_game_object->getObjectSprite()->xPos(600);
	lv3_block_node4.node_game_object->getObjectSprite()->yPos(420);
	lv3_block_node4.node_game_object->getObjectSprite()->width(50);
	lv3_block_node4.z_order = 2;

	lv3_block_node5.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node5.node_game_object->getObjectSprite()->xPos(580);
	lv3_block_node5.node_game_object->getObjectSprite()->yPos(320);
	lv3_block_node5.node_game_object->getObjectSprite()->width(500);
	lv3_block_node5.z_order = 2;

	lv3_block_node6.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node6.node_game_object->getObjectSprite()->xPos(280);
	lv3_block_node6.node_game_object->getObjectSprite()->yPos(320);
	lv3_block_node6.z_order = 2;

	lv3_block_node7.node_game_object = block_pool->getNewDWBlock();
	lv3_block_node7.node_game_object->getObjectSprite()->xPos(200);
	lv3_block_node7.node_game_object->getObjectSprite()->yPos(220);
	lv3_block_node7.z_order = 2;

	lv3_block_node8.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node8.node_game_object->getObjectSprite()->xPos(830);
	lv3_block_node8.node_game_object->getObjectSprite()->yPos(120);
	lv3_block_node8.node_game_object->getObjectSprite()->width(100);
	lv3_block_node8.z_order = 2;

	lv3_block_node9.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node9.node_game_object->getObjectSprite()->xPos(1080);
	lv3_block_node9.node_game_object->getObjectSprite()->yPos(220);
	lv3_block_node9.z_order = 2;

	lv3_block_node10.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node10.node_game_object->getObjectSprite()->xPos(830);
	lv3_block_node10.node_game_object->getObjectSprite()->yPos(70);
	lv3_block_node10.node_game_object->getObjectSprite()->height(100);
	lv3_block_node10.node_game_object->getObjectSprite()->width(50);
	lv3_block_node10.node_game_object->setIsEndBlock(true);
	lv3_block_node10.z_order = 2;

	lv3_block_node11.node_game_object = block_pool->getNewRWBlock();
	lv3_block_node11.node_game_object->getObjectSprite()->xPos(0);
	lv3_block_node11.node_game_object->getObjectSprite()->yPos(170);
	lv3_block_node11.node_game_object->getObjectSprite()->width(100);
	lv3_block_node11.z_order = 2;

	lv3_block_node12.node_game_object = block_pool->getNewDWBlock(); //wall
	lv3_block_node12.node_game_object->getObjectSprite()->xPos(200);
	lv3_block_node12.node_game_object->getObjectSprite()->yPos(0);
	lv3_block_node12.node_game_object->getObjectSprite()->height(600);
	lv3_block_node12.node_game_object->getObjectSprite()->width(50);
	lv3_block_node12.z_order = 2;

	lv3_block_node13.node_game_object = block_pool->getNewRWBlock(); //wall
	lv3_block_node13.node_game_object->getObjectSprite()->xPos(200);
	lv3_block_node13.node_game_object->getObjectSprite()->yPos(0);
	lv3_block_node13.node_game_object->getObjectSprite()->width(50);
	lv3_block_node13.node_game_object->getObjectSprite()->height(600);
	lv3_block_node13.z_order = 2;

	scene_manager->addNodeToScene(level3_RW, lv3_block_node1);
	scene_manager->addNodeToScene(level3_DW, lv3_block_node2);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node3);
	scene_manager->addNodeToScene(level3_DW, lv3_block_node4);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node5);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node6);
	scene_manager->addNodeToScene(level3_DW, lv3_block_node7);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node8);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node9);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node10);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node11);
	scene_manager->addNodeToScene(level3_DW, lv3_block_node12);
	scene_manager->addNodeToScene(level3_RW, lv3_block_node13);
}
