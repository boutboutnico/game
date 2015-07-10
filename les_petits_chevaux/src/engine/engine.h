///
/// \file	engine.h
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///
#ifndef ENGINE_H_
#define ENGINE_H_

/// === Includes	================================================================================

#include <vector>
#include <string>
#include <memory>
#include <assert.h>

#include "player.h"
#include "board.h"
#include "stairs.hpp"

/// === Namespaces	================================================================================

namespace game
{
enum class e_engine_result
	: uint8_t
	{
		SUCCESS = 0,
	ERROR_UNDEFINED,
	NEED_DICE_6_TO_RELEASE,
	CELL_NOT_FREE,
	HORSE_NOT_AT_STABLE,
	HORSE_NOT_ON_BOARD,
	HORSE_NOT_IN_FRONT_OF_STAIRS,
	NEED_DICE_1_TO_ENTER_STAIRS,
	NEED_GOOD_VALUE_TO_MOVE_ON_STAIRS,
};

/// === Class Declarations	========================================================================
/// \class	
/// \brief
/// \date	24 juin 2015
/// \author	nboutin
class Engine
{
public:
	/// === Public Declarations	====================================================================

	Engine();

	bool add_player(const std::string& _name, uint8_t _home_position);

	bool start(uint8_t _n_horses);

	inline bool is_game_finished() const
	{
		return false;
	}

	/// ---	Operations	----------------------------------------------------------------------------

	inline e_engine_result pass_turn()
	{
		next_player();
		return e_engine_result::SUCCESS;
	}

	e_engine_result release_horse(std::shared_ptr<Horse> _horse, uint8_t _dice_value);
	e_engine_result move_horse_on_board(std::shared_ptr<Horse> _horse, uint8_t _dice_value);
	e_engine_result move_horse_on_stairs(std::shared_ptr<Horse> _horse, uint8_t _dice_value);

	/// ---	Accessors	----------------------------------------------------------------------------

	inline std::shared_ptr<Player> get_current_player()
	{
		return players_.at(current_player_index_);
	}

	inline const Board& get_board() const
	{
		return board_;
	}

	inline const Stairs& get_stairs() const
	{
		return stairs_;
	}

private:
	/// === Private Declarations	================================================================

	inline void next_player()
	{
		++current_player_index_;
		current_player_index_ %= players_.size();
	}

	/// === Private Attributes	====================================================================

	std::vector<std::shared_ptr<Player>> players_;
	uint8_t current_player_index_;

	Board board_;
	Stairs stairs_;
};

/// === INLINE DEFINITIONS	========================================================================

}

#endif	/// ENGINE_H_
/// === END OF FILE	================================================================================
