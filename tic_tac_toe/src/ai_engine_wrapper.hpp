///
/// \file	ai_engine_wrapper.h
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///
#ifndef AI_ENGINE_WRAPPER_HPP_
#define AI_ENGINE_WRAPPER_HPP_

/// === Includes	================================================================================

#include "ai/i_engine.hpp"

///	===	Forward Declarations	====================================================================

namespace engine
{
class Engine;
}

/// === Namespaces	================================================================================
namespace tic_tac_toe
{

class move_xy : public ai::move_t
{
public:
	move_xy(uint8_t _x, uint8_t _y)
			: x_(_x), y_(_y)
	{
	}

	uint8_t x_;
	uint8_t y_;
};

/// === Class Declarations	========================================================================
class AI_Engine_Wrapper : public ai::IEngine
{
public:
	/// === Public Declarations	====================================================================

	AI_Engine_Wrapper(engine::Engine& _engine);

	virtual std::vector<std::unique_ptr<ai::move_t>> get_moves() const;
	virtual void execute_move(const std::shared_ptr<ai::move_t> _move) const;
	virtual void undo_move(const std::shared_ptr<ai::move_t> _move) const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	engine::Engine& engine_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
