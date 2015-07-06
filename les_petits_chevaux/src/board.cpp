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

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

Board::Board()
		: cells_(n_cells)
{

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
