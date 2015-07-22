///
/// \file	engine.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include "engine.hpp"
using namespace connect_4;

#include <iostream>
using namespace std;

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

bool Engine::is_valid_move(uint8_t _x) const
{
	/// Check input range
	if (_x >= width) return false;

	/// Is free cell
	if (grid_[0][_x] != e_pawn::none) return false;

	return true;
}

///	------------------------------------------------------------------------------------------------

bool Engine::add_pawn(const uint8_t _x)
{
	if (is_valid_move(_x) == false) return false;

	/// Find last free cell in column _x
	auto y = uint8_t { };
	for (; y < height; ++y)
	{
		/// Is free cell
		if (grid_[y][_x] != e_pawn::none) break;
	}

	/// Set pawn in free cell and column _x
	grid_[y - 1][_x] = (players_[current_player_] == players_[0]) ? e_pawn::cross : e_pawn::circle;

	/// Control end of game
	check_is_finished();

	/// Change player
	next_player();

	return true;
}

///	------------------------------------------------------------------------------------------------

void Engine::remove_pawn(uint8_t _x)
{
	auto y = uint8_t { };

	while (grid_[y][_x] == e_pawn::none)
		++y;

	grid_[y][_x] = e_pawn::none;
	winner_ = n_players;
	is_finished_ = false;
	previous_player();
}

/// === Private Definitions	========================================================================

void Engine::check_is_finished()
{
	auto x_win = width;
	auto y_win = height;

	auto x = uint16_t { };
	auto y = uint16_t { };

	auto n_cell = uint16_t { };

	///	===	Horizontal check	==========
	for (y = 0; y < height; ++y)
	{
		for (x = 0; x <= width - line; ++x)
		{
			auto first_cell = grid_[y][x];

			if (first_cell == e_pawn::none) continue;

			auto count = uint16_t { };

			for (uint16_t xl = x; xl < width; ++xl)
			{
				if (first_cell == grid_[y][xl]) count++;
				else break;
			}

			if (count >= line)
			{
				x_win = x;
				y_win = y;
				goto found;
			}

			x += count - 1;
		}
	}

	///	===	Vertical check	==========

	for (x = 0; x < width; ++x)
	{
		for (y = 0; y <= height - line; ++y)
		{
			auto first_cell = grid_[y][x];

			if (first_cell == e_pawn::none) continue;

			auto count = uint16_t { };

			for (uint16_t yl = y; yl < height; ++yl)
			{
				if (first_cell == grid_[yl][x]) count++;
				else break;
			}

			if (count >= line)
			{
				x_win = x;
				y_win = y;
				goto found;
			}

			y += count - 1;
		}
	}

	/// === Diagonal check from left-high to right-low	===========

	for (y = 0; y <= height - line; ++y)
	{
		for (x = 0; x <= width - line; ++x)
		{
			auto first_cell = grid_[y][x];

			if (first_cell == e_pawn::none) continue;

			auto count = uint16_t { };

			uint16_t xl, yl;
			for (xl = x + 1, yl = y + 1; yl < height && xl < width; ++yl, ++xl)
			{
				if (first_cell == grid_[yl][xl]) count++;
				else break;
			}

			if (count >= line - 1)
			{
				x_win = x;
				y_win = y;
				goto found;
			}
		}
	}

	/// === Diagonal check from left-bottom to right-top	===========

	for (y = height - line + 1; y < height; ++y)
	{
		for (x = 0; x <= width - line; ++x)
		{
			auto first_cell = grid_[y][x];

			if (first_cell == e_pawn::none) continue;

			auto count = uint16_t { };

			int16_t xl, yl;
			for (xl = x + 1, yl = y - 1; yl >= 0 && xl < width; --yl, ++xl)
			{
				if (first_cell == grid_[yl][xl]) count++;
				else break;
			}

			/// Count could be greater than line, still a win
			if (count >= line - 1)
			{
				x_win = x;
				y_win = y;
				goto found;
			}
		}
	}

	/// ===	Check if game is finished but there is no winner
	for (auto& line : grid_)
		for (auto cell : line)
			if (cell != e_pawn::none) n_cell++;

	if (n_cell == width * height) is_finished_ = true;

	return;

	/// Label : Line found
	found:
	{
		winner_ = (grid_[y_win][x_win] == e_pawn::cross) ? 0 : 1;
		is_finished_ = true;
	}
}
/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
