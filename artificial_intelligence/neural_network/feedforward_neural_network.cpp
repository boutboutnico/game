///
/// \file	neural_network.cpp
///	\brief	
///	\date	24 juil. 2015
/// \author	nboutin
///

#include <neural_network/feedforward_neural_network.hpp>
using namespace neural_network;

/// === Includes	================================================================================

#include <random>
#include <ctime>

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

void FeedForward_Neural_Network::add_layer(uint16_t _n_neurons)
{
	auto result = std::time(nullptr);
	std::localtime(&result);

	static mt19937 generator(result);
	/// Mean 0, deviation 1
	normal_distribution<> distribution(0,1);

	distribution(generator);

	/// Add input layer, one input by neurons
	if (layers_.empty() == true)
	{
		layers_.push_back(vector<Neuron>(_n_neurons, w, b));
	}
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
