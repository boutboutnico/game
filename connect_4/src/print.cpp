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

	for (uint8_t x = 0; x <= grid.size(); ++x)
		cout << " " << uint16_t(x + 1) << " ";
	cout << endl;

	for (uint8_t x = 0; x < grid.size(); ++x)
	{
		for (uint8_t y = 0; y < grid[x].size(); ++y)
		{
			auto str = (grid[x][y] == e_pawn::yellow) ? ">< " :
						(grid[x][y] == e_pawn::red) ? "() " : "-- ";
			cout << str;
		}
		cout << endl;
	}
	cout << "____________________" << endl;
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
