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
#include <chrono>

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

/// TODO
///	- use time limit for ai
/// - randomize move if several are equals
/// - minmax alpha-beta pruning

int main()
{
#ifndef TEST
	cout << "Connect 4" << endl;

	auto is_quit = false;

	while (is_quit == false)
	{
		auto mmg = Min_Max_Generic<uint8_t> { };
		auto str_input = string { };
		auto x = uint16_t { };
		auto engine_result = false;

		cout << "Set AI level: ";
		getline(cin, str_input);
		auto level = int16_t { 0 };
		stringstream(str_input) >> level;
		mmg.set_depth(level);

		auto player_1 = Player { "AI1", e_pawn::cross };
		auto player_2 = Player { "AI2", e_pawn::circle };

		auto engine = Engine { player_1, player_2 };
		auto ai_engine_1 = Engine_MMG { engine, player_1 };
		auto ai_engine_2 = Engine_MMG { engine, player_2 };
		auto n_turn = uint16_t { };

		while (engine.is_game_finished() == false)
		{
			print_grid(engine);

			auto& current_player = engine.get_current_player();
			cout << "=====\t" << current_player << " T:" << ++n_turn << "\t=====" << endl;

			do
			{
				auto t1 = std::chrono::high_resolution_clock::now();

				if (current_player.get_name() == "AI1")
				{
					x = mmg.compute(ai_engine_1);
				}
				else if (current_player.get_name() == "AI2")
				{
					x = mmg.compute(ai_engine_2);
				}
				else
				{
					cout << "Select column: ";
					getline(cin, str_input);
					stringstream(str_input) >> x;
					--x;
				}

				auto t2 = std::chrono::high_resolution_clock::now();
				auto duration =
						std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

				cout << "Move: " << x + 1 << " (" << duration << " ms)" << endl;

				current_player.add_move(x + 1);
				engine_result = engine.add_pawn(x);
			}
			while (engine_result == false);
		}

		print_grid(engine);

		/// Display end of game
		cout << "Winner is " << engine.get_winner() << " (AI level: " << level << ")" << endl;

		cout << "===== End of Game =====" << endl << endl;

		cout << "History" << endl;

		cout << "n turn: " << n_turn << endl;

		cout << player_1.get_name() << ":\t";
		for (auto i : player_1.get_history())
			cout << " " << uint16_t(i);
		cout << endl;

		cout << player_2.get_name() << ":\t";
		for (auto i : player_2.get_history())
			cout << " " << uint16_t(i);
		cout << endl;

		cout << "Play again (y/n): ";
		getline(cin, str_input);
		if (str_input == "n") is_quit = true;
	}

	return 0;
#else

	using namespace test;

	test_launch();

	return 0;
#endif
}
///	=== END OF FILE	================================================================================
