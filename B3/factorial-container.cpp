#include "factorial-container.hpp"

#include <iostream>
#include <stdexcept>

FactorialContainer::FactorialContainer(size_t max):
  min_(Iterator(1)),
  max_(Iterator(max + 1))
{}

FactorialContainer::Iterator FactorialContainer::begin()
{
  return min_;
}

FactorialContainer::Iterator FactorialContainer::end()
{
  return max_;
}

FactorialContainer::Iterator::Iterator(size_t index):
  index_(index),
  value_(calculateFactorial(index))
{}

FactorialContainer::Iterator & FactorialContainer::Iterator::operator++()
{
  index_++;
  value_ *= index_;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  Iterator oldIterator = *this;
  index_++;
  value_ *= index_;
  return oldIterator;
}

FactorialContainer::Iterator & FactorialContainer::Iterator::operator--()
{
  value_ /= index_;
  index_--;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  Iterator oldIterator = *this;
  value_ /= index_;
  index_--;
  return oldIterator;
}

bool FactorialContainer::Iterator::operator==(const Iterator & other) const
{
  return index_ == other.index_;
}

bool FactorialContainer::Iterator::operator!=(const Iterator & other) const
{
  return !(index_ == other.index_);
}

const unsigned int & FactorialContainer::Iterator::operator*() const
{
  return value_;
}

unsigned int FactorialContainer::Iterator::calculateFactorial(size_t index) const
{
  unsigned int factorial = 1;
  for (size_t i = 2; i <= index; i++) {
    unsigned int testFactorial = factorial;
    factorial *= i;
    if (factorial / i != testFactorial) {
      throw std::overflow_error("Factorial value overflow!");
    }
  }
  return factorial;
}
