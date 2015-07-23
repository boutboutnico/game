//============================================================================
// Name        : tic_tac_toe.cpp
// Author      : nboutin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

///	=== Includes	================================================================================

#include <iostream>
#include <string>
#include <sstream>

#include <min_max_generic/min_max_generic.hpp>
#include <min_max_impl/engine_mmg.hpp>
#include "engine/engine.hpp"
#include "print.hpp"

#ifdef TEST
#include "test/test.hpp"
using namespace test;
#endif

///	=== Namespaces	================================================================================

using namespace std;
using namespace ai::min_max;
using namespace print;
using namespace tic_tac_toe;

///	===	Public Definitions	========================================================================

#ifndef TEST

int main()
{
	cout << "TIC TAC TOE" << endl;

	auto engine = Engine("P1", "AI");
	auto ai_engine = Engine_MMG { engine, "AI" };
	auto mmg = Min_Max_Generic<tic_tac_toe::move_t> { };

	auto is_quit = false;
	auto str_input = string { };
	auto move = move_t { };
	auto engine_result = false;

	cout << "Set AI level: ";
	getline(cin, str_input);
	auto level = int16_t { 0 };
	stringstream(str_input) >> level;
	mmg.set_depth(level);

	while (engine.is_game_finished() == false && is_quit == false)
	{
		print_grid(engine);

		auto current_player = engine.get_current_player();
		cout << "=====\t" << current_player << "\t=====" << endl;

		do
		{
			if (current_player == "P1")
			{
				cout << "Select cell(x y): ";
				getline(cin, str_input);
				auto x = uint16_t { }, y = uint16_t { };
				stringstream(str_input) >> x >> y;
				move =
				{	static_cast<uint8_t>(x) , static_cast<uint8_t>(y)};
			}
			else
			{
				move = mmg.compute(ai_engine);
				cout << "AI: " << int16_t(move.x_) << " " << int16_t(move.y_) << endl;
				move = mmg.minimax(ai_engine);
				cout << "AI: " << int16_t(move.x_) << " " << int16_t(move.y_) << endl;
			}

			engine_result = engine.add_pawn(move.x_, move.y_);
		}
		while (engine_result == false);
	}

	print_grid(engine);

	/// Display end of game
	cout << "Winner is " << engine.get_winner() << endl;

	cout << "===== End of Game =====" << endl;

	return 0;
}

#else

int main()
{
	run_test();
}

#endif

///	===	END OF FILE	================================================================================
