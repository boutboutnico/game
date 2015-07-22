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

Engine_MMG::Engine_MMG(Engine& _engine, const string& _ai_player)
		: engine_(_engine), ai_player_(_ai_player)
{
}

///	------------------------------------------------------------------------------------------------

vector<uint8_t> Engine_MMG::get_moves() const
{
	std::lock_guard<std::mutex> lock(mut_);

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
	std::lock_guard<std::mutex> lock(mut_);
	engine_.add_pawn(_move);
}

///	------------------------------------------------------------------------------------------------

void Engine_MMG::undo_move(const uint8_t& _move) const
{
	std::lock_guard<std::mutex> lock(mut_);
	engine_.remove_pawn(_move);
}

///	------------------------------------------------------------------------------------------------

int16_t Engine_MMG::eval() const
{
	std::lock_guard<std::mutex> lock(mut_);
	auto n_cell = uint16_t { };

	/// Count active pawn
	for (auto& line : engine_.get_grid())
		for (auto cell : line)
			if (cell != e_pawn::none) n_cell++;

	auto winner = engine_.get_winner();
	auto result = int16_t { };

	if (winner == ai_player_) result = 1000 - n_cell;
	else if (winner == "draw") result = 0;
	else result = -1000 + n_cell;

	return result;
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
