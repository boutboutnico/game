///
/// \file	print.cpp
///	\brief	
///	\date	8 juil. 2015
/// \author	nboutin
///

#include "move_on_board.hpp"

/// === INCLUDES	================================================================================

#include <iostream>
#include "engine/engine.h"
#include "print.hpp"

/// === NAMESPACES	================================================================================

using namespace std;
using namespace print;

namespace game
{
namespace test
{

/// === PUBLIC DEFINITIONS	========================================================================

/// 1- Test rebound on other player'horses
/// 2- Test kill other player's horses
/// 3- Test rebound on home position from forward move
/// 4- Test rebound on home position from backward move

void move_on_board()
{
	move_on_board_1();
	move_on_board_2();
	move_on_board_3();
	move_on_board_4();

	cout << "=====\t" << __func__ << "\t=====" << endl;
}

///	------------------------------------------------------------------------------------------------

/// === PRIVATE DEFINITIONS	========================================================================

/// Test rebound on home position from backward move
void move_on_board_4()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.add_player("2", 1);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	/// Player 1
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);

	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 4) == e_engine_result::SUCCESS);

	/// Player 2
	horse = engine.get_current_player()->get_horse(0);
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 5) == e_engine_result::SUCCESS);

//	print_board(engine.get_board());
//	print_stairs(engine.get_stairs());

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

/// Test rebound on home position
void move_on_board_3()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	/// Player 1
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);

	for (auto i = 0U; i < 8; ++i)
		assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);

	assert(engine.move_horse_on_board(horse, 3) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);

	assert(engine.get_board().get_position(horse) == 53);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

/// Test kill other player'horses
void move_on_board_2()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.add_player("2", 1);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	/// Player 1
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 5) == e_engine_result::SUCCESS);

	/// Player 2
	horse = engine.get_current_player()->get_horse(0);
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 1) == e_engine_result::SUCCESS);
	assert(engine.get_board().get_position(horse) == 15);

	/// Player 1
	horse = engine.get_current_player()->get_horse(0);
	assert(engine.move_horse_on_board(horse, 4) == e_engine_result::SUCCESS);
	assert(engine.get_board().get_position(horse) == 15);

	/// Player 2
	horse = engine.get_current_player()->get_horse(0);
	assert(horse->get_status() == e_horse_status::AT_HOME);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------

/// Test rebound on other player'horses
void move_on_board_1()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.add_player("2", 1);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	/// Player 1
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 5) == e_engine_result::SUCCESS);

	/// Player 2
	horse = engine.get_current_player()->get_horse(0);
	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.move_horse_on_board(horse, 2) == e_engine_result::SUCCESS);
	assert(engine.get_board().get_position(horse) == 16);

	/// Player 1
	horse = engine.get_current_player()->get_horse(0);
	assert(engine.move_horse_on_board(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.get_board().get_position(horse) == 15);

	cout << __func__ << endl;
}

///	------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
