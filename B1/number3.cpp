#include "numbers.hpp"
#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include "utilities.hpp"

void number3()
{
  std::vector<int> vector;
  readData(vector);

  if (vector.empty())
  {
    return;
  }

  if (vector.back() != 0)
  {
    throw std::runtime_error("Last symbol must be 0!");
  }
  
  vector.pop_back();
  auto i = vector.begin();
  
  if (vector.back() == 1)
  {
    while (i != vector.end())
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        ++i;
      }
    }
  }

  if (vector.back() == 2)
  {
    while (i != vector.end())
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(i + 1, 3, 1);
      }
      
      ++i;
    }
  }

  printCollection(vector);
}
