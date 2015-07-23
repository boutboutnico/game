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

///	=== Public Declarations	========================================================================

uint16_t ask_ai_level();

/// === Public Definitions	========================================================================

/// TODO
///	- use time limit for ai
/// - randomize move if several are equals
/// - minmax alpha-beta pruning

int main()
{
#ifndef TEST
	cout << "=====\tConnect4\t=====" << endl << endl;

	auto str_input = string { };
	auto is_quit = false;

	while (is_quit == false)
	{
		///	=========================

		cout << "Choose an option:" << endl;
		cout << "1- Human vs Human" << endl;
		cout << "2- Human vs AI" << endl;
		cout << "3- AI vs Human" << endl;
		cout << "4- AI vs AI" << endl;
		getline(cin, str_input);
		auto option = int16_t { 0 };
		stringstream(str_input) >> option;
		cout << endl;

		///	=========================

		auto player_1 = unique_ptr<Player> { };
		auto player_2 = unique_ptr<Player> { };

		auto mmg = Min_Max_Generic<uint8_t> { };
		auto ai_level_1 = uint16_t { };
		auto ai_level_2 = uint16_t { };

		switch (option)
		{
		case 1:
		{
			auto p1 = unique_ptr<Player>(new Player { "P1", e_pawn::cross });
			auto p2 = unique_ptr<Player>(new Player { "P2", e_pawn::circle });
			player_1 = move(p1);
			player_2 = move(p2);
			break;
		}
		case 2:
		{
			auto p1 = unique_ptr<Player>(new Player { "P1", e_pawn::cross });
			auto p2 = unique_ptr<Player>(new Player { "AI2", e_pawn::circle });
			player_1 = move(p1);
			player_2 = move(p2);
			ai_level_2 = ask_ai_level();
			break;
		}
		case 3:
		{
			auto p1 = unique_ptr<Player>(new Player { "AI1", e_pawn::cross });
			auto p2 = unique_ptr<Player>(new Player { "P2", e_pawn::circle });
			player_1 = move(p1);
			player_2 = move(p2);
			ai_level_1 = ask_ai_level();
			break;
		}
		case 4:
		{
			auto p1 = unique_ptr<Player>(new Player { "AI1", e_pawn::cross });
			auto p2 = unique_ptr<Player>(new Player { "AI2", e_pawn::circle });
			player_1 = move(p1);
			player_2 = move(p2);
			ai_level_1 = ask_ai_level();
			ai_level_2 = ask_ai_level();
			break;
		}
		default:
			return 0;
		}

		auto n_turn = uint16_t { };
		auto engine = Engine { *player_1, *player_2 };

		auto ai_engine_1 = Engine_MMG { engine, *player_1 };
		auto ai_engine_2 = Engine_MMG { engine, *player_2 };

		while (engine.is_game_finished() == false)
		{
			print_grid(engine);

			auto engine_result = false;
			auto x = uint16_t { };
			auto& current_player = engine.get_current_player();
			cout << "=====\t" << current_player << " T:" << ++n_turn << "\t=====" << endl;

			do
			{
				auto t1 = std::chrono::high_resolution_clock::now();

				if (current_player.get_name() == "AI1")
				{
					mmg.set_depth(ai_level_1);
					x = mmg.compute(ai_engine_1);
				}
				else if (current_player.get_name() == "AI2")
				{
					mmg.set_depth(ai_level_2);
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
		cout << "Winner is " << engine.get_winner() << " (AI level: " << ai_level_1 << "&"
				<< ai_level_2 << ")" << endl;

		cout << "===== End of Game =====" << endl << endl;

		cout << "History" << endl;

		cout << "n turn: " << n_turn << endl;

		cout << player_1->get_name() << ":\t";
		for (auto i : player_1->get_history())
			cout << " " << uint16_t(i);
		cout << endl;

		cout << player_2->get_name() << ":\t";
		for (auto i : player_2->get_history())
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

///	------------------------------------------------------------------------------------------------

uint16_t ask_ai_level()
{
	cout << "Set AI level: ";
	auto str_input = string { };
	getline(cin, str_input);
	auto level = uint16_t { 0 };
	stringstream(str_input) >> level;

	return level;
}

///	=== END OF FILE	================================================================================
