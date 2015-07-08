///
/// \file	stairs.hpp
///	\brief	
///	\date	8 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_STAIRS_HPP_
#define ENGINE_STAIRS_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <vector>
#include <memory>

/// === Namespaces	================================================================================

namespace game
{

/// === Forward Declarations	====================================================================

enum class e_engine_result
: uint8_t;
class Horse;

/// === Class Declarations	========================================================================

class Stairs
{
public:
	/// === Public Declarations	====================================================================

	Stairs();

	e_engine_result move_up_stairs(std::shared_ptr<Horse> _horse, uint8_t _dice);

	///	---	Accessors	----------------------------------------------------------------------------

	const std::vector<std::vector<std::shared_ptr<Horse>>>&get_stairs() const
	{
		return stairs_;
	}

private:
	///	===	Private Constants	====================================================================

	static const uint8_t n_stairs = 6;

	///	=== Private Declarations	================================================================

	inline void _M_add(std::shared_ptr<Horse> _horse, uint8_t _dice)
	{
		stairs_[_dice - 1].push_back(_horse);
	}

	uint8_t _M_get_position(const std::shared_ptr<Horse> _horse) const;
	void _M_remove(std::shared_ptr<Horse> _horse, uint8_t _horse_position);

	/// === Private Attributs	====================================================================

	std::vector<std::vector<std::shared_ptr<Horse>>>stairs_;
};
///	------------------------------------------------------------------------------------------------
}
#endif	/// ENGINE_STAIRS_HPP_
/// === END OF FILE	================================================================================
