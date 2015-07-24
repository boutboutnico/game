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
#include <algorithm>
#include <functional>

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

void FeedForward_Neural_Network::add_layer(uint16_t _n_neurons)
{
	/// Add input layer, one input by neurons
	if (layers_.empty() == true)
	{
		/// Input as no weights and no bias
		layers_.push_back(vector<Neuron>(_n_neurons, Neuron { vector<float> { 0 }, 0 }));
	}
	else
	{
		/// Mean 0, deviation 1
		auto distribution = normal_distribution<float>(0.0f, 1.0f);
		auto engine = mt19937 { };
		auto generator = bind(distribution, engine);

		auto w = vector<float>(layers_.back().size(), 0);
		generate_n(w.begin(), layers_.back().size(), generator);

		layers_.push_back(vector<Neuron>(_n_neurons, Neuron { w, generator() }));
	}
}

/// === Private Definitions	========================================================================

/// === END OF FILES	============================================================================
