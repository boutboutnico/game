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
using namespace tic_tac_toe;

namespace print
{

/// === Public Definitions	========================================================================

void print_grid(const Engine& engine)
{
	auto& grid = engine.get_grid();

	for (auto& line : grid)
	{
		for (auto& cell : line)
		{
			auto str = (cell == e_pawn::circle) ? "() " : (cell == e_pawn::cross) ? ">< " : "-- ";
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
