//============================================================================
// Name        : petits_chevaux.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>

#include "engine.h"

using namespace std;
using namespace game;

auto roll_dice() -> uint16_t;
shared_ptr<Horse> select_horse(shared_ptr<Player> _player);
void print_board(const Board& _board);
void print_action_message(uint16_t _user_action, e_engine_result _engine_result);
void print_engine_message(e_engine_result _engine_result);

int main()
{
	cout << "=====	Les Petits Chevaux	=====" << endl;

	auto engine = Engine();

	/// Add players		name	home_pos	n_horse
	engine.add_player("1", 0);
	engine.add_player("2", 1);
	engine.add_player("3", 2);
	engine.add_player("4", 3);

	/// Start game
	auto n_horses_by_player = 2U;
	engine.start(n_horses_by_player);

	auto current_player = engine.get_current_player();
	bool is_ended = false;
	string str_input;
	uint16_t user_action = 0;

	while (engine.is_game_finished() == false && is_ended == false)
	{
		/// Print information
		current_player = engine.get_current_player();
		cout << "=====\t" << current_player->get_name() << "\t=====" << endl;

		/// Roll Dice
		cout << "Roll dice: ";
		auto dice = roll_dice();
		cout << dice << endl;

		auto engine_result = e_engine_result::ERROR_UNDEFINED;
		do
		{
			/// Choose action
			cout << "Select action:\t   ";
			getline(cin, str_input);
			stringstream(str_input) >> user_action;

			/// Execute Action
			switch (user_action)
			{
			case 0:
				engine_result = engine.pass_turn();
				break;

			case 1:
			{
				/// Select Horse
				auto current_horse = select_horse(current_player);
				engine_result = engine.release_horse(current_horse, dice);
				break;
			}

			case 2:
			{
				/// Select Horse
				auto current_horse = select_horse(current_player);
				engine_result = engine.move_horse_on_board(current_horse, dice);
				break;
			}

			case 99:
			{
				is_ended = true;
				break;
			}

			default:
			{
				break;
			}

			}

			print_action_message(user_action, engine_result);
		}
		while (engine_result != e_engine_result::SUCCESS && is_ended == false);

		print_board(engine.get_board());

	}
	cout << "===== End of Game	=====" << endl;
	return 0;
}

///	------------------------------------------------------------------------------------------------

void print_action_message(uint16_t _user_action, e_engine_result _engine_result)
{
	switch (_user_action)
	{
	case 0:
		cout << "Pass turn" << endl;
		break;

	case 1:
	{
		cout << "Release horse -> ";
		print_engine_message(_engine_result);
		break;
	}

	case 2:
	{
		cout << "Move horse on board -> ";
		print_engine_message(_engine_result);
		break;
	}

	case 99:
		cout << "Quit game" << endl;
		break;

	default:
		cout << __func__ << endl;
		break;

	}
}

///	------------------------------------------------------------------------------------------------

void print_engine_message(e_engine_result _engine_result)
{
	switch (_engine_result)
	{
	case e_engine_result::HORSE_NOT_AT_STABLE:
		cout << "Horse not at stable" << endl;
		break;

	case e_engine_result::CELL_NOT_FREE:
		cout << "Cell is not free" << endl;
		break;

	case e_engine_result::ERROR_UNDEFINED:
		cout << "Error undefined" << endl;
		break;

	case e_engine_result::HORSE_NOT_ON_BOARD:
		cout << "Horse not on board" << endl;
		break;

	case e_engine_result::NEED_DICE_6_TO_RELEASE:
		cout << "Need a dice equal to 6" << endl;
		break;

	case e_engine_result::SUCCESS:
		cout << "Ok" << endl;
		break;

	default:
		cout << __func__ << endl;
		break;
	}
}

///	------------------------------------------------------------------------------------------------

void print_board(const Board& _board)
{
	auto cells = _board.get_cells();

	for (auto i = 0U; i < cells.size(); ++i)
	{
		auto horse = cells[i];

		if (i % 14 == 0) cout << endl;

		if (horse == false) cout << "-- ";
		else
		{
			if (auto player = horse->get_player().lock())
			{
				cout << player->get_name() << horse->get_name() << " ";
			}
			else
			{
				cout << "ee ";
			}
		}

	}

	cout << endl;
}

///	------------------------------------------------------------------------------------------------

shared_ptr<Horse> select_horse(shared_ptr<Player> _player)
{
	string str_input;
	uint16_t user_input = 0;

	/// TODO Add control on user input (value range)

	cout << "Select horse(1-" << (uint16_t) _player->get_horse_count() << "): ";
	getline(cin, str_input);
	stringstream(str_input) >> user_input;
	return _player->get_horse(user_input - 1);
}

///	------------------------------------------------------------------------------------------------

auto roll_dice() -> uint16_t
{
/// std::time_t
	auto result = std::time(nullptr);
	std::localtime(&result);

	static mt19937 rng(result);    // random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(1, 6);    // guaranteed unbiased

	return uni(rng);
//	return 6;
}
