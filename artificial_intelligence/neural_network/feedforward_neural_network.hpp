///
/// \file	neural_network.hpp
///	\brief	
///	\date	24 juil. 2015
/// \author	nboutin
///
#ifndef EXTERNAL_AI_HOME_NEURAL_NETWORK_NEURAL_NETWORK_HPP_
#define EXTERNAL_AI_HOME_NEURAL_NETWORK_NEURAL_NETWORK_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <vector>
#include "neuron.hpp"

/// === Namespaces	================================================================================
namespace neural_network
{

/// === Class Declarations	========================================================================
class FeedForward_Neural_Network
{
public:
	/// === Public Declarations	====================================================================

	void add_layer(uint16_t _n_neurons);

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	std::vector<std::vector<Neuron>> layers_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
