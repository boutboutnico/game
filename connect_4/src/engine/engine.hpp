///
/// \file	engine.hpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_ENGINE_HPP_
#define ENGINE_ENGINE_HPP_

/// === Includes	================================================================================

#include <string>
#include <vector>
#include <array>

#include "player.hpp"

/// === Namespaces	================================================================================
namespace connect_4
{

/// === Class Declarations	========================================================================
class Engine
{
public:
	/// === Public Constants	====================================================================

	static const uint8_t width = 7;
	static const uint8_t height = 6;
	static const uint8_t line = 4;

	static const Player no_winner_;

	/// === Public Declarations	====================================================================

	Engine(Player& _p1, Player& _p2);

	///	---	Status	--------------------------------------------------------------------------------

	inline bool is_game_finished()
	{
		return is_finished_;
	}

	bool is_valid_move(uint8_t _x) const;

	///	---	Operations	----------------------------------------------------------------------------

	bool add_pawn(uint8_t _x);

	/// For AI or cheaters...
	void remove_pawn(uint8_t _x);

	///	---	Accessors	----------------------------------------------------------------------------

	inline Player& get_current_player() const
	{
		return *players_[current_player_id_];
	}

	inline const Player& get_winner() const
	{
		return *winner_;
	}

	inline const std::array<std::array<e_pawn, width>, height>& get_grid() const
	{
		return grid_;
	}

private:
	/// === Private Declarations	================================================================

	inline void next_player()
	{
		++current_player_id_;
		current_player_id_ %= players_.size();
	}

	inline void previous_player()
	{
		--current_player_id_;
		current_player_id_ %= players_.size();
	}

	void check_is_finished();

	/// === Private Attributs	====================================================================

	std::vector<Player*> players_;
	int8_t current_player_id_;
	const Player* winner_;
	bool is_finished_;

	std::array<std::array<e_pawn, width>, height> grid_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
