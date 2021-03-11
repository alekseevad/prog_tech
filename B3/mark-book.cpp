#include "mark-book.hpp"

#include <iostream>

#include "phone-book.hpp"

MarkBook::MarkBook(PhoneBook *phoneBook):
  phoneBook_(phoneBook),
  marks_()
{
  marks_["current"] = phoneBook_->begin();
}

void MarkBook::add(const std::string & phoneNumber, const std::string & name)
{
  phoneBook_->pushBack({phoneNumber, name});
  if (phoneBook_->size() == 1) {
    marks_["current"] = phoneBook_->next(marks_["current"]);
  }
}

void MarkBook::store(const std::string & oldName, const std::string & newName)
{
  if (marks_.find(oldName) != marks_.end()) {
    marks_[newName] = marks_[oldName];
  }
}

void MarkBook::insertBeforeMark(const std::string & markName, const std::string & phoneNumber, const std::string & name)
{
  if (phoneBook_->isEmpty()) {
    add(phoneNumber, name);
  }
  
  if (marks_.find(markName) != marks_.end()) {
    phoneBook_->pushBefore(marks_[markName], {phoneNumber, name});
  }
}

void MarkBook::insertAfterMark(const std::string & markName, const std::string & phoneNumber, const std::string & name)
{
  if (phoneBook_->isEmpty()) {
    add(phoneNumber, name);
  }
  
  if (marks_.find(markName) != marks_.end()) {
    phoneBook_->pushAfter(marks_[markName], {phoneNumber, name});
  }
}

void MarkBook::deleteMark(const std::string & markName)
{
  if (marks_.find(markName) == marks_.end()) {
    return;
  }
  
  auto delIterator = marks_[markName];
  auto destIterator = std::next(delIterator);
  
  if (destIterator == phoneBook_->end()) {
    destIterator = phoneBook_->begin();
  }
  
  for (auto iterator : marks_) {
    if (iterator.second == delIterator) {
      marks_[iterator.first] = destIterator;
    }
  }
  phoneBook_->deleteRecord(delIterator);
}

void MarkBook::show(std::ostream & outStream, const std::string & markName)
{
  
  if (marks_.find(markName) == marks_.end()) {
    outStream << "<INVALID BOOKMARK>" << std::endl;
    return;
  }
  
  if (phoneBook_->isEmpty()) {
    outStream << "<EMPTY>" << std::endl;
    return;
  }
    
  phoneBook_->show(outStream, marks_[markName]);
}

void MarkBook::move(const std::string & markName, int step)
{
  if (marks_.find(markName) != marks_.end()) {
    marks_[markName] = phoneBook_->move(marks_[markName], step);
  }
}

void MarkBook::move(const std::string & markName, bookIterator position)
{
  if (marks_.find(markName) != marks_.end()) {
    marks_[markName] = position;
  }
}
