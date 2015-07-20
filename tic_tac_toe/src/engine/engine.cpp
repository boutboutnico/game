///
/// \file	engine.cpp
///	\brief	
///	\date	9 juil. 2015
/// \author	nboutin
///

#include "engine.hpp"
using namespace tic_tac_toe;

/// === Includes	================================================================================
/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================

Engine::Engine(const std::string& _p1, const std::string& _p2)
		: players_ { _p1, _p2 }, current_player_(0), winner_(n_players), is_finished_(false)
{
	for (auto& line : grid_)
		line.fill(e_pawn::none);
}

///	------------------------------------------------------------------------------------------------

bool Engine::is_valid_move(uint8_t _x, uint8_t _y) const
{
	/// Check input range
	if (_x >= n_cells || _y >= n_cells) return false;

	/// Is free cell
	if (grid_[_y][_x] != e_pawn::none) return false;

	return true;
}

///	------------------------------------------------------------------------------------------------

bool Engine::add_pawn(const uint8_t _x, const uint8_t _y)
{
	if (is_valid_move(_x, _y) == false) return false;

	/// Set pawn according to current player at _x, _y position
	grid_[_y][_x] = (players_[current_player_] == players_[0]) ? e_pawn::circle : e_pawn::cross;

	/// Control end of game
	check_is_finished();

	/// Change player
	next_player();

	return true;
}

/// === Private Definitions	========================================================================

void Engine::check_is_finished()
{
	auto x_win = n_cells, y_win = n_cells;
	auto reference = grid_[0][0];

	/// Horizontal
	for (auto y = 0U; y < n_cells; ++y)
	{
		reference = grid_[y][0];
		if (reference == grid_[y][1] && reference == grid_[y][2] && reference != e_pawn::none)
		{
			x_win = 0;
			y_win = y;
			break;
		}
	}

	/// Vertical
	for (auto x = 0U; x < n_cells; ++x)
	{
		reference = grid_[0][x];
		if (reference == grid_[1][x] && reference == grid_[2][x] && reference != e_pawn::none)
		{
			x_win = x;
			y_win = 0;
			break;
		}
	}

	/// Diagonale
	if (grid_[0][0] == grid_[1][1] && grid_[0][0] == grid_[2][2] && grid_[0][0] != e_pawn::none)
	{
		x_win = 0;
		y_win = 0;
	}

	/// Diagonale
	reference = grid_[2][0];
	if (reference == grid_[1][1] && reference == grid_[0][2] && reference != e_pawn::none)
	{
		x_win = 0;
		y_win = 2;
	}

	/// Set winner
	if (x_win != n_cells && y_win != n_cells)
	{
		winner_ = (grid_[y_win][x_win] == e_pawn::circle) ? 0 : 1;
		is_finished_ = true;
	}
	else
	{
		auto n_cell = 0ULL;

		for (auto& line : grid_)
			for (auto cell : line)
				if (cell != e_pawn::none) n_cell++;

		if (n_cell == n_cells * n_cells) is_finished_ = true;
	}
}

/// === END OF FILES	============================================================================
