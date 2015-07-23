///
/// \file	ai_engine_wrapper.h
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_GMM_HPP_
#define ENGINE_GMM_HPP_

/// === Includes	================================================================================

#include "min_max_generic/min_max_engine.hpp"
#include "engine/engine.hpp"

/// === Namespaces	================================================================================
namespace connect_4
{

/// === Class Declarations	========================================================================
class Engine_MMG : public ai::min_max::Min_Max_Engine<uint8_t>
{
public:
	/// === Public Declarations	====================================================================

	Engine_MMG(Engine& _engine, Player& _ai_player);

	virtual std::vector<uint8_t> get_moves() const;
	virtual void execute_move(const uint8_t& _move) const;
	virtual void undo_move(const uint8_t& _move) const;
	virtual int16_t eval() const;

	virtual bool is_game_finished() const
	{
		return engine_.is_game_finished();
	}

private:
	///	=== Private Structures	====================================================================
	struct point_t
	{
		int8_t x, y;

//		void inc()
//		{
//
//		}
	};

	/// === Private Declarations	================================================================

	inline bool is_in_bound(int8_t x, int8_t y) const
	{
		return (y < 0 || y >= Engine::height || x < 0 || x >= Engine::width) ? false : true;
	}

	int16_t draw_eval(uint8_t _depth) const;
	int16_t point_eval(int8_t _x, int8_t _y, point_t _p, uint8_t _depth) const;
	int16_t eval(int8_t _x, int8_t _y, point_t _p) const;

	/// === Private Attributs	====================================================================

	Engine& engine_;
	Player& ai_player_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
