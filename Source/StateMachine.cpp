#include <Engine/Keys.h>

#include "StateMachine.h"

std::atomic<MenuState> menu_state = MenuState::HOVER_START;
std::atomic<OverallState> overall_state = OverallState::MENU;
std::atomic<PauseState> pause_state = PauseState::HOVER_CONTINUE;
std::atomic<PlayerJumpState> jump_state = PlayerJumpState::JUMP_OFF;
std::atomic<PlayerMoveState> move_state = PlayerMoveState::NONE;
std::atomic<GameoverState> gameover_state = GameoverState::HOVER_MENU;
std::atomic<LevelSelect> level_select = LevelSelect::LEVEL1;
std::atomic<WorldTypeState> world_type_state = WorldTypeState::REALWORLD;

/**
*   @brief   Takes input and passes into certain functions depending on overall state.
*/

void StateMachine::passInInputToStateMachine(int input_key)
{
	switch (overall_state)
	{
		case OverallState::MENU:
		{
			processMenuState(input_key);
			break;
		}

		case OverallState::PAUSE:
		{
			processPauseState(input_key);
			break;
		}

		case OverallState::GAMEPLAY:
		{
			processGameState(input_key);
			break;
		}

		case OverallState::GAMEOVER:
		{
			processGameoverState(input_key);
			break;
		}
	}
}

/**
*   @brief   Resets jump_state and move_state back to its default state for repeat play.
*/
void StateMachine::resetGameActionState() const
{
	jump_state = PlayerJumpState::JUMP_OFF;
	move_state = PlayerMoveState::NONE;
	world_type_state = WorldTypeState::REALWORLD;
}

/**
*   @brief   Checks to see if current players movement and jump state is default.
*   @return  True if jump_state == jump_off and move_state == NONE.
*/
bool StateMachine::isGameActionStateDefault() const
{
	if (jump_state != PlayerJumpState::JUMP_OFF && move_state != PlayerMoveState::NONE)
	{
		return false;
	}

	else
	{
		return true;
	}
}

/**
*   @brief   Uses input passed into it for change menu_state.
*	@details	Left, right, up and down arrow keys switch between which menu option it hovers
and enter confirms the selection
*/



void StateMachine::processMenuState(int input_key)
{
	switch (input_key)
	{
		case ASGE::KEYS::KEY_LEFT:
		case ASGE::KEYS::KEY_RIGHT:
		case ASGE::KEYS::KEY_UP:
		case ASGE::KEYS::KEY_DOWN:
		{
			if (menu_state == MenuState::HOVER_EXIT)
			{
				menu_state = MenuState::HOVER_START;
			}

			else if (menu_state == MenuState::HOVER_START)
			{
				menu_state = MenuState::HOVER_EXIT;
			}
			break;
		}

		case ASGE::KEYS::KEY_ENTER:
		{
			if (menu_state == MenuState::HOVER_EXIT)
			{
				overall_state = OverallState::EXIT;
			}

			else if (menu_state == MenuState::HOVER_START)
			{
				overall_state = OverallState::GAMEPLAY;
			}
			break;
		}
	}
}

/**
*   @brief   Takes the input passed into it to change pause_state.
*   @details Left, right, up and down arrow keys switch between hovering continue and quit,
enter confirms the selection.
*/
void StateMachine::processPauseState(int input_key)
{
	switch (input_key)
	{
		case ASGE::KEYS::KEY_LEFT:
		case ASGE::KEYS::KEY_RIGHT:
		case ASGE::KEYS::KEY_UP:
		case ASGE::KEYS::KEY_DOWN:
		{
			if (pause_state == PauseState::HOVER_CONTINUE)
			{
				pause_state = PauseState::HOVER_QUIT;
			}

			else if (pause_state == PauseState::HOVER_QUIT)
			{
				pause_state = PauseState::HOVER_CONTINUE;
			}
			break;
		}

		case ASGE::KEYS::KEY_ENTER:
		{
			if (pause_state == PauseState::HOVER_QUIT)
			{
				overall_state = OverallState::MENU;
			}

			else if (pause_state == PauseState::HOVER_CONTINUE)
			{
				overall_state = OverallState::GAMEPLAY;
			}
			break;
		}
	}
}

/**
*   @brief   Takes input and changes game_action.
*   @details Arrow keys control which direction is set on game_action,
escape switches game into Pause.
*/

void StateMachine::processGameState(int input_key)
{
	switch (input_key)
	{
		case ASGE::KEYS::KEY_ESCAPE:
		{
			overall_state = OverallState::PAUSE;
			break;
		}

		case::ASGE::KEYS::KEY_SPACE:
		{
			if (jump_state == PlayerJumpState::JUMP_OFF)
			{
				jump_state = PlayerJumpState::JUMP_ON;
			}
			break;
		}

		case ASGE::KEYS::KEY_LEFT:
		{
			if (move_state != PlayerMoveState::MOVE_LEFT)
			{
				move_state = PlayerMoveState::MOVE_LEFT;
			}
			break;
		}

		case ASGE::KEYS::KEY_RIGHT:
		{
			if (move_state != PlayerMoveState::MOVE_RIGHT)
			{
				move_state = PlayerMoveState::MOVE_RIGHT;
			}
			break;
		}

		case ASGE::KEYS::KEY_V:
		{
			if (world_type_state == WorldTypeState::DREAMWORLD)
			{
				world_type_state = WorldTypeState::REALWORLD;
			}
			else
			{
				world_type_state = WorldTypeState::DREAMWORLD;
			}
		}

	}
}

/**
*   @brief   Takes input and changes gameover_state.
*   @details Left, right, up and down arrows toggle between menu options for gameover_state,
enter confirms the selection.
*/
void StateMachine::processGameoverState(int input_key)
{
	switch (input_key)
	{
		case ASGE::KEYS::KEY_ENTER:
		{
			overall_state = OverallState::MENU;
			break;
		}
	}
}

void StateMachine::processLevelSelect(int input_key)
{
	
}


