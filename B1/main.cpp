#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include "numbers.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Invalid arguments!\n";
    return 1;
  }
  
  const int number = std::stoi(argv[1]);
  
  try
  {
    if ((argc == 3) && (number == 1))
    {
      number1(argv[2]);
    }
    else if ((argc == 3) && (number == 2))
    {
      number2(argv[2]);
    }
    else if ((argc == 2) && (number == 3))
    {
      number3();
    }
    else if ((argc == 4) && (number == 4))
    {
      number4(argv[2], std::stoi(argv[3]));
    }
    else
    {
      std::cerr << "Invalid arguments!\n";
      return 2;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 3;
  }

  return 0;
}
