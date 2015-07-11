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

#include "engine/engine.hpp"
#include "ai/min_max.hpp"
#include "print.hpp"

#ifdef TEST
#include "test/test.hpp"
using namespace test;
#endif

///	=== Namespaces	================================================================================

using namespace std;
using namespace engine;
using namespace ai;
using namespace print;

///	===	Public Definitions	========================================================================

#ifndef TEST

int main()
{
	cout << "TIC TAC TOE" << endl;

	auto engine = Engine("P1", "AI");
	auto ai = Min_Max { "AI" };

	auto is_quit = false;
	auto str_input = string { };
	uint16_t x = 0U, y = 0U;
	auto engine_result = false;
	auto level = 0U;

	cout << "Set AI level: ";
	getline (cin, str_input);
	stringstream(str_input) >> level;

	while (engine.is_game_finished() == false && is_quit == false)
	{
		auto current_player = engine.get_current_player();
		cout << "=====\t" << current_player << "\t=====" << endl;

		do
		{
			if (current_player == "P1")
			{
				cout << "Select cell(x y): ";
				getline(cin, str_input);
				stringstream(str_input) >> x >> y;
			}
			else
			{
				ai.compute(engine, level, x, y);
				cout << "AI: " << x << " " << y << endl;
			}

			engine_result = engine.add_pawn(x, y);
		}
		while (engine_result == false);

		print_grid(engine);
	}

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
