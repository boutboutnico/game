///
/// \file	print.cpp
///	\brief	
///	\date	9 juil. 2015
/// \author	nboutin
///

#include "print.hpp"

/// === Includes	================================================================================

#include <iostream>
#include "engine/engine.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace connect_4;

namespace print
{
/// === Public Definitions	========================================================================

void print_grid(const Engine& engine)
{
	auto& grid = engine.get_grid();

	cout << endl;
	for (uint8_t x = 0; x <= grid.size(); ++x)
		cout << " " << uint16_t(x + 1) << " ";
	cout << endl;

	for (uint8_t x = 0; x < grid.size(); ++x)
	{
		for (uint8_t y = 0; y < grid[x].size(); ++y)
		{
//			auto str = (grid[x][y] == e_pawn::cross) ? ">< " :
//						(grid[x][y] == e_pawn::circle) ? "() " : "-- ";
			cout << grid[x][y] << " ";
		}
		cout << endl;
	}
	cout << "____________________" << endl << endl;
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
