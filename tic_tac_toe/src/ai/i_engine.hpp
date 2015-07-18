///
/// \file	i_engine.hpp
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///
#ifndef AI_I_ENGINE_HPP_
#define AI_I_ENGINE_HPP_

/// === Includes	================================================================================

#include <vector>
#include <memory>

/// === Namespaces	================================================================================
namespace ai
{
/// === Structures Declarations	====================================================================

class move_t
{
public:
	virtual ~move_t()
	{
	}
};

/// === Class Declarations	========================================================================
class IEngine
{
public:
	/// === Public Declarations	====================================================================

	virtual std::vector<std::unique_ptr<move_t>> get_moves() const = 0;
	virtual void execute_move(const std::shared_ptr<move_t> _move) const = 0;
	virtual void undo_move(const std::shared_ptr<move_t> _move) const = 0;

};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
