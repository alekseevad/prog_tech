#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <algorithm>
#include <cstddef>
#include "utilities.hpp"

template <template<typename> typename Access, typename Collection>
void sort(Collection& collection, const Order order)
{
  using access_type = Access<Collection>;
  using index_type = typename access_type::index_type;
  index_type begin = access_type::begin(collection);
  index_type end = access_type::end(collection);

  for (index_type i = begin; i != end; ++i)
  {
    for (index_type j = i; j != end; ++j)
    {
      if ((access_type::getElement(collection, i) > access_type::getElement(collection, j))
          && (order == Order::ASCENDING))
      {
        std::swap(access_type::getElement(collection, i), access_type::getElement(collection, j));
      }
      else if ((access_type::getElement(collection, i) < access_type::getElement(collection, j))
          && (order == Order::DESCENDING))
      {
        std::swap(access_type::getElement(collection, i), access_type::getElement(collection, j));
      }
    }
  }
}

void number1(const char* order);

void number2(const char* file_name);

void number3();

void fillRandom(double* array, const std::size_t size);

void number4(const char* order, const int array_size);

#endif
