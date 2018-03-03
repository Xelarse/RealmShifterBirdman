#pragma once
#include <atomic>

class StateMachine
{
public:

	StateMachine() = default;
	~StateMachine() = default;

	void passInInputToStateMachine(int input_key);
	void resetGameActionState() const;
	bool isGameActionStateDefault() const;



private:

	void processMenuState(int input_key);
	void processPauseState(int input_key);
	void processGameState(int input_key);
	void processGameoverState(int input_key);
	void processLevelSelect(int input_key);
	

};

enum class LevelSelect
{

	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4
};

enum class WorldTypeState
{
	DREAMWORLD,
	REALWORLD
};

enum class MenuState
{
	HOVER_START,
	HOVER_EXIT
};

enum class OverallState
{
	GAMEPLAY,
	MENU,
	PAUSE,
	GAMEOVER,
	EXIT
};

enum class PauseState
{
	HOVER_CONTINUE,
	HOVER_QUIT
};

enum class GameoverState
{
	HOVER_MENU,
	HOVER_QUIT
};

enum class PlayerJumpState
{
	JUMP_ON,
	JUMP_OFF
};

enum class PlayerMoveState
{
	INVALID = -1,  /**< is a non-valid game action */
	NONE = 0,  /**< means no outstanding action to process */
	MOVE_LEFT,
	MOVE_RIGHT,
};

extern std::atomic<MenuState> menu_state;
extern std::atomic<OverallState> overall_state;
extern std::atomic<PauseState> pause_state;
extern std::atomic<PlayerJumpState> jump_state;
extern std::atomic<GameoverState> gameover_state;
extern std::atomic<PlayerMoveState> move_state;
extern std::atomic<LevelSelect> level_select;
extern std::atomic<WorldTypeState> world_type_state;