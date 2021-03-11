#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "parser.hpp"
#include "mark-book.hpp"
#include "phone-book.hpp"
#include "factorial-container.hpp"

int firstTask();
int secondTask();

int completeTasks(int argc, const char *argv[])
{
  if (argc != 2) {
    std::cerr << "Programm must have 1 initial parametr!" << std::endl;
    return 3;
  }

  switch (std::stoi(argv[1])) {
    case 1: {
      firstTask();
      break;
    }
    case 2: {
      secondTask();
      break;
    }
    default: {
      std::cerr << "Incorrect number of task!" << std::endl;
      return 3;
      break;
    }
  }
  
  return 0;
}

int firstTask()
{
  PhoneBook phoneBook;
  MarkBook markBook(&phoneBook);
  Parser parser(&markBook, &phoneBook);
  parser.parseInStream(std::cin);
  
  return 0;
}

const size_t MAX = 10;

int secondTask()
{
  FactorialContainer factContainer(MAX);
  std::copy(factContainer.begin(), factContainer.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << std::endl;

  std::reverse_copy(factContainer.begin(), factContainer.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}
