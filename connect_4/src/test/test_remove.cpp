///
/// \file	test_is_finished.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include <test/test_remove.hpp>

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

void remomve_pawn_1()
{
	auto player_1 = Player {"P1", e_pawn::cross};
	auto player_2 = Player {"P2", e_pawn::circle};
	auto engine = Engine { player_1, player_2 };

	engine.add_pawn(3);

	print::print_grid(engine);

	engine.remove_pawn(3);

	print::print_grid(engine);

	cout << __func__ << endl;
}

/// === Private Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
