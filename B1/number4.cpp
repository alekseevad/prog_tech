#include "numbers.hpp"
#include <cstddef>
#include <cstdlib>
#include <random>
#include <vector>
#include <stdexcept>
#include "utilities.hpp"

void fillRandom(double* array, const std::size_t size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Invalid array!");
  }
  
  const double min = -1.0, max = 1.0;
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<double> distribution(min, max);
  
  for(std::size_t i = 0; i < size; ++i)
  {
    array[i] = distribution(gen);
  }
}

void number4(const char* order, const int array_size)
{
  if (order == nullptr)
  {
    throw std::runtime_error("Missing order!");
  }
  
  if (array_size <= 0)
  {
    throw std::invalid_argument("Incorrect array size!");
  }
  
  const Order working_order = checkOrder(order);
  std::vector<double> vector(array_size);
  fillRandom(&vector[0], array_size);
  printCollection(vector);
  sort<access_by_at_t>(vector, working_order);
  printCollection(vector);
}
