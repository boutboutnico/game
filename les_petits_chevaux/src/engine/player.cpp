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

Player::Player(const std::string& _name, uint16_t _home_number)
		: 	name_(_name),
			home_number_(_home_number)
//			horses_(_n_horse, std::make_shared<Horse>(shared_from_this()))
{

}

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================
