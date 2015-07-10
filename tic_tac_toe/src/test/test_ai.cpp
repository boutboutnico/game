///
/// \file	is_finished.cpp
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///

/// === Includes	================================================================================

#include <iostream>
#include <assert.h>
#include <test/test_ai.hpp>
#include "engine/engine.hpp"
#include "ai/min_max.hpp"
#include "print.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace engine;
using namespace ai;

namespace test
{

/// === Public Definitions	========================================================================

void run_ai()
{
	ai_1();
	ai_2();
}

/// === Private Definitions	========================================================================

//X1 X2 O3
//O4 O1 --
//X3 O2 --
void ai_2()
{
	auto engine = Engine("P1", "AI");

	assert(engine.add_pawn(1, 1) == true);
	assert(engine.add_pawn(0, 0) == true);
	assert(engine.add_pawn(1, 2) == true);
	assert(engine.add_pawn(1, 0) == true);
	assert(engine.add_pawn(2, 0) == true);
	assert(engine.add_pawn(0, 2) == true);
	assert(engine.add_pawn(0, 1) == true);

	auto ai = Min_Max { "AI" };
	uint16_t x = 10, y = 10;
	ai.compute(engine, 10, x, y);
	assert(x == 2 && y == 1);

	cout << __func__ << endl;

}

///	------------------------------------------------------------------------------------------------

//00 10 20
//01 11 21
//02 12 22

// O1 X1 O2
// O3 X2 --
// -- X3 --
/// win on last move
void ai_1()
{
	auto engine = Engine("P1", "AI");

	assert(engine.add_pawn(0, 0) == true);
	assert(engine.add_pawn(1, 0) == true);
	assert(engine.add_pawn(2, 0) == true);
	assert(engine.add_pawn(1, 1) == true);
	assert(engine.add_pawn(0, 1) == true);

	auto ai = Min_Max { "AI" };
	uint16_t x = 10, y = 10;
	ai.compute(engine, 5, x, y);

	cout << x << " " << y << endl;

	assert(x == 1 && y == 2);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
