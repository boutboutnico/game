///
/// \file	min_max.h
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///
#ifndef AI_GENERIC_MIN_MAX_HPP_
#define AI_GENERIC_MIN_MAX_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <limits>

#include "i_engine.hpp"

/// === Namespaces	================================================================================

namespace ai
{

/// === Class Declarations	========================================================================

template<class T>
class Generic_Min_Max
{
public:
	/// === Public Declarations	====================================================================

	T compute(const IEngine<T>& _engine) const;

private:
	/// === Private Declarations	================================================================

	int16_t min(const IEngine<T>& _engine, uint16_t _depth) const;

	int16_t max(const IEngine<T>& _engine, uint16_t _depth) const;

/// === Private Attributs	====================================================================

	uint16_t depth_ = 10;
};
///	------------------------------------------------------------------------------------------------

/// === Public Definitions	========================================================================
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
template<class T>
T Generic_Min_Max<T>::compute(const IEngine<T>& _engine) const
{
	auto val = int16_t { 0 };
	T best_move;
	auto max = std::numeric_limits<int16_t>::min();

	for (const auto& move : _engine.get_moves())
	{
		_engine.execute_move(move);

		val = min(_engine, depth_ - 1);

		if (val > max)
		{
			max = val;
			best_move = move;
		}

		_engine.undo_move(move);
	}

	return best_move;
}

///	------------------------------------------------------------------------------------------------

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

template<class T>
int16_t Generic_Min_Max<T>::min(const IEngine<T>& _engine, uint16_t _depth) const
{
	auto val = int16_t { 0 };
	auto min = std::numeric_limits<int16_t>::max();

	if (_depth == 0 || _engine.is_game_finished() == true)
	{
		return _engine.eval();
	}

	for (const auto& move : _engine.get_moves())
	{
		_engine.execute_move(move);

		val = max(_engine, _depth - 1);

		if (val < min) min = val;

		_engine.undo_move(move);
	}

	return min;
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

template<class T>
int16_t Generic_Min_Max<T>::max(const IEngine<T>& _engine, uint16_t _depth) const
{
	auto val = int16_t { 0 };
	auto max = std::numeric_limits<int16_t>::min();

	if (_depth == 0 || _engine.is_game_finished() == true)
	{
		return _engine.eval();
	}

	for (const auto& move : _engine.get_moves())
	{
		_engine.execute_move(move);

		val = min(_engine, _depth - 1);

		if (val > max) max = val;

		_engine.undo_move(move);
	}

	return max;
}

}

#endif
/// === END OF FILE	================================================================================
