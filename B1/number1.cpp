#include "numbers.hpp"
#include <vector>
#include <forward_list>
#include <fstream>
#include <stdexcept>
#include "utilities.hpp"

void number1(const char* order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Missing order!");
  }
  
  const Order working_order = checkOrder(order);
  std::vector<int> vector_1;
  readData(vector_1);
  
  if (vector_1.empty())
  {
    return;
  }
  
  std::vector<int> vector_2(vector_1);
  std::forward_list<int> list(vector_1.begin(), vector_1.end());

  sort<access_by_brackets_t>(vector_1, working_order);
  sort<access_by_at_t>(vector_2, working_order);
  sort<access_by_iterator_t>(list, working_order);

  printCollection(vector_1);
  printCollection(vector_2);
  printCollection(list);
}
