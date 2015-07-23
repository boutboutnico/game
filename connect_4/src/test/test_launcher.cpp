///
/// \file	test_launcher.cpp
///	\brief	
///	\date	20 juil. 2015
/// \author	nboutin
///

#include <test/test_launcher.hpp>

/// === Includes	================================================================================

#include "test_is_finished.hpp"
#include "test_remove.hpp"
#include "test_minmax_eval.hpp"

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
	is_finished_diag_LB_RT_1();
	is_finished_diag_LB_RT_2();

	remomve_pawn_1();

	draw_eval_1();
	draw_eval_2();
	draw_eval_3();
	draw_eval_4();
}

/// === Private Definitions	========================================================================
///	------------------------------------------------------------------------------------------------
}
}
/// === END OF FILES	============================================================================
