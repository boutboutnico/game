///
/// \file	stairs.cpp
///	\brief	
///	\date	8 juil. 2015
/// \author	nboutin
///

#include "stairs.hpp"
using namespace game;

/// === Includes 	================================================================================

#include <assert.h>
#include "engine.h"
#include "horse.h"

/// === Namespaces	================================================================================

/// === Public Definitions	========================================================================

Stairs::Stairs()
		: stairs_(n_stairs)
{

}

///	------------------------------------------------------------------------------------------------

e_engine_result Stairs::move_up_stairs(std::shared_ptr<Horse> _horse, const uint8_t _dice)
{
	if (_horse->get_status() == e_horse_status::ON_BOARD)
	{
		if (_dice != 1) return e_engine_result::NEED_DICE_1_TO_ENTER_STAIRS;

		/// Add horse on first step
		stairs_[_dice - 1].push_back(_horse);

		_horse->set_status(e_horse_status::ON_STAIRS);

		return e_engine_result::SUCCESS;
	}
	else if (_horse->get_status() == e_horse_status::ON_STAIRS)
	{
		/// Need dice equal to position + 1 to move onto next step
		auto horse_position = _M_get_position(_horse);

		if (horse_position == _dice - 1)
		{
			_M_remove(_horse, horse_position);
			_M_add(_horse, _dice);

			return e_engine_result::SUCCESS;
		}
		else
		{
			return e_engine_result::NEED_GOOD_VALUE_TO_MOVE_ON_STAIRS;
		}
	}

	return e_engine_result::ERROR_UNDEFINED;
}

/// === Private Definitions	========================================================================

uint8_t Stairs::_M_get_position(const std::shared_ptr<Horse> _horse) const
{
	for (auto i = 0U; i < n_stairs; ++i)
	{
		auto horses = stairs_[i];
		const auto stair_position = std::find(horses.begin(), horses.end(), _horse);

		/// We found horse
		if (stair_position != horses.end()) return (i + 1);
	}
	assert(false);
}

///	------------------------------------------------------------------------------------------------

void Stairs::_M_remove(std::shared_ptr<Horse> _horse, uint8_t _horse_position)
{
	auto& v = stairs_[_horse_position - 1];
	v.erase(std::remove(v.begin(), v.end(), _horse), v.end());
}

///	------------------------------------------------------------------------------------------------

/// === END OF FILES	============================================================================
