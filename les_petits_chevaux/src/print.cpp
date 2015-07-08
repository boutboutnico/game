///
/// \file	print.cpp
///	\brief	
///	\date	8 juil. 2015
/// \author	nboutin
///

/// === INCLUDES	================================================================================

#include <iostream>
#include "engine/board.h"
#include "engine/stairs.hpp"
#include "engine/horse.h"
#include "engine/player.h"

/// === NAMESPACES	================================================================================

using namespace std;
using namespace game;

namespace print
{

/// === PUBLIC DEFINITIONS	========================================================================

void print_board(const Board& _board)
{
	auto cells = _board.get_cells();

	for (auto i = 0U; i < cells.size(); ++i)
	{
		auto horse = cells[i];

		if (i % 14 == 0) cout << endl;

		if (horse == false) cout << "-- ";
		else
		{
			if (auto player = horse->get_player().lock())
			{
				cout << player->get_name() << horse->get_name() << " ";
			}
			else
			{
				cout << "ee ";
			}
		}

	}

	cout << endl;
}

///	------------------------------------------------------------------------------------------------

void print_stairs(const Stairs& _stairs)
{
	const auto stairs = _stairs.get_stairs();

	for (auto step_position = 0U; step_position < stairs.size(); ++step_position)
	{
		auto horses = stairs[step_position];
		if (horses.empty() == false)
		{
			cout << static_cast<uint16_t>(step_position + 1) << " -> ";

			for (auto h : horses)
			{
				if (auto player = h->get_player().lock())
				{
					cout << player->get_name() << h->get_name() << " ";
				}
				else
				{
					cout << "ee ";
				}
			}
			cout << endl;
		}
	}
}

/// === PRIVATE DEFINITIONS	========================================================================
///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
