///
/// \file	engine.hpp
///	\brief	
///	\date	9 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_ENGINE_HPP_
#define ENGINE_ENGINE_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <array>

/// === Namespaces	================================================================================
namespace engine
{

///	===	Public Enumerations	========================================================================

enum class e_pawn
{
	none,
	cross,
	circle,
};

/// === Class Declarations	========================================================================
class Engine
{
private:
	/// === Private Constants	================================================================

	static const uint8_t n_players = 2;
	static const uint8_t n_cells = 3;

public:
	/// === Public Declarations	====================================================================

	Engine(const std::string& _p1, const std::string& _p2);

	///	---	Status	--------------------------------------------------------------------------------

	bool is_game_finished();

	///	---	Operations	----------------------------------------------------------------------------

	bool add_pawn(uint8_t _x, uint8_t _y);

	///	---	Accessors	----------------------------------------------------------------------------

	inline const std::string& get_current_player() const
	{
		return players_[current_player_];
	}

	inline const std::string& get_winner() const
	{
		static const auto no_winner = std::string { "draw" };
		return (winner_ < n_players) ? players_[winner_] : no_winner;
	}

	inline const std::array<std::array<e_pawn, n_cells>, n_cells>& get_grid() const
	{
		return grid_;
	}

private:
	/// === Private Declarations	================================================================

	inline void next_player()
	{
		++current_player_;
		current_player_ %= n_players;
	}

	/// === Private Attributs	====================================================================

	std::array<std::string, n_players> players_;
	uint8_t current_player_;
	uint8_t winner_;

	std::array<std::array<e_pawn, n_cells>, n_cells> grid_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
