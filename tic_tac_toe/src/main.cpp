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
#include "engine/engine.h"

///	=== Namespaces	================================================================================

using namespace std;
using namespace engine;

///	===	Public Definitions	========================================================================

int main()
{
	cout << "TIC TAC TOE" << endl;

	auto engine = Engine();
	auto is_quit = false;
	auto str_input = string {};
	auto x = 0U, y = 0U;
	auto engine_result = false;

	while (engine.is_game_finished() == false && is_quit == false)
	{

		do
		{
			/// Choose action
			cout << "Select cell(x y):\t   ";
			getline(cin, str_input);
			stringstream(str_input) >> x >> y;

			engine_result = engine.add_pawn(x, y);
		}
		while (engine_result == false);
	}

	return 0;
}

///	===	END OF FILE	================================================================================
