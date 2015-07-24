///
/// \file	neuron.hpp
///	\brief	
///	\date	24 juil. 2015
/// \author	nboutin
///
#ifndef EXTERNAL_AI_HOME_NEURAL_NETWORK_NEURON_HPP_
#define EXTERNAL_AI_HOME_NEURAL_NETWORK_NEURON_HPP_

/// === Includes	================================================================================

#include <vector>

/// === Namespaces	================================================================================
namespace neural_network
{

/// === Class Declarations	========================================================================
class Neuron
{
public:
	/// === Public Declarations	====================================================================

	Neuron(const std::vector<float>& _weights, float _bias);

	///	--- Operations	----------------------------------------------------------------------------

	/// _inputs value [0, 1]
	float fire(const std::vector<float>& _inputs) const;

private:
	/// === Private Declarations	================================================================

	float sigmoid_function(float _z) const;

	/// === Private Attributs	====================================================================

	std::vector<float> weights_;
	float bias_;
};

///	------------------------------------------------------------------------------------------------

}

#endif
/// === END OF FILE	================================================================================
