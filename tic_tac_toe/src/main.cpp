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
#include "print.hpp"

///	=== Namespaces	================================================================================

using namespace std;
using namespace engine;
using namespace print;

///	===	Public Definitions	========================================================================

int main()
{
	cout << "TIC TAC TOE" << endl;

	auto engine = Engine("P1", "P2");
	auto is_quit = false;
	auto str_input = string { };
	auto x = 0U, y = 0U;
	auto engine_result = false;

	while (engine.is_game_finished() == false && is_quit == false)
	{
		cout << "=====\t" << engine.get_current_player() << "\t=====" << endl;

		do
		{
			cout << "Select cell(x y): ";
			getline(cin, str_input);
			stringstream(str_input) >> x >> y;

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

///	===	END OF FILE	================================================================================
