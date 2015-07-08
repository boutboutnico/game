///
/// \file	engine.cpp
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///

#include "engine.h"
using namespace game;

/// === Includes	================================================================================

#include <iostream>
#include <algorithm>

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

Engine::Engine()
		: current_player_index_(0)
{

}

///	------------------------------------------------------------------------------------------------

bool Engine::add_player(const std::string& _name, uint8_t _home_position)
{
	players_.push_back(make_shared<Player>(_name, _home_position));
	return true;
}

///	------------------------------------------------------------------------------------------------

bool Engine::start(uint8_t _n_horses)
{
	for (auto p : players_)
	{
		p->add_horses(_n_horses);
	}

	/// Set current_player to first player
	current_player_index_ = 0;

	return true;
}

///	------------------------------------------------------------------------------------------------

e_engine_result Engine::release_horse(shared_ptr<Horse> _horse, uint8_t _dice_value)
{
	/// Need a 6 to release a horse
	if (_dice_value != 6)
	{
		return e_engine_result::NEED_DICE_6_TO_RELEASE;
	}

	/// Horse already out ?
	if (_horse->get_status() != e_horse_status::AT_HOME)
	{
		return e_engine_result::HORSE_NOT_AT_STABLE;
	}

	/// Destination cell free ?
	/// If destination cell is not free, kill present horse
	auto horse_destination = _horse->get_home_position();
	if (board_.is_free_cell(horse_destination) == false)
	{
		/// Be carefull you can kill an other of your own horses
		auto horse_to_kill = board_.get_horse(horse_destination);
		horse_to_kill->set_status(e_horse_status::AT_HOME);
	}

	/// All good, release horse
	board_.add_horse(_horse, horse_destination);

	/// Update horse status
	_horse->set_status(e_horse_status::ON_BOARD);

	return e_engine_result::SUCCESS;

	return e_engine_result::ERROR_UNDEFINED;
}

///	------------------------------------------------------------------------------------------------

e_engine_result Engine::move_horse_on_board(shared_ptr<Horse> _horse, const uint8_t _dice_value)
{
	if (_horse->get_status() != e_horse_status::ON_BOARD)
	{
		return e_engine_result::HORSE_NOT_ON_BOARD;
	}

	const auto horse_position = board_.get_position(_horse);
	int16_t virtual_horse_position = horse_position;
	auto virtual_dice_value = _dice_value;
	bool dir_fwd = true;

	while (virtual_dice_value != 0)
	{
		if (dir_fwd)
		{
			/// Move horse
			++virtual_horse_position;

			/// Check next position
			if (board_.is_free_cell(virtual_horse_position) == false    ///
				&& virtual_horse_position == _horse->get_home_position()	///
				&& horse_position != virtual_horse_position)
			{
				dir_fwd = false;
			}
		}
		else
		{
			--virtual_horse_position;

			if (board_.is_free_cell(virtual_horse_position) == false    ///
				&& horse_position != virtual_horse_position)
			{
				dir_fwd = true;
			}
		}

		--virtual_dice_value;
	}

	/// If destination cell is not free, kill present horse
	if (board_.is_free_cell(virtual_horse_position) == false)
	{
		auto horse_to_kill = board_.get_horse(virtual_horse_position);

		/// Should not be itself
		if (_horse != horse_to_kill) horse_to_kill->set_status(e_horse_status::AT_HOME);
	}

	board_.remove_horse(horse_position);
	board_.add_horse(_horse, virtual_horse_position);

	if (_dice_value != 6) next_player();
	return e_engine_result::SUCCESS;
}

///	------------------------------------------------------------------------------------------------

e_engine_result Engine::move_horse_on_stairs(std::shared_ptr<Horse> _horse, uint8_t _dice_value)
{
	if (_horse->get_status() == e_horse_status::ON_BOARD)
	{
		if (board_.is_in_front_of_stairs(_horse) == false) return e_engine_result::HORSE_NOT_IN_FRONT_OF_STAIRS;

		/// Add board on stairs, here it is first step
		/// Horse status modified here (if necessary)
		auto result = stairs_.move_up_stairs(_horse, _dice_value);

		if (result == e_engine_result::SUCCESS)
		{
			/// Remove horse from board
			auto horse_position = board_.get_position(_horse);
			board_.remove_horse(horse_position);
		}

		return result;
	}
	else if (_horse->get_status() == e_horse_status::ON_STAIRS)
	{
		return stairs_.move_up_stairs(_horse, _dice_value);
	}
	else
	{
		return e_engine_result::ERROR_UNDEFINED;
	}

	if (_dice_value != 6) next_player();
	return e_engine_result::SUCCESS;
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
