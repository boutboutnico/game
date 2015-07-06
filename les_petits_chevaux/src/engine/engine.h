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

#include "player.h"
#include "board.h"

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
};

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	24 juin 2015
/// \author	nboutin
class Engine
{
public:
	/// === PUBLIC DECLARATIONS	====================================================================

	Engine();

	bool add_player(const std::string& _name, uint8_t _home_position);

	bool start(uint8_t _n_horses);

	inline std::shared_ptr<Player> get_current_player()
	{
		return players_.at(current_player_index_);
	}

	inline bool is_game_finished() const
	{
		return false;
	}

	inline e_engine_result pass_turn()
	{
		next_player();
		return e_engine_result::SUCCESS;
	}

	e_engine_result release_horse(std::shared_ptr<Horse> _horse, uint8_t _dice_value);
	e_engine_result move_horse_on_board(std::shared_ptr<Horse> _horse, uint8_t _dice_value);

	inline const Board& get_board() const
	{
		return board_;
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
};

/// === INLINE DEFINITIONS	========================================================================

}

#endif	/// ENGINE_H_
/// === END OF FILE	================================================================================
