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
using namespace engine;

namespace print
{

/// === Public Definitions	========================================================================

void print_grid(const engine::Engine& engine)
{
	auto& grid = engine.get_grid();

	for (auto& line : grid)
	{
		for (auto& cell : line)
		{
			auto str = (cell == e_pawn::circle) ? "O" : (cell == e_pawn::cross) ? "X" : "-";
			cout << str;
		}
		cout << endl;
	}
	cout << "--------------------" << endl;
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
