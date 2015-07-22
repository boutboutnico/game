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
namespace min_max
{
/// === Class Declarations	========================================================================
template<class T>
class Min_Max_Engine
{
public:
	/// === Public Declarations	====================================================================

//	virtual ~Min_Max_Engine(){};

//	virtual Min_Max_Engine* clone() const = 0;

	virtual std::vector<T> get_moves() const = 0;
	virtual void execute_move(const T& _move) const = 0;
	virtual void undo_move(const T& _move) const = 0;

	virtual bool is_game_finished() const = 0;
	virtual int16_t eval() const = 0;
};

///	------------------------------------------------------------------------------------------------

}
}
#endif
/// === END OF FILE	================================================================================
