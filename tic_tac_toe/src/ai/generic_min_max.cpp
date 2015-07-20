///
/// \file	min_max.cpp
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///

#if 0
#include <ai/generic_min_max.hpp>
using namespace ai;

/// === Includes	================================================================================

#include <limits>
#include "i_engine.hpp"
//#include "engine/engine.hpp"

//#include <iostream>

/// === Namespaces	================================================================================

using namespace std;
//using namespace engine;

/// === Public Definitions	========================================================================

Min_Max::Min_Max()
{

}

///	------------------------------------------------------------------------------------------------

//	max_val <- -infini
//
//	     Pour tous les coups possibles
//	          simuler(coup_actuel)
//	          val <- Min(etat_du_jeu, profondeur)
//
//	          si val > max_val alors
//	               max_val <- val
//	               meilleur_coup <- coup_actuel
//	          fin si
//
//	          annuler_coup(coup_actuel)
//	     fin pour
//
//	     jouer(meilleur_coup)

ai::move_t Min_Max::compute(IEngine& _iengine) const
{
	auto val = int16_t(0);
	auto best_move = move_t { };
	auto max = numeric_limits < int16_t > ::min();

	for (const auto& move : _iengine.get_moves())
	{
		_iengine.execute_move(make_shared<move_t>(move.get()));

		val = min(_iengine, depth_ - 1);

		if (val > max)
		{
			max = val;
			best_move = move;
		}

		_iengine.undo_move(move);
	}

	return best_move;

//	auto engine = _engine;	/// local instance
//	auto max = numeric_limits<int16_t>::min();
//	auto val = 0L;
//
//	for (auto y = 0U; y < Engine::n_cells; ++y)
//	{
//		for (auto x = 0U; x < Engine::n_cells; ++x)
//		{
//			/// Play move
//			if (engine.add_pawn(x, y) == true)
//			{
//				val = min(engine, _depth - 1);
//
//				if (val > max)
//				{
//					max = val;
//					_x = x;
//					_y = y;
//				}
//
//				/// Cancel played move
//				engine.remove_pawn(x, y);
//			}
//		}
//	}
}

/// === Private Definitions	========================================================================

//fonction Min : entier
//
//     si profondeur = 0 OU fin du jeu alors
//          renvoyer eval(etat_du_jeu)
//
//     min_val <- infini
//
//     Pour tous les coups possibles
//          simuler(coup_actuel)
//          val <- Max(etat_du_jeu, profondeur-1)
//
//          si val < min_val alors
//               min_val <- val
//          fin si
//
//          annuler_coup(coup_actuel)
//     fin pour
//
//     renvoyer min_val
//fin fonction

int16_t Min_Max::min(IEngine& _iengine, uint16_t _depth) const
{
//	auto val = 0L;
//	auto min = numeric_limits<int16_t>::max();
//
//	if (_depth == 0 || _engine.is_game_finished() == true)
//	{
//		return eval(_engine);
//	}
//
//	for (auto y = 0U; y < Engine::n_cells; ++y)
//	{
//		for (auto x = 0U; x < Engine::n_cells; ++x)
//		{
//			/// Play move
//			if (_engine.add_pawn(x, y) == true)
//			{
//				val = max(_engine, _depth - 1);
//
//				if (val < min) min = val;
//
//				/// Cancel played move
//				_engine.remove_pawn(x, y);
//			}
//		}
//	}
//
//	return min;
}

///	------------------------------------------------------------------------------------------------

//fonction Max : entier
//
//     si profondeur = 0 OU fin du jeu alors
//          renvoyer eval(etat_du_jeu)
//
//     max_val <- -infini
//
//     Pour tous les coups possibles
//          simuler(coup_actuel)
//          val <- Min(etat_du_jeu, profondeur-1)
//
//          si val > max_val alors
//               max_val <- val
//          fin si
//
//          annuler_coup(coup_actuel)
//     fin pour
//
//     renvoyer max_val
//fin fonction

int16_t Min_Max::max(IEngine& _iengine, uint16_t _depth) const
{
//	auto val = 0L;
//	auto max = numeric_limits<int16_t>::min();
//
//	if (_depth == 0 || _engine.is_game_finished() == true)
//	{
//		return eval(_engine);
//	}
//
//	for (auto y = 0U; y < Engine::n_cells; ++y)
//	{
//		for (auto x = 0U; x < Engine::n_cells; ++x)
//		{
//			/// Play move
//			if (_engine.add_pawn(x, y) == true)
//			{
//				val = min(_engine, _depth - 1);
//
//				if (val > max) max = val;
//
//				/// Cancel played move
//				_engine.remove_pawn(x, y);
//			}
//		}
//	}
//
//	return max;
}

///	------------------------------------------------------------------------------------------------

int16_t Min_Max::eval(IEngine& _iengine) const
{
//	auto n_cell = 0ULL;
//
//	for (auto& line : _engine.get_grid())
//		for (auto cell : line)
//			if (cell != e_pawn::none) n_cell++;
//
//	auto winner = _engine.get_winner();
//
//	auto result = 0;
//	if (winner == ai_player_) result = 1000 - n_cell;
//	else if (winner == "draw") result = 0;
//	else result = -1000 + n_cell;
//
////	static auto cpt = 0UL;
////	cout << __func__ << cpt++ << "=" << result << endl;
//	return result;
}
#endif
/// === END OF FILES	============================================================================
