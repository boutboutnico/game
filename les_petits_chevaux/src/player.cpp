///
/// \file	player.cpp
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///

#include "player.h"
using namespace game;

/// === Includes	================================================================================

/// === Namespaces	================================================================================

/// === PUBLIC DEFINITIONS	========================================================================

Player::Player(const std::string& _name, uint16_t _home_position)
		: 	name_(_name),
			home_position_(_home_position)
//			horses_(_n_horse, std::make_shared<Horse>(shared_from_this()))
{

}

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================
