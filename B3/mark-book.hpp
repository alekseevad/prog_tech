#ifndef MARK_BOOK_HPP
#define MARK_BOOK_HPP

#include <string>
#include <map>
#include <iterator>
#include <list>
#include <memory>

#include "phone-book.hpp"

class MarkBook
{
public:
  
  using bookIterator = std::list<PhoneBook::Record>::iterator;
  
  MarkBook(PhoneBook *phoneBook);
  
  void add(const std::string & phoneNumber, const std::string & name);
  void store(const std::string & oldName, const std::string & newName);
  
  void insertBeforeMark(const std::string & markName, const std::string & phoneNumber, const std::string & name);
  void insertAfterMark(const std::string & markName, const std::string & phoneNumber, const std::string & name);
  
  void deleteMark(const std::string & markName);
  
  void show(std::ostream & outStream, const std::string & markName);
  
  void move(const std::string & markName, int step);
  void move(const std::string & markName, bookIterator position);
  
private:
  PhoneBook *phoneBook_;
  
  std::map<std::string, bookIterator> marks_;
};

#endif /* MARK_BOOK_HPP */
