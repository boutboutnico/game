///
/// \file	engine.cpp
///	\brief	
///	\date	9 juil. 2015
/// \author	nboutin
///

#include "engine.hpp"
using namespace engine;

/// === Includes	================================================================================
/// === Namespaces	================================================================================

/// === Public Definitions	========================================================================

Engine::Engine(const std::string& _p1, const std::string& _p2)
{
	players_[0] = _p1;
	players_[1] = _p2;

	current_player_ = 0;
	winner_ = n_players;

	for (auto& line : grid_)
		line.fill(e_pawn::none);
}

///	------------------------------------------------------------------------------------------------

bool Engine::is_game_finished()
{
	auto x_win = n_cells, y_win = n_cells;

	/// Horizontal
	for (auto y = 0U; y < n_cells; ++y)
	{
		if (grid_[y][0] == grid_[y][1] && grid_[y][0] == grid_[y][2] && grid_[y][0] != e_pawn::none)
		{
			y_win = y;
			break;
		}
	}

	/// Set winner
	if (y_win != n_cells)
	{
		winner_ = (grid_[y_win][0] == e_pawn::circle) ? 0 : 1;
		return true;
	}

	return false;
}

///	------------------------------------------------------------------------------------------------

bool Engine::add_pawn(uint8_t _x, uint8_t _y)
{
	/// Check input range
	if (_x >= n_cells || _y >= n_cells) return false;

	/// Is free cell
	if (grid_[_y][_x] != e_pawn::none) return false;

	/// Set pawn according to current player at _x, _y position
	grid_[_y][_x] = (players_[current_player_] == players_[0]) ? e_pawn::circle : e_pawn::cross;

	/// Change player
	next_player();

	return true;
}

/// === Private Definitions	========================================================================
/// === END OF FILES	============================================================================
