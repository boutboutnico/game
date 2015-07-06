///
/// \file	release_horse.hpp
///	\brief	
///	\date	6 juil. 2015
/// \author	nboutin
///

/// === INCLUDES	================================================================================

#include <assert.h>
#include <iostream>
#include "engine.h"

/// === NAMESPACES	================================================================================

using namespace std;

namespace game
{
namespace test
{

/// === PUBLIC DEFINITIONS	========================================================================

/// 1- Don't release horse without dice equal to 6
/// 2- Don't release horse already out
/// Release horse on free home cell
/// Release horse on home cell taken by own horse
/// Release horse on home cell taken by other player horse

void release_horse_1();
void release_horse_2();

void release_horse()
{
	release_horse_1();
	release_horse_2();

	cout << "=====\t" << __func__ << "\t=====" << endl;
}

/// === PRIVATE DEFINITIONS	========================================================================

void release_horse_2()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	assert(engine.release_horse(horse, 6) == e_engine_result::SUCCESS);
	assert(engine.release_horse(horse, 6) == e_engine_result::HORSE_NOT_AT_STABLE);

	cout << __func__ << endl;
}

void release_horse_1()
{
	auto engine = Engine();
	engine.add_player("1", 0);
	engine.start(2);

	auto horse = engine.get_current_player()->get_horse(0);

	assert(engine.release_horse(horse, 1) == e_engine_result::NEED_DICE_6_TO_RELEASE);

	cout << __func__ << endl;

}

}
}
/// === END OF FILES	============================================================================
