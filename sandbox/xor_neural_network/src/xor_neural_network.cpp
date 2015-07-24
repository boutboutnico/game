//============================================================================
// Name        : xor_neural_network.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "neural_network/neuron.hpp"

using namespace std;
using namespace neural_network;

int main()
{
	cout << "=====\t XOR Neural Network\t=====" << endl;    // prints !!!Hello World!!!

	auto w = vector<float> { 0.0001 };
	auto n = Neuron { w, -1000 };

	auto x = vector<float> { 0.0001 };
	auto result = n.fire(x);

	cout << result << endl;

	return 0;
}
