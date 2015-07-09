///
/// \file	player.h
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///
#ifndef PLAYER_H_
#define PLAYER_H_

/// === Includes	================================================================================

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "horse.h"

/// === Namespaces	================================================================================

namespace game
{

/// === Class Declarations	========================================================================
/// \class	
/// \brief
/// \date	24 juin 2015
/// \author	nboutin
class Player : public std::enable_shared_from_this<Player>
{
public:
	/// === Public Declarations	====================================================================

	Player(const std::string& _name, uint16_t _home_number);

	inline const std::string& get_name() const
	{
		return name_;
	}

	inline uint16_t get_home_number() const
	{
		return home_number_;
	}

	inline void add_horses(uint8_t _n_horses)
	{
		for (auto i = 0U; i < _n_horses; ++i)
		{
			std::stringstream ss;
			ss << (i + 1);
			horses_.push_back(
					std::make_shared<Horse>(home_number_ * 14, ss.str(), shared_from_this()));
		}
	}

	inline std::shared_ptr<Horse> get_horse(uint8_t _index) const
	{
		return horses_.at(_index);
	}

	inline auto get_horse_count() const -> uint8_t
	{
		return horses_.size();
	}

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================

	std::string name_;
	uint16_t home_number_;
	std::vector<std::shared_ptr<Horse>> horses_;

};

/// === INLINE DEFINITIONS	========================================================================

}

#endif	/// PLAYER_H_
/// === END OF FILE	================================================================================
