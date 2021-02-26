#include "utilities.hpp"
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <vector>

Order checkOrder(const char* order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Invalid order!");
  }
  
  if (std::strcmp(order, "ascending") == 0)
  {
    return Order::ASCENDING;
  }
  else if (std::strcmp(order, "descending") == 0)
  {
    return Order::DESCENDING;
  }
  else
  {
    throw std::invalid_argument("Invalid order!");
  }
}
