///
/// \file	test_is_finished.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include <test/test_is_finished.hpp>

/// === Includes	================================================================================

#include <iostream>
#include <assert.h>
#include "engine/engine.hpp"
#include "print.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace connect_4
{
namespace test
{

/// === Public Definitions	========================================================================

void is_finished_1()
{
	auto engine = Engine{"P1", "P2"};

	engine.add_pawn(3);
	engine.add_pawn(3);

	engine.add_pawn(4);
	engine.add_pawn(4);

	engine.add_pawn(5);
	engine.add_pawn(5);

	print::print_grid(engine);

	engine.add_pawn(6);

	assert(engine.is_game_finished() == true);

	cout << __func__ << endl;
}

/// === Private Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
