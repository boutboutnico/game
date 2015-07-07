///
/// \file	release_horse.hpp
///	\brief	
///	\date	6 juil. 2015
/// \author	nboutin
///

/// === INCLUDES	================================================================================

#include <assert.h>
#include <iostream>
#include "engine/engine.h"
#include "print.hpp"

/// === NAMESPACES	================================================================================

using namespace std;

namespace game
{
namespace test
{

/// === PUBLIC DEFINITIONS	========================================================================

void stairs_1();

void stairs()
{
	stairs_1();

	cout << "=====\t" << __func__ << "\t=====" << endl;
}

/// === PRIVATE DEFINITIONS	========================================================================

void stairs_1()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);

	/// After 9 dice 6, It should be one cell before stairs entrance
	for (auto i = 0U; i < 9; ++i)
		assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);

	assert(engine.move_horse_on_board(horse, 1) == e_engine_result::SUCCESS);

	print_board(engine.get_board());
	print_stairs(engine);

	assert(engine.move_horse_on_stairs(horse, 1) == e_engine_result::SUCCESS);

	print_board(engine.get_board());
	print_stairs(engine);

	cout << __func__ << endl;

}

///	------------------------------------------------------------------------------------------------

}
}
/// === END OF FILES	============================================================================
