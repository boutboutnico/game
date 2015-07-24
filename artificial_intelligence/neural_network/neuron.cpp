///
/// \file	neuron.cpp
///	\brief	
///	\date	24 juil. 2015
/// \author	nboutin
///

#include <neural_network/neuron.hpp>
using namespace neural_network;

/// === Includes	================================================================================

#include <algorithm>
#include <cstdlib>

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

Neuron::Neuron(const std::vector<float>& _weights, float _bias)
		: weights_(_weights), bias_(_bias)
{

}

/// === Private Definitions	========================================================================

float Neuron::sigmoid_function(const vector<float>& _inputs) const
{
	auto result = float { };

	result = inner_product(weights_.begin(), weights_.end(), _inputs.begin(), 0);

	return (1 / (1 + exp(-(result + bias_))));
}

/// === END OF FILES	============================================================================
