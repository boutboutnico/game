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
#include <cstdlib>
#include <ctime>

#include <min_max_generic/min_max_engine.hpp>

/// === Namespaces	================================================================================

namespace ai
{
namespace min_max
{
/// === Class Declarations	========================================================================

template<class T>
class Min_Max_Generic
{
public:
	/// === Public Declarations	====================================================================

	Min_Max_Generic()
	{
		std::srand(std::time(0));
	}

	T compute(const Min_Max_Engine<T>& _engine) const;
	T minimax(const Min_Max_Engine<T>& _engine) const;

	inline void set_depth(uint16_t _depth)
	{
		depth_ = _depth;
	}

private:
	/// === Private Declarations	================================================================

	void minimax(	const Min_Max_Engine<T>& _engine,
					uint16_t _player,
					uint16_t _depth,
					int16_t& _val_best,
					T& _move_best) const;

	int16_t min(const Min_Max_Engine<T>& _engine, uint16_t _depth) const;
	int16_t max(const Min_Max_Engine<T>& _engine, uint16_t _depth) const;

/// === Private Attributs	====================================================================

	uint16_t depth_ = 10;
};
///	------------------------------------------------------------------------------------------------

/// === Public Definitions	========================================================================

template<class T>
T Min_Max_Generic<T>::minimax(const Min_Max_Engine<T>& _engine) const
{
	auto val_best = int16_t { };
	auto move_best = T { };
	minimax(_engine, 0, depth_, val_best, move_best);
	return move_best;
}

///	------------------------------------------------------------------------------------------------

//function minimax(State, Player)
//  if (State is terminal):
//    Return Result(State);
//  if (Player):
//    bestValue = -inf;
//    for each possible play P from state:
//      value = minimax(P);
//      if (value > bestValue):
//        bestValue = value;
//    return bestValue
//  else:
//    bestValue = +inf;
//    for each possible play P from state:
//      value = minimax(P);
//      if (value < bestValue):
//        bestValue = value;
//    return bestValue

template<class T>
void Min_Max_Generic<T>::minimax(	const Min_Max_Engine<T>& _engine,
									uint16_t _player,
									uint16_t _depth,
									int16_t& _val_best,
									T& _move_best) const
{
	if (_depth == 0 || _engine.is_game_finished() == true)
	{
		_val_best = _engine.eval();
		return;
	}

	if (_player % 2 == 0)
	{
		auto val_best = std::numeric_limits<int16_t>::min();
		auto move_best = T { };

		for (const auto& move : _engine.get_moves())
		{
			auto val = int16_t { };

			_engine.execute_move(move);

			minimax(_engine, _player + 1, _depth - 1, val, move_best);
			if (val > val_best)
			{
				val_best = val;
				move_best = move;
			}
			_engine.undo_move(move);
		}

		_val_best = val_best;
		_move_best = move_best;
		return;
	}
	else
	{
		auto val_best = std::numeric_limits<int16_t>::max();
		auto move_best = T { };

		for (const auto& move : _engine.get_moves())
		{
			auto val = int16_t { };

			_engine.execute_move(move);

			minimax(_engine, _player + 1, _depth - 1, val, move_best);
			if (val < val_best)
			{
				val_best = val;
				move_best = move;
			}
			_engine.undo_move(move);
		}

		_val_best = val_best;
		_move_best = move_best;
		return;
	}
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
template<class T>
T Min_Max_Generic<T>::compute(const Min_Max_Engine<T>& _engine) const
{
	auto val = int16_t { 0 };
	auto best_move = T { };
	auto max = std::numeric_limits<int16_t>::min();

	for (const auto& move : _engine.get_moves())
	{
		_engine.execute_move(move);

		val = min(_engine, depth_ - 1);

		if (val > max)    ///|| ((val == max) && (rand() % 2 == 0)))
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
int16_t Min_Max_Generic<T>::min(const Min_Max_Engine<T>& _engine, uint16_t _depth) const
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
int16_t Min_Max_Generic<T>::max(const Min_Max_Engine<T>& _engine, uint16_t _depth) const
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
///	------------------------------------------------------------------------------------------------
}
}
#endif
/// === END OF FILE	================================================================================
