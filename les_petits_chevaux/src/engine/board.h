///
/// \file	board.h
///	\brief	
///	\date	24 juin 2015
/// \author	nboutin
///
#ifndef BOARD_H_
#define BOARD_H_

/// === Includes	================================================================================

#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>
//#include "player.h"

/// === Namespaces	================================================================================

namespace game
{

/// === Forward Declarations	====================================================================

class Horse;

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	24 juin 2015
/// \author	nboutin
class Board
{
public:
	/// === Constants Definitions	================================================================

	static const uint8_t n_cells = 56;

	/// === PUBLIC DECLARATIONS	====================================================================

	Board();

	inline const std::vector<std::shared_ptr<Horse>>& get_cells() const
	{
		return cells_;
	}

	inline bool is_free_cell(int16_t _cell_index) const
	{
		/// Shared_ptr is false when empty
		return (cells_[_M_convert_index(_cell_index)] == false) ? true : false;
	}

	bool add_horse(std::shared_ptr<Horse> _horse, uint8_t _cell_index);
	bool remove_horse(uint8_t _cell_index);

	/// Be sure that _horse is on the board before calling this method
	uint8_t get_horse_position(std::shared_ptr<Horse> _horse)
	{
		const auto i = std::find(cells_.begin(), cells_.end(), _horse);
		return (i - cells_.begin());
	}

	inline std::shared_ptr<Horse> get_horse(uint8_t _cell_index)
	{
		return cells_[_M_convert_index(_cell_index)];
	}

private:
	/// === PRIVATE DECLARATIONS	================================================================

	inline uint16_t _M_convert_index(int16_t _cell_index) const
	{
		return ((_cell_index + n_cells) % n_cells);
	}

	/// === PRIVATE ATTRIBUTS	====================================================================

	std::vector<std::shared_ptr<Horse>> cells_;
};

/// === INLINE DEFINITIONS	========================================================================

}

#endif	/// BOARD_H_
/// === END OF FILE	================================================================================
