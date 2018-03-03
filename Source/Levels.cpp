//#include "Levels.h"
//
//Levels::~Levels()
//{
//}
//
//void Levels::initLevel1()
//{
//	lv1_block_node1.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node1.node_game_object->getObjectSprite()->xPos(200);
//	lv1_block_node1.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node1.z_order = 2;
//
//	lv1_block_node2.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node2.node_game_object->getObjectSprite()->xPos(350);
//	lv1_block_node2.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node2.z_order = 2;
//
//	lv1_block_node3.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node3.node_game_object->getObjectSprite()->xPos(500);
//	lv1_block_node3.node_game_object->getObjectSprite()->yPos(520);
//	lv1_block_node3.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node3.z_order = 2;
//
//	lv1_block_node4.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node4.node_game_object->getObjectSprite()->xPos(600);
//	lv1_block_node4.node_game_object->getObjectSprite()->yPos(420);
//	lv1_block_node4.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node4.z_order = 2;
//
//	lv1_block_node5.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node5.node_game_object->getObjectSprite()->xPos(580);
//	lv1_block_node5.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node5.node_game_object->getObjectSprite()->width(500);
//	lv1_block_node5.z_order = 2;
//
//	lv1_block_node6.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node6.node_game_object->getObjectSprite()->xPos(280);
//	lv1_block_node6.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node6.z_order = 2;
//
//	lv1_block_node7.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node7.node_game_object->getObjectSprite()->xPos(200);
//	lv1_block_node7.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node7.z_order = 2;
//
//	lv1_block_node8.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node8.node_game_object->getObjectSprite()->xPos(830);
//	lv1_block_node8.node_game_object->getObjectSprite()->yPos(120);
//	lv1_block_node8.z_order = 2;
//
//	lv1_block_node9.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node9.node_game_object->getObjectSprite()->xPos(1080);
//	lv1_block_node9.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node9.z_order = 2;
//
//
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node1);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node2);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node3);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node4);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node5);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node6);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node7);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node8);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node9);
//	
//}
//
//void Levels::initLevel2()
//{
//	lv1_block_node1.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node1.node_game_object->getObjectSprite()->xPos(200);
//	lv1_block_node1.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node1.z_order = 2;
//
//	lv1_block_node2.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node2.node_game_object->getObjectSprite()->xPos(350);
//	lv1_block_node2.node_game_object->getObjectSprite()->yPos(620);
//	lv1_block_node2.z_order = 2;
//
//	lv1_block_node3.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node3.node_game_object->getObjectSprite()->xPos(500);
//	lv1_block_node3.node_game_object->getObjectSprite()->yPos(520);
//	lv1_block_node3.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node3.z_order = 2;
//
//	lv1_block_node4.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node4.node_game_object->getObjectSprite()->xPos(600);
//	lv1_block_node4.node_game_object->getObjectSprite()->yPos(420);
//	lv1_block_node4.node_game_object->getObjectSprite()->width(50);
//	lv1_block_node4.z_order = 2;
//
//	lv1_block_node5.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node5.node_game_object->getObjectSprite()->xPos(580);
//	lv1_block_node5.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node5.node_game_object->getObjectSprite()->width(500);
//	lv1_block_node5.z_order = 2;
//
//	lv1_block_node6.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node6.node_game_object->getObjectSprite()->xPos(280);
//	lv1_block_node6.node_game_object->getObjectSprite()->yPos(320);
//	lv1_block_node6.z_order = 2;
//
//	lv1_block_node7.node_game_object = block_pool->getNewDWBlock();
//	lv1_block_node7.node_game_object->getObjectSprite()->xPos(200);
//	lv1_block_node7.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node7.z_order = 2;
//
//	lv1_block_node8.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node8.node_game_object->getObjectSprite()->xPos(830);
//	lv1_block_node8.node_game_object->getObjectSprite()->yPos(120);
//	lv1_block_node8.z_order = 2;
//
//	lv1_block_node9.node_game_object = block_pool->getNewRWBlock();
//	lv1_block_node9.node_game_object->getObjectSprite()->xPos(1080);
//	lv1_block_node9.node_game_object->getObjectSprite()->yPos(220);
//	lv1_block_node9.z_order = 2;
//
//
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node1);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node2);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node3);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node4);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node5);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node6);
//	scene_manager->addNodeToScene(level1_DW, lv1_block_node7);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node8);
//	scene_manager->addNodeToScene(level1_RW, lv1_block_node9);
//}
