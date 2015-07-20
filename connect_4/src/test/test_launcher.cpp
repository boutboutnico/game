///
/// \file	test_launcher.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include <test/test_launcher.hpp>

/// === Includes	================================================================================

#include "test_is_finished.hpp"

/// === Namespaces	================================================================================

namespace connect_4
{
namespace test
{
/// === Public Definitions	========================================================================

void test_launch()
{
	is_finished_horizontal_1();
	is_finished_diag_LT_RB_1();
	is_finished_diag_LT_RB_2();
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
