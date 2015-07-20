///
/// \file	ai_engine_wrapper.cpp
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///

#include "engine_gmm.hpp"
using namespace tic_tac_toe;

/// === Includes	================================================================================

#include "engine/engine.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace ai;

/// === Public Definitions	========================================================================

Engine_GMM::Engine_GMM(Engine& _engine, const string& _ai_player)
		: engine_(_engine), ai_player_(_ai_player)
{
}

///	------------------------------------------------------------------------------------------------

vector<tic_tac_toe::move_t> Engine_GMM::get_moves() const
{
	auto moves = vector<move_t> { };

	for (auto y = 0U; y < Engine::n_cells; ++y)
	{
		for (auto x = 0U; x < Engine::n_cells; ++x)
		{
			if (engine_.is_valid_move(x, y) == true)
			{
				moves.push_back(move_t(x, y));
			}
		}
	}
	return moves;
}

///	------------------------------------------------------------------------------------------------

void Engine_GMM::execute_move(const move_t& _move) const
{
//	auto move = dynamic_pointer_cast<move_xy, move_t>(_move);

	engine_.add_pawn(_move.x_, _move.y_);
}

///	------------------------------------------------------------------------------------------------

void Engine_GMM::undo_move(const move_t& _move) const
{
//	auto move = dynamic_pointer_cast<move_xy, move_t>(_move);

	engine_.remove_pawn(_move.x_, _move.y_);
}

///	------------------------------------------------------------------------------------------------

int16_t Engine_GMM::eval() const
{
	auto n_cell = 0ULL;

	for (auto& line : engine_.get_grid())
		for (auto cell : line)
			if (cell != e_pawn::none) n_cell++;

	auto winner = engine_.get_winner();

	auto result = 0;
	if (winner == ai_player_) result = 1000 - n_cell;
	else if (winner == "draw") result = 0;
	else result = -1000 + n_cell;

	return result;
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
