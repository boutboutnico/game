///
/// \file	test.cpp
///	\brief	
///	\date	10 juil. 2015
/// \author	nboutin
///

#include "test.hpp"

/// === Includes	================================================================================

#include <iostream>
#include "test/test_finish.hpp"
#include "test/test_ai.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace test
{

/// === Public Definitions	========================================================================

void run_test()
{
	cout << "=====\tTEST\t=====" << endl;

	run_is_finished();
	run_ai();

	cout << "=====\tEND OF TEST\t=====" << endl;
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
/// === END OF FILES	============================================================================
