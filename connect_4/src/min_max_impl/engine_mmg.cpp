///
/// \file	ai_engine_wrapper.cpp
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///

#include <min_max_impl/engine_mmg.hpp>
using namespace connect_4;

/// === Includes	================================================================================

#include <limits>
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
	auto n_cell = uint16_t { };

	/// Count active pawn
	for (auto& line : engine_.get_grid())
		for (auto cell : line)
			if (cell != e_pawn::none) n_cell++;

	auto winner = engine_.get_winner();
	auto result = int16_t { };

	if (winner == ai_player_)
	{
		result = numeric_limits<int16_t>::max() - n_cell;
	}
	else if (winner == Engine::no_winner_)
	{
		result = draw_eval(draw_eval_depth_);
	}
	else
	{
		result = numeric_limits<int16_t>::min() + n_cell;
	}

	return result;
}

/// === Private Definitions	========================================================================

int16_t Engine_MMG::draw_eval(uint8_t _depth) const
{
	static const array<point_t, 8> points = { point_t { -1, -1 }, point_t { 0, -1 },
												point_t { 1, -1 }, point_t { 1, 0 },
												point_t { 1, 1 }, point_t { 0, 1 },
												point_t { -1, 1 }, point_t { -1, 0 } };

	const auto& grid = engine_.get_grid();
	auto result = int16_t { };

	for (auto y = uint8_t { }; y < grid.size(); ++y)
	{
		for (auto x = uint8_t { }; x < grid[y].size(); ++x)
		{
			if (grid[y][x] == e_pawn::none) continue;

			for (const auto& p : points)
			{
				result += point_eval(x, y, p, p, _depth - 1);
			}
		}
	}
	return result;
}

///	------------------------------------------------------------------------------------------------

int16_t Engine_MMG::point_eval(	const uint8_t _x,
								const uint8_t _y,
								const point_t _p_move,
								point_t _p_next,
								uint8_t _depth) const
{
	if (_depth == 0 || is_in_bound(_x + _p_next.x, _y + _p_next.y) == false)
	{
		return eval(_x, _y, _p_next);
	}

	auto result = int16_t { };
	result += eval(_x, _y, _p_next);

	_p_next.x += _p_move.x;
	_p_next.y += _p_move.y;

	result += point_eval(_x, _y, _p_move, _p_next, _depth - 1);
	return result;
}

///	------------------------------------------------------------------------------------------------

int16_t Engine_MMG::eval(int8_t x, int8_t y, point_t p) const
{
	auto own_pts = int16_t { }, adver_pts = int16_t { };
	const auto& grid = engine_.get_grid();

	if (grid[y][x] == ai_player_.get_pawn())
	{
		/// Is in bound
		if (is_in_bound(x + p.x, y + p.y) == false)
		{
			own_pts += wall_coef;
		}
		else if (grid[y + p.y][x + p.x] == ai_player_.get_pawn())
		{
			own_pts += player_coef;
		}
		else if (grid[y + p.y][x + p.x] == e_pawn::none)
		{
			own_pts += empty_coef;
		}
		else
		{
			own_pts += adversary_coef;
		}
	}
	else
	{
		/// Is in bound
		if (is_in_bound(x + p.x, y + p.y) == false)
		{
			adver_pts += wall_coef;
		}
		else if (grid[y + p.y][x + p.x] == e_pawn::none)
		{
			adver_pts += empty_coef;
		}
		else if (grid[y + p.y][x + p.x] == ai_player_.get_pawn())
		{
			adver_pts += adversary_coef;
		}
		else
		{
			adver_pts += player_coef;
		}
	}

	return own_pts - adver_pts;
}

/// === END OF FILES	============================================================================
