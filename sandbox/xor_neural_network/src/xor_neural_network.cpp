//============================================================================
// Name        : xor_neural_network.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "neural_network/feedforward_neural_network.hpp"

using namespace std;
using namespace neural_network;

int main()
{
	cout << "=====\t XOR Neural Network\t=====" << endl;

	auto nn = FeedForward_Neural_Network { };
	nn.add_layer(2);
	nn.add_layer(4);
	nn.add_layer(1);

	return 0;
}
