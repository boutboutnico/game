///
/// \file	pawn.h
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///
#ifndef HORSE_H_
#define HORSE_H_

/// === Includes	================================================================================

#include <cstdint>
#include <memory>

/// === Namespaces	================================================================================
namespace game
{

/// ===  Forward Declarations	====================================================================

class Player;

enum class e_horse_status
	: uint8_t
	{
		AT_HOME,
	ON_BOARD,
	ON_STAIRS,
	HAVE_FINISHED,
};

/// === Class Declarations	========================================================================
/// \class	
/// \brief
/// \date	24 juin 2015
/// \author	nboutin
class Horse
{
public:
	/// === Public Declarations	====================================================================

	Horse(const std::string& _name, std::weak_ptr<Player> _player)
			: e_status_(e_horse_status::AT_HOME), name_(_name), player_(_player)
	{
	}

	inline e_horse_status get_status() const
	{
		return e_status_;
	}

	inline void set_status(e_horse_status _status)
	{
		e_status_ = _status;
	}

	inline const std::string& get_name() const
	{
		return name_;
	}

	inline std::weak_ptr<Player> get_player() const
	{
		return player_;
	}

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================

	e_horse_status e_status_;
	std::string name_;
	std::weak_ptr<Player> player_;
};

/// === INLINE DEFINITIONS	========================================================================

}

#endif	/// HORSE_H_
/// === END OF FILE	================================================================================