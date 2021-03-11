#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iterator>
#include <string>
#include <list>

class PhoneBook
{
public:
  struct Record
  {
    std::string phoneNumber;
    std::string name;
  };
  
  using phoneBookIter = std::list<Record>::iterator;
  using phoneBookSizeType = std::list<Record>::size_type;
  
  phoneBookIter begin();
  phoneBookIter end();
  bool isEmpty() const;
  phoneBookSizeType size() const;
  
  void deleteRecord(phoneBookIter iterator);
  
  void show(std::ostream & outStream, phoneBookIter iterator) const;
  phoneBookIter next(phoneBookIter iterator) const;
  phoneBookIter prev(phoneBookIter iterator) const;
  phoneBookIter move(phoneBookIter iterator, int step);
  
  void pushBefore(phoneBookIter iterator, const Record & record);
  void pushAfter(phoneBookIter iterator, const Record & record);
  void pushBack(const Record & record);
  
  void change(phoneBookIter iterator, const Record & newRecord);
  
private:
  std::list<Record> records_;
};

#endif /* PHONE_BOOK_HPP */
