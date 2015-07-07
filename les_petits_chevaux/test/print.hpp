///
/// \file	release_horse.hpp
///	\brief	
///	\date	6 juil. 2015
/// \author	nboutin
///

/// === INCLUDES	================================================================================

#include <assert.h>
#include <iostream>
#include "engine/engine.h"

/// === NAMESPACES	================================================================================

using namespace std;

namespace game
{
namespace test
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

void print_stairs(const Engine& _engine)
{
	const auto stairs = _engine.get_stairs();

	for (auto dice_value = 0U; dice_value < stairs.size(); ++dice_value)
	{
		auto horses = stairs[dice_value];
		if (horses.empty() == false)
		{
			cout << static_cast<uint16_t>(dice_value) << " -> ";

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

}
}
/// === END OF FILES	============================================================================
