//============================================================================
// Name        : connect_4.cpp
// Author      : nboutin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/// === Includes	================================================================================

#include <iostream>
#include <sstream>
#include "engine/engine.hpp"
#include "print.hpp"
#include "min_max_generic/min_max_generic.hpp"
#include "min_max_impl/engine_mmg.hpp"

#ifdef TEST
#include "test/test_launcher.hpp"
#endif

/// === Namespaces	================================================================================

using namespace std;
using namespace connect_4;
using namespace print;
using namespace ai::min_max;

/// === Public Definitions	========================================================================

int main()
{
#ifndef TEST
	cout << "Connect 4" << endl;

	auto engine = Engine("P1", "AI");

	auto mmg = Min_Max_Generic<uint8_t> { };
	auto ai_engine = Engine_MMG { engine, "AI" };

	auto is_quit = false;
	auto str_input = string { };
	auto x = uint16_t { };
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
			if (current_player == "P1" || current_player == "P2")
			{
				cout << "Select column: ";
				getline(cin, str_input);
				stringstream(str_input) >> x;
			}
			else
			{
				x = mmg.compute(ai_engine);
				cout << "AI: " << x << endl;
			}

			engine_result = engine.add_pawn(x);
		}
		while (engine_result == false);
	}

	print_grid(engine);

	/// Display end of game
	cout << "Winner is " << engine.get_winner() << endl;

	cout << "===== End of Game =====" << endl;

	return 0;
#else

	using namespace test;

	test_launch();

	return 0;
#endif
}
///	=== END OF FILE	================================================================================
