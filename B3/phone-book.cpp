#include "phone-book.hpp"

#include <iostream>
#include <iterator>
#include <list>

PhoneBook::phoneBookIter PhoneBook::begin()
{
  return records_.begin();
}

PhoneBook::phoneBookIter PhoneBook::end()
{
  return records_.end();
}

bool PhoneBook::isEmpty() const
{
  return records_.empty();
}

PhoneBook::phoneBookSizeType PhoneBook::size() const
{
  return records_.size();
}

void PhoneBook::deleteRecord(phoneBookIter iterator)
{
  records_.erase(iterator);
}

void PhoneBook::show(std::ostream & outStream, phoneBookIter iterator) const
{
  outStream << iterator->phoneNumber << " " << iterator->name << "\n";
}

PhoneBook::phoneBookIter PhoneBook::next(phoneBookIter iterator) const
{
  if (std::next(iterator) != records_.end()) {
    return ++iterator;
  } else {
    return iterator;
  }
}

PhoneBook::phoneBookIter PhoneBook::prev(phoneBookIter iterator) const
{
  if (iterator != records_.begin()) {
    return --iterator;
  } else {
    return iterator;
  }
}

void PhoneBook::pushBefore(phoneBookIter iterator, const Record & record)
{
  records_.insert(iterator, record);
}

void PhoneBook::pushAfter(phoneBookIter iterator, const Record & record)
{
  records_.insert(std::next(iterator), record);
}

void PhoneBook::pushBack(const Record & record)
{
  records_.push_back(record);
}

void PhoneBook::change(phoneBookIter iterator, const Record & newRecord)
{
  iterator->phoneNumber = newRecord.phoneNumber;
  iterator->name = newRecord.name;
}

PhoneBook::phoneBookIter PhoneBook::move(phoneBookIter iterator, int step)
{
  if (step == 0) {
    return iterator;
  }
  
  if (step > 0) {
    while (step > 0) {
      iterator = next(iterator);
      step--;
    }
  } else {
    while (step < 0) {
      iterator = prev(iterator);
      step++;
    }
  }
  return iterator;
}
