///
/// \file	ai_engine_wrapper.h
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_GMM_HPP_
#define ENGINE_GMM_HPP_

/// === Includes	================================================================================

#include <min_max_generic/min_max_engine.hpp>
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
class Engine_MMG : public ai::min_max::Min_Max_Engine<move_t>
{
public:
	/// === Public Declarations	====================================================================

	Engine_MMG(Engine& _engine, const std::string& _ai_player);

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

	Engine& engine_;
	std::string ai_player_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
