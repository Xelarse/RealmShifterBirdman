#pragma once
#include <Engine\OGLGame.h>
#include <Engine\Sprite.h>
#include <irrKlang.h>
#include <iostream>
#include <fstream>


#include "SceneManager.h"
#include "StateMachine.h"
#include "Player.h"
#include "LevelBlocks.h"
#include "BlockPool.h"
#include "Backgrounds.h"

using namespace irrklang;

namespace ASGE {
	struct GameTime;
}
namespace irrKlang {
	class ISoundEngine;
}

/**
*  BirdmanTheGame is the main entrypoint into the game.
*  It is based on the ASGE framework and makes use of
*  the OGLGame class. This allows the rendering and
*  input initialisation to be handled easily and without
*  fuss. The game logic responsible for updating and
*  rendering the game starts here.
*/
class BirdmanTheGame 
	: public ASGE::OGLGame
{
public:


	
	/**
	*  Default constructor for game.
	*/
	BirdmanTheGame() = default;
	
	/**
	*  Destructor for game.
	*  Make sure to clean up any dynamically allocated
	*  memory inside the game's destructor. For example
	*  game fonts need to be deallocated.
	*/ 
	~BirdmanTheGame();

	/**
	*  The initialisation of the game.
	*  Both the game's initialisation and the API setup
	*  should be performed inside this function. Once the
	*  API is up and running the input system can register
	*  callback functions when certain events happen.
	*/ 
	virtual bool init() override;
	
private:
	/**
	*  The simulation for the game.
	*  The objects in the game need to updated or simulated
	*  over time. Use this function to decouple the render
	*  phases from the simulation.
	*  @param us The ms time between frames and running time
	*  @see GameTime
	*/
	virtual void update(const ASGE::GameTime& ms) override;
	
	/**
	*  The rendering of the game.
	*  This function gets called after the game world has
	*  been updated. Ensure all your objects are in a sane
	*  simulated state before calling this function.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void render(const ASGE::GameTime& ms) override;

	/**
	*  The key handling function for the game.
	*  Key inputs will be delivered and handled within this function.
	*  Make a decision whether to process the input immediately
	*  or whether to generate a queue of actions that are then
	*  processed at the beginning of the game update loop.
	*  @param data They key event and its related data.
	*  @see SharedEventData
	*/
	void keyHandler(const ASGE::SharedEventData data);


	//STUFF WE ADD GOES BELOW HERE FOR CLARITY //


	//bool initAudioEngine();

private:
	std::unique_ptr<ASGE::Sprite> backdrop = nullptr;
	int key_handler_id = -1;  /**< Input Callback ID. 
							       The callback ID assigned by the game engine. */

	//STUFF WE ADD GOES BELOW HERE FOR CLARITY //
	float high_score = 0;
	float game_timer = 0;
	void initHighScore();
	void saveHighScore();


	void initiliseMenus(ASGE::Renderer* renderer);
	void gameReset();


	void levelSelection();

	void Level1();
	void Level2();
	void Level3();


	bool isSpriteColliding(Player* player, GameObject* block);
	void landOnBlockCheck(Player* player, GameObject* block);

	void renderGameState(ASGE::Renderer* renderer);
	void renderPauseState(ASGE::Renderer* renderer);
	void renderMenuState(ASGE::Renderer* renderer);
	void renderGameOverState(ASGE::Renderer* renderer);

	float collider_tolerance = 15;
	bool off_block = true;

	std::unique_ptr<SceneManager> scene_manager = nullptr;
	std::unique_ptr<StateMachine> state_machine = nullptr;

	bool level_1_to_2 = false;
	bool level_2_to_3 = false;

	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<BlockPool> block_pool = nullptr;

	SceneManager::SCENE gameover_scene;
	SceneManager::NODE player_node;


	std::unique_ptr<Backgrounds> dream_background;
	std::unique_ptr<Backgrounds> real_background;

	SceneManager::NODE RW_background;
	SceneManager::NODE DW_background;

	//Level 1 scene stuff
	SceneManager::SCENE level1_DW;
	SceneManager::SCENE level1_RW;

	SceneManager::NODE lv1_block_node1;
	SceneManager::NODE lv1_block_node2;
	SceneManager::NODE lv1_block_node3;
	SceneManager::NODE lv1_block_node4;
	SceneManager::NODE lv1_block_node5;
	SceneManager::NODE lv1_block_node6;
	SceneManager::NODE lv1_block_node7;
	SceneManager::NODE lv1_block_node8;
	SceneManager::NODE lv1_block_node9;
	SceneManager::NODE lv1_block_node10;


	//Level 2 scene stuff
	SceneManager::SCENE level2_DW;
	SceneManager::SCENE level2_RW;

	SceneManager::NODE lv2_block_node1;
	SceneManager::NODE lv2_block_node2;
	SceneManager::NODE lv2_block_node3;
	SceneManager::NODE lv2_block_node4;
	SceneManager::NODE lv2_block_node5;
	SceneManager::NODE lv2_block_node6;
	SceneManager::NODE lv2_block_node7;
	SceneManager::NODE lv2_block_node8;
	SceneManager::NODE lv2_block_node9;
	SceneManager::NODE lv2_block_node10;



	//Level 3 scene stuff
	SceneManager::SCENE level3_DW;
	SceneManager::SCENE level3_RW;

	SceneManager::NODE lv3_block_node1;
	SceneManager::NODE lv3_block_node2;
	SceneManager::NODE lv3_block_node3;
	SceneManager::NODE lv3_block_node4;
	SceneManager::NODE lv3_block_node5;
	SceneManager::NODE lv3_block_node6;
	SceneManager::NODE lv3_block_node7;
	SceneManager::NODE lv3_block_node8;
	SceneManager::NODE lv3_block_node9;
	SceneManager::NODE lv3_block_node10;
	SceneManager::NODE lv3_block_node11;
	SceneManager::NODE lv3_block_node12;
	SceneManager::NODE lv3_block_node13;
	

	//Menu scene stuff
	SceneManager::SCENE menu_scene;
	SceneManager::NODE menu_background_node;
	SceneManager::NODE menu_text_node;
	std::unique_ptr<ASGE::Sprite> background_sprite;

	//Pause scene stuff
	SceneManager::SCENE pause_scene;
	SceneManager::NODE pause_background_node;
	SceneManager::NODE pause_text_node;
	std::unique_ptr<ASGE::Sprite> pause_background;
};

