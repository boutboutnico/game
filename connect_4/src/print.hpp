///
/// \file	print.hpp
///	\brief	
///	\date	9 juil. 2015
/// \author	nboutin
///
#ifndef PRINT_HPP_
#define PRINT_HPP_

/// === Includes	================================================================================

///	===	Forward Declarations	====================================================================

namespace connect_4
{
class Engine;
}

/// === Namespaces	================================================================================

namespace print
{
/// === Public Declarations	========================================================================

void print_grid(const connect_4::Engine& engine);

///	------------------------------------------------------------------------------------------------
}
#endif
/// === END OF FILE	================================================================================
