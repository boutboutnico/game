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


#include <map>
#include <functional>
#include <random>
#include <cmath>
#include <iomanip>

int main()
{
	cout << "=====\t XOR Neural Network\t=====" << endl;

//	normal_distribution<> distribution(0, 5);
//	auto engine = mt19937 {};
//	auto generator = bind(distribution, engine);
//
//	std::map<int, int> hist;
//	for (int n = 0; n < 50000; ++n)
//	{
//		++hist[std::round(generator())];
//	}
//	for (const auto& p : hist)
//	{
//		std::cout << std::fixed << std::setprecision(1) << std::setw(2) << p.first << ' '
//		<< std::string(p.second / 100, '*') << '\n';
//	}

	auto nn = FeedForward_Neural_Network { };
	nn.add_layer(2);
	nn.add_layer(4);
	nn.add_layer(1);

	return 0;
}
