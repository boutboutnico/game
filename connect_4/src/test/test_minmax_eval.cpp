///
/// \file	test_is_finished.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include "test_minmax_eval.hpp"

/// === Includes	================================================================================

#include <iostream>
#include <assert.h>

#include "engine/engine.hpp"
#include "print.hpp"
#include "min_max_impl/engine_mmg.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace ai::min_max;

namespace connect_4
{
namespace test
{

/// === Public Definitions	========================================================================

///	------------------------------------------------------------------------------------------------

void draw_eval_1()
{
	auto player_1 = Player { "AI1", e_pawn::cross };
	auto player_2 = Player { "P2", e_pawn::circle };

	auto engine = Engine { player_1, player_2 };
	auto ai_engine_1 = Engine_MMG { engine, player_1 };

	engine.add_pawn(3);
	print::print_grid(engine);

	auto result = friend_draw_eval(ai_engine_1, 1);

	assert(result == 2 * Engine_MMG::empty_coef);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

void draw_eval_2()
{
	auto player_1 = Player { "AI1", e_pawn::cross };
	auto player_2 = Player { "P2", e_pawn::circle };

	auto engine = Engine { player_1, player_2 };
	auto ai_engine_1 = Engine_MMG { engine, player_1 };

	engine.add_pawn(3);
	print::print_grid(engine);

	auto result = friend_draw_eval(ai_engine_1, 2);

	assert(result == 7 * Engine_MMG::empty_coef);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

void draw_eval_3()
{
	auto player_1 = Player { "AI1", e_pawn::cross };
	auto player_2 = Player { "P2", e_pawn::circle };

	auto engine = Engine { player_1, player_2 };
	auto ai_engine_1 = Engine_MMG { engine, player_1 };

	engine.add_pawn(3);
	print::print_grid(engine);

	auto result = friend_draw_eval(ai_engine_1, 3);

	assert(result == 12 * Engine_MMG::empty_coef);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

void draw_eval_4()
{
	auto player_1 = Player { "AI1", e_pawn::cross };
	auto player_2 = Player { "P2", e_pawn::circle };

	auto engine = Engine { player_1, player_2 };
	auto ai_engine_1 = Engine_MMG { engine, player_1 };

	engine.add_pawn(3);
	engine.add_pawn(3);
	engine.add_pawn(4);
	engine.add_pawn(4);
	print::print_grid(engine);

	auto result = friend_draw_eval(ai_engine_1, 1);

	assert(result == -60);

	cout << __func__ << endl;
}

/// === Private Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
