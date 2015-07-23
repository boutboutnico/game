///
/// \file	ai_engine_wrapper.cpp
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///

#include <min_max_impl/engine_mmg.hpp>
using namespace connect_4;

/// === Includes	================================================================================

#include "engine/engine.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace ai;

/// === Public Definitions	========================================================================

Engine_MMG::Engine_MMG(Engine& _engine, Player& _ai_player)
		: engine_(_engine), ai_player_(_ai_player)
{
}

///	------------------------------------------------------------------------------------------------

vector<uint8_t> Engine_MMG::get_moves() const
{
	auto moves = vector<uint8_t> { };

	for (auto x = uint8_t { }; x < Engine::width; ++x)
	{
		if (engine_.is_valid_move(x) == true)
		{
			moves.push_back(x);
		}
	}

	return moves;
}

///	------------------------------------------------------------------------------------------------

void Engine_MMG::execute_move(const uint8_t& _move) const
{
	engine_.add_pawn(_move);
}

///	------------------------------------------------------------------------------------------------

void Engine_MMG::undo_move(const uint8_t& _move) const
{
	engine_.remove_pawn(_move);
}

///	------------------------------------------------------------------------------------------------

int16_t Engine_MMG::eval() const
{
	static const int16_t high_score = Engine::width * Engine::height * 8 * 10;
	auto n_cell = uint16_t { };

	/// Count active pawn
	for (auto& line : engine_.get_grid())
		for (auto cell : line)
			if (cell != e_pawn::none) n_cell++;

	auto winner = engine_.get_winner();
	auto result = int16_t { };

	if (winner == ai_player_)
	{
		result = high_score - n_cell;
	}
	else if (winner == Engine::no_winner_)
	{
		const auto& grid = engine_.get_grid();

		for (auto y = uint16_t { }; y < grid.size(); ++y)
		{
			for (auto x = uint16_t { }; x < grid[y].size(); ++x)
			{
				result += eval_rec(x, y, 1);
			}
		}
	}
	else
	{
		result = -high_score + n_cell;
	}

	return result;
}

/// === Private Definitions	========================================================================

/// Cross = adver
/// Circle = AI

struct point_t
{
	int8_t x, y;
};

int16_t Engine_MMG::eval_rec(uint8_t x, uint8_t y, uint8_t _depth) const
{
	static const array<point_t, 8> points = { point_t { -1, -1 }, point_t { 0, -1 },
												point_t { 1, -1 }, point_t { 1, 0 },
												point_t { 1, 1 }, point_t { 0, 1 },
												point_t { -1, 1 }, point_t { -1, 0 } };

	const auto& grid = engine_.get_grid();
	auto own_pts = int16_t { }, adver_pts = int16_t { };

	if(_depth == 0)
	{

	}

	if (grid[y][x] == e_pawn::none)
	{
//		continue;
	}
	else if (grid[y][x] == ai_player_.get_pawn())
	{
		for (const auto& p : points)
		{
			/// Is in bound
			if (y + p.y < 0 || y + p.y >= Engine::height || x + p.x < 0 || x + p.x >= Engine::width)
			{
				own_pts -= 5;
			}
			else if (grid[y + p.y][x + p.x] == ai_player_.get_pawn())
			{
				own_pts += 10;
			}
			else if (grid[y + p.y][x + p.x] == e_pawn::none)
			{
				own_pts += 5;
			}
			else
			{
				own_pts -= 10;
			}
		}
	}
	else
	{
		for (const auto& p : points)
		{
			/// Is in bound
			if (y + p.y < 0 || y + p.y >= Engine::height || x + p.x < 0 || x + p.x >= Engine::width)
			{
				adver_pts -= 5;
			}
			else if (grid[y + p.y][x + p.x] == e_pawn::none)
			{
				adver_pts += 5;
			}
			else if (grid[y + p.y][x + p.x] == ai_player_.get_pawn())
			{
				adver_pts -= 10;
			}
			else
			{
				adver_pts += 10;
			}
		}
	}

	return own_pts + adver_pts;
}

/// === END OF FILES	============================================================================
