#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "numbers.hpp"

int main(/*int argc, char* argv[]*/)
{
	Numbers<std::vector<int>> try_(1, Order::ASCENDING);
	std::cin >> try_;
	std::cout << try_;
	return 0;
}