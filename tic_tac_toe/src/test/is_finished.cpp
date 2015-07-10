///
/// \file	is_finished.cpp
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///

/// === Includes	================================================================================

#include "is_finished.hpp"
#include <iostream>
#include <assert.h>
#include "engine/engine.hpp"
#include "print.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace engine;

namespace test
{

/// === Public Definitions	========================================================================

void run_is_finished()
{
	horizontal_1();
	horizontal_2();
	horizontal_3();
}

/// === Private Definitions	========================================================================

void horizontal_1()
{
	auto engine = Engine("P1", "P2");

	assert(engine.add_pawn(0, 0) == true);
	assert(engine.is_game_finished() == false);

	assert(engine.add_pawn(0, 1) == true);
	assert(engine.is_game_finished() == false);

	assert(engine.add_pawn(1, 0) == true);
	assert(engine.is_game_finished() == false);

	assert(engine.add_pawn(1, 1) == true);
	assert(engine.is_game_finished() == false);

	assert(engine.add_pawn(2, 0) == true);
	assert(engine.is_game_finished() == true);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

void horizontal_2()
{

}

///	------------------------------------------------------------------------------------------------

void horizontal_3()
{

}

///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
