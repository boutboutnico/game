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
	/// === Public Constants	====================================================================

	static const int16_t wall_coef = -5;
	static const int16_t player_coef = 10;
	static const int16_t empty_coef = 5;
	static const int16_t adversary_coef = -10;

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

	void set_draw_eval_depth(uint8_t _depth)
	{
		draw_eval_depth_ = _depth;
	}

private:
	///	=== Private Structures	====================================================================
	struct point_t
	{
		int8_t x, y;
	};

	/// === Private Declarations	================================================================

	inline bool is_in_bound(int8_t x, int8_t y) const
	{
		return (y < 0 || y >= Engine::height || x < 0 || x >= Engine::width) ? false : true;
	}

	int16_t draw_eval(uint8_t _depth) const;
	int16_t point_eval(	uint8_t _x,
						uint8_t _y,
						point_t _p_move,
						point_t _p_next,
						uint8_t _depth) const;
	int16_t eval(int8_t _x, int8_t _y, point_t _p) const;

	/// === Private Attributs	====================================================================

	Engine& engine_;
	Player& ai_player_;
	uint8_t draw_eval_depth_ = 2;

#ifdef TEST
	friend int16_t friend_draw_eval(Engine_MMG& _mmg, uint8_t _depth)
	{
		return _mmg.draw_eval(_depth);
	}
#endif
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
