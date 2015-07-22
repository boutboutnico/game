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
#include <thread>
#include <mutex>

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

	inline void set_depth(uint16_t _depth)
	{
		depth_ = _depth;
	}

private:
	/// === Private Declarations	================================================================

	int16_t min(const Min_Max_Engine<T>& _engine, uint16_t _depth) const;
	int16_t max(const Min_Max_Engine<T>& _engine, uint16_t _depth) const;

	void task(	const Min_Max_Engine<T>* _engine,
				uint16_t _depth,
				const T& _move,
				int16_t* _val) const;

/// === Private Attributs	====================================================================

	uint16_t depth_ = 10;
	mutable std::mutex mut_;
};
///	------------------------------------------------------------------------------------------------

/// === Public Definitions	========================================================================

template<class T>
void Min_Max_Generic<T>::task(	const Min_Max_Engine<T>* _engine,
								uint16_t _depth,
								const T& _move,
								int16_t* _val) const
{
	std::lock_guard<std::mutex> lock(mut_);
	_engine->execute_move(_move);
	*_val = min(*_engine, _depth - 1);
	_engine->undo_move(_move);
}

///	------------------------------------------------------------------------------------------------
/*
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
 */
#define no_thread 0
template<class T>
T Min_Max_Generic<T>::compute(const Min_Max_Engine<T>& _engine) const
{
	T best_move;
	auto max = std::numeric_limits<int16_t>::min();

#if no_thread

	auto val = int16_t
	{	0}, t_val = int16_t
	{	0};
	const auto& moves = _engine.get_moves();

	_engine.execute_move(moves[0]);
//	auto clone = _engine.clone();
	std::thread t(&Min_Max_Generic<T>::task, this, &_engine, depth_, &t_val);
	_engine.undo_move(moves[0]);

	for (auto i = uint16_t
			{	1}; i < moves.size(); ++i)
	{
		_engine.execute_move(moves[i]);

		val = min(_engine, depth_ - 1);

		if (val > max)    ///|| ((val == max) && (rand() % 2 == 0)))
		{
			max = val;
			best_move = moves[i];
		}

		_engine.undo_move(moves[i]);
	}

	t.join();
//	delete clone;

	if (t_val >= max)
	{
		best_move = moves[0];
	}

#else
	const auto& moves = _engine.get_moves();
	auto threads = std::vector<std::thread> { };
	auto values = std::vector<int16_t>(0, moves.size());

	for (auto m = uint16_t { }; m < moves.size(); ++m)
	{
		threads.push_back(
				std::thread(&Min_Max_Generic<T>::task, this, &_engine, depth_, moves[m],
							&values[m]));
	}

	for (auto& t : threads)
	{
		t.join();
	}

	for (auto i = uint16_t { }; i < values.size(); ++i)
	{
		if (values[i] > max)
		{
			max = values[i];
			best_move = moves[i];
		}
	}

#endif

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
