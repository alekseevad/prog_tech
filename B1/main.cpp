#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include "numbers.hpp"

int main(int argc, char* argv[])
{
	try
	{
        Numbers *number1 = new Numbers();
		if (argc < 2)
		{
			throw std::invalid_argument("Wrong number of arguments");
		}

		const int number = std::stoi(argv[1]);	

        if ((argc == 7) && (number == 1))
        {

            number1->sort1(argv[2]);
        }
        /*else if ((argc == 3) && (number == 2))
        {
            number1->sort2(argv[2]);
        }
        else if ((argc == 2) && (number == 3))
        {
            number1->sort3();
        }
        else if ((argc == 4) && (number == 4))
        {
            number1->sort4(argv[2], std::stoi(argv[3]));
        }*/
        else
        {
            throw std::invalid_argument("Wrong type of sort or order");
        }
	}
	catch (std::exception& a)
	{
		std::cerr << a.what() << std::endl;
		return 1;
	}
	return 0;
}