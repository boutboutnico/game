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
#include <string>

/// ===	Forward Declarations	====================================================================

namespace engine
{
class Engine;
}

/// === Namespaces	================================================================================
namespace ai
{

/// === Class Declarations	========================================================================
class Min_Max
{
public:
	/// === Public Declarations	====================================================================

	Min_Max(const std::string& _ai_player);

	void compute(const engine::Engine& _engine, uint16_t _depth, uint16_t& _x, uint16_t& _y);

private:
	/// === Private Declarations	================================================================

	int16_t min(engine::Engine& _engine, uint8_t _depth);

	int16_t max(engine::Engine& _engine, uint8_t _depth);

	int16_t eval(engine::Engine& _engine);

	/// === Private Attributs	====================================================================

	std::string ai_player_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
