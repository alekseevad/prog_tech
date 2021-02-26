#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>

enum class Order
{
  ASCENDING,
  DESCENDING
};

Order checkOrder(const char* order);

template <typename Collection>
void printCollection(const Collection& collection)
{
  for (auto i = collection.begin(); i != collection.end(); ++i)
  {
    std::cout << *i << ' ';
  }

  std::cout << std::endl;
}

template <typename Collection>
void readData(Collection& collection)
{
  typename Collection::value_type pars;

  while(std::cin >> pars)
  {
    collection.push_back(pars);
  }

  if (std::cin.eof() == false)
  {
    throw std::invalid_argument("Incorrect input data!");
  }
}

template <typename Collection>
struct access_by_brackets_t
{
  using value_type = typename Collection::value_type;
  using index_type = typename Collection::size_type;

  static index_type begin(const Collection&)
  {
    return 0;
  }

  static index_type end(const Collection& collection)
  {
    return collection.size();
  }

  static value_type& getElement (Collection& collection, const index_type i)
  {
    return collection[i];
  }
};

template <typename Collection>
struct access_by_at_t
{
  using value_type = typename Collection::value_type;
  using index_type = typename Collection::size_type;

  static index_type begin(const Collection&)
  {
    return 0;
  }

  static index_type end(const Collection& collection)
  {
    return collection.size();
  }

  static value_type& getElement (Collection& collection, const index_type i)
  {
    return collection.at(i);
  }
};

template <typename Collection>
struct access_by_iterator_t
{
  using value_type = typename Collection::value_type;
  using index_type = typename Collection::iterator;

  static index_type begin(Collection& collection)
  {
    return collection.begin();
  }

  static index_type end(Collection& collection)
  {
    return collection.end();
  }

  static value_type& getElement (Collection&, index_type const iter)
  {
    return *iter;
  }
};

#endif
