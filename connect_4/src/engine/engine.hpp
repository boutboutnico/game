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
#include <array>

/// === Namespaces	================================================================================
namespace connect_4
{
///	===	Public Enumerations	========================================================================

enum class e_pawn
{
	none,
	yellow,
	red,
};

/// === Class Declarations	========================================================================
class Engine
{
public:
	/// === Public Constants	====================================================================

	static const uint8_t n_players = 2;
	static const uint8_t width = 7;
	static const uint8_t height = 6;
	static const uint8_t line = 4;

	/// === Public Declarations	====================================================================

	Engine(const std::string& _p1, const std::string& _p2);

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

	inline const std::string& get_current_player() const
	{
		return players_[current_player_];
	}

	inline const std::string& get_winner() const
	{
		static const auto no_winner = std::string { "draw" };
		return (winner_ < n_players) ? players_[winner_] : no_winner;
	}

	inline const std::array<std::array<e_pawn, width>, height>& get_grid() const
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

	inline void previous_player()
	{
		--current_player_;
		current_player_ %= n_players;
	}

	void check_is_finished();

	/// === Private Attributs	====================================================================

	std::array<std::string, n_players> players_;
	int8_t current_player_;
	uint8_t winner_;
	bool is_finished_;

	std::array<std::array<e_pawn, width>, height> grid_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
