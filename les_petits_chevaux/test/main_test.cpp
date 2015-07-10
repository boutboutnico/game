///
/// \file	main_test.cpp
///	\brief	
///	\date	6 juil. 2015
/// \author	nboutin
///

/// === Includes	================================================================================

#include "release_horse.hpp"
#include "move_on_board.hpp"
#include "stairs.hpp"

/// === Namespaces	================================================================================

using namespace game;
using namespace game::test;

/// === Public Definitions	========================================================================

/// TODO test
/// - Next player
/// - Test overtake other horse or rebound
/// - Rebound on home after a complete board turn

int main()
{
	release_horse();
	move_on_board();
//	stairs();
}

/// === END OF FILES	============================================================================
