///
/// \file	board.cpp
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///

#include "board.h"

#include <iostream>
using namespace std;

using namespace game;

/// === Includes	================================================================================

#include "horse.h"

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

Board::Board()
		: cells_(n_cells)
{

}

/// ------------------------------------------------------------------------------------------------

bool Board::is_in_front_of_stairs(std::shared_ptr<Horse> _horse) const
{
	auto horse_position = get_position(_horse);
	horse_position = _M_convert_index(horse_position);

	auto stairs_entry_position = _horse->get_home_position() - 1;
	stairs_entry_position = _M_convert_index(stairs_entry_position);

	return (horse_position == stairs_entry_position) ? true : false;
}

/// ------------------------------------------------------------------------------------------------

bool Board::add_horse(shared_ptr<Horse> _horse, uint8_t _cell_index)
{
	cells_[_M_convert_index(_cell_index)] = _horse;
	return true;
}

/// ------------------------------------------------------------------------------------------------

bool Board::remove_horse(uint8_t _cell_index)
{
	cells_[_M_convert_index(_cell_index)] = shared_ptr<Horse>();
	return true;
}

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================
