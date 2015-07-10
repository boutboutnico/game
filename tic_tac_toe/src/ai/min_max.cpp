///
/// \file	min_max.cpp
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///

#include <ai/min_max.hpp>
using namespace ai;

/// === Includes	================================================================================

#include <limits>
#include "engine/engine.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace engine;

/// === Public Definitions	========================================================================

Min_Max::Min_Max(const std::string& _ai_player)
		: ai_player_(_ai_player)
{

}

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
void Min_Max::compute(const Engine& _engine, uint8_t& _x, uint8_t& _y)
{
	auto engine = _engine;
	auto max = numeric_limits<int16_t>::max();
	auto val = 0L;
	auto depth = 2U;

	for (auto y = 0U; y < Engine::n_cells; ++y)
	{
		for (auto x = 0U; x < Engine::n_cells; ++x)
		{
			/// Play move
			if (engine.add_pawn(x, y) == true)
			{
				val = min(engine, depth - 1);

				if (val > max)
				{
					max = val;
					_x = x;
					_y = y;
				}

				/// Cancel played move
				engine.remove_pawn(x, y);
			}
		}
	}
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

int16_t Min_Max::min(engine::Engine& _engine, uint8_t _depth)
{
	auto val = 0L;
	auto min = numeric_limits<int16_t>::min();

	if (_depth == 0 || _engine.is_game_finished() == true)
	{
		return eval(_engine);
	}

	for (auto y = 0U; y < Engine::n_cells; ++y)
	{
		for (auto x = 0U; x < Engine::n_cells; ++x)
		{
			/// Play move
			if (_engine.add_pawn(x, y) == true)
			{
				val = max(_engine, _depth - 1);

				if (val < min) min = val;

				/// Cancel played move
				_engine.remove_pawn(x, y);
			}
		}
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

int16_t Min_Max::max(engine::Engine& _engine, uint8_t _depth)
{
	auto val = 0L;
	auto max = numeric_limits<int16_t>::max();

	if (_depth == 0 || _engine.is_game_finished() == true)
	{
		return eval(_engine);
	}

	for (auto y = 0U; y < Engine::n_cells; ++y)
	{
		for (auto x = 0U; x < Engine::n_cells; ++x)
		{
			/// Play move
			if (_engine.add_pawn(x, y) == true)
			{
				val = min(_engine, _depth - 1);

				if (val > max) max = val;

				/// Cancel played move
				_engine.remove_pawn(x, y);
			}
		}
	}

	return max;
}

///	------------------------------------------------------------------------------------------------

int16_t Min_Max::eval(engine::Engine& _engine)
{
	auto winner = _engine.get_winner();

	if (winner == ai_player_) return 1000;
	else if (winner == "draw") return 0;
	else return -1000;
}

/// === END OF FILES	============================================================================
