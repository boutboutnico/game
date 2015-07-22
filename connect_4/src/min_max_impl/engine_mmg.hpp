///
/// \file	ai_engine_wrapper.h
///	\brief	
///	\date	16 juil. 2015
/// \author	nboutin
///
#ifndef ENGINE_GMM_HPP_
#define ENGINE_GMM_HPP_

/// === Includes	================================================================================

#include <mutex>
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

	Engine_MMG(Engine& _engine, const std::string& _ai_player);
//	Engine_MMG(const Engine_MMG& _src) = default;
	virtual ~Engine_MMG()
	{
	}

//	virtual Engine_MMG* clone() const
//	{
//		return new Engine_MMG(*this);
//	}

	virtual std::vector<uint8_t> get_moves() const;
	virtual void execute_move(const uint8_t& _move) const;
	virtual void undo_move(const uint8_t& _move) const;
	virtual int16_t eval() const;

	virtual bool is_game_finished() const
	{
		std::lock_guard<std::mutex> lock(mut_);
		return engine_.is_game_finished();
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	Engine& engine_;
	std::string ai_player_;
	mutable std::mutex mut_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
