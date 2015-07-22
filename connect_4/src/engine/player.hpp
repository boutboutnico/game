///
/// \file	player.hpp
///	\brief	
///	\date	22 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_PLAYER_HPP_
#define ENGINE_PLAYER_HPP_

/// === Includes	================================================================================

#include <string>
#include <iostream>
#include <vector>

/// === Namespaces	================================================================================
namespace connect_4
{
///	===	Public Enumerations	========================================================================

enum class e_pawn
{
	none,
	cross,
	circle,
};

/// === Class Declarations	========================================================================
class Player
{
public:
	/// === Public Declarations	====================================================================

	Player(const std::string& _name, e_pawn _pawn);

	///	---	Accessors	----------------------------------------------------------------------------

	inline const std::string& get_name() const
	{
		return name_;
	}

	inline e_pawn get_pawn() const
	{
		return pawn_;
	}

	inline void add_move(uint8_t _move)
	{
		history_.push_back(_move);
	}

	inline const std::vector<uint8_t> get_history() const
	{
		return history_;
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	std::string name_;
	e_pawn pawn_;
	std::vector<uint8_t> history_;
};

///	=== Operators Definitions	====================================================================

inline std::ostream& operator<<(std::ostream& _os, const e_pawn& _p)
{
	auto str = std::string { (_p == e_pawn::circle) ? "()" : (_p == e_pawn::cross) ? "><" : "--" };
	_os << str;
	return _os;
}

///	------------------------------------------------------------------------------------------------

inline std::ostream& operator<<(std::ostream& _os, const Player& _p)
{
//	auto str = std::string { (_p.get_pawn() == e_pawn::circle) ? "()" : "><" };
	_os << _p.get_name() << " [" << _p.get_pawn() << "]";
	return _os;
}

///	------------------------------------------------------------------------------------------------

inline bool operator==(const Player& _p1, const Player& _p2)
{
	return (_p1.get_name() == _p2.get_name() && _p1.get_pawn() == _p2.get_pawn()) ? true : false;
}

///	------------------------------------------------------------------------------------------------

inline bool operator!=(const Player& lhs, const Player& rhs)
{
	return !(lhs == rhs);
}

///	------------------------------------------------------------------------------------------------
}

#endif
/// === END OF FILE	================================================================================
