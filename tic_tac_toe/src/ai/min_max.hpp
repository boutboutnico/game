///
/// \file	min_max.h
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///
#ifndef AI_MIN_MAX_HPP_
#define AI_MIN_MAX_HPP_

/// === Includes	================================================================================

#include <cstdint>
//#include <string>

/// ===	Forward Declarations	====================================================================


/// === Namespaces	================================================================================
namespace ai
{
/// ===	Forward Declarations	====================================================================

struct move_t;
class IEngine;

/// === Class Declarations	========================================================================
class Min_Max
{
public:
	/// === Public Declarations	====================================================================

	Min_Max();

	move_t compute(ai::IEngine& _iengine) const;

private:
	/// === Private Declarations	================================================================

	int16_t min(ai::IEngine& _iengine, uint16_t _depth) const;

	int16_t max(ai::IEngine& _iengine, uint16_t _depth) const;

	int16_t eval(ai::IEngine& _iengine) const;

	/// === Private Attributs	====================================================================

	uint16_t depth_ = 10;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
