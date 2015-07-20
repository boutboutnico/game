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
#include "engine/engine.hpp"

/// === Namespaces	================================================================================
namespace tic_tac_toe
{

struct move_t
{
	move_t() = default;
	move_t(uint8_t _x, uint8_t _y)
			: x_(_x), y_(_y)
	{
	}

	uint8_t x_ = 0;
	uint8_t y_ = 0;
};

/// === Class Declarations	========================================================================
class AI_Engine_Wrapper : public ai::IEngine<move_t>
{
public:
	/// === Public Declarations	====================================================================

	AI_Engine_Wrapper(engine::Engine& _engine, const std::string& _ai_player);

	virtual std::vector<move_t> get_moves() const;
	virtual void execute_move(const move_t& _move) const;
	virtual void undo_move(const move_t& _move) const;
	virtual int16_t eval() const;

	virtual bool is_game_finished() const
	{
		return engine_.is_game_finished();
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	engine::Engine& engine_;
	std::string ai_player_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
