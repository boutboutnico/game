///
/// \file	ai_engine_wrapper.cpp
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///

#include "ai_engine_wrapper.hpp"
using namespace tic_tac_toe;

/// === Includes	================================================================================

#include "engine/engine.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace ai;
using namespace engine;

/// === Public Definitions	========================================================================

AI_Engine_Wrapper::AI_Engine_Wrapper(engine::Engine& _engine)
		: engine_(_engine)
{
}

///	------------------------------------------------------------------------------------------------

vector<unique_ptr<move_t>> AI_Engine_Wrapper::get_moves() const
{
	auto moves = vector<unique_ptr<move_t>> { };

	for (auto y = 0U; y < Engine::n_cells; ++y)
	{
		for (auto x = 0U; x < Engine::n_cells; ++x)
		{
			if (engine_.is_valid_move(x, y) == true)
			{
				moves.push_back(unique_ptr<move_t>(new move_xy(x, y)));
			}
		}
	}
	return moves;
}

///	------------------------------------------------------------------------------------------------

void AI_Engine_Wrapper::execute_move(const std::shared_ptr<move_t> _move) const
{
	auto move = dynamic_pointer_cast<move_xy, move_t>(_move);

	engine_.add_pawn(move->x_, move->y_);
}

///	------------------------------------------------------------------------------------------------

void AI_Engine_Wrapper::undo_move(const std::shared_ptr<move_t> _move) const
{
	auto move = dynamic_pointer_cast<move_xy, move_t>(_move);

	engine_.remove_pawn(move->x_, move->y_);
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
