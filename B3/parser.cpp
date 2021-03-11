#include "parser.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "mark-book.hpp"
#include "phone-book.hpp"


Parser::Parser(MarkBook *markBook, PhoneBook *phoneBook):
  markBook_(markBook),
  phoneBook_(phoneBook)
{}

void Parser::parseInStream(std::istream & inStream)
{
  std::string str;
  while (std::getline(inStream, str)) {
    std::stringstream sstream(str);
    parseCommand(sstream);
  }
}

void Parser::parseCommand(std::stringstream & sstream)
{
  std::string command;
  sstream >> command >> std::ws;
  
  if (command == "add") {
    add(sstream);
  } else if (command == "store") {
    storeMark(sstream);
  } else if (command == "insert") {
    insertMark(sstream);
  } else if (command == "delete") {
    deleteMark(sstream);
  } else if (command == "show") {
    show(sstream);
  } else if (command == "move") {
    move(sstream);
  } else {
    std::cout << "<INVALID COMMAND>" << std::endl;
  }
}

void Parser::add(std::stringstream & sstream)
{
  std::string phoneNumber;
  std::string name;
  
  try {
    phoneNumber = parsePhoneNumber(sstream);
    name = parseName(sstream);
  } catch (const std::runtime_error & err) {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  
  markBook_->add(phoneNumber, name);
}

void Parser::storeMark(std::stringstream & sstream)
{
  std::string markOld;
  std::string markNew;
  try {
    markOld = parseMark(sstream);
    markNew = parseMark(sstream);
  } catch (const std::runtime_error & err) {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  
  markBook_->store(markOld, markNew);
}

void Parser::insertMark(std::stringstream & sstream)
{
  std::string insertDirection;
  std::string mark;
  std::string phoneNumber;
  std::string name;
  try {
    insertDirection = parseInsertDirection(sstream);
    mark = parseMark(sstream);
    phoneNumber = parsePhoneNumber(sstream);
    name = parseName(sstream);
  } catch (const std::runtime_error & err) {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  
  if (insertDirection == "before") {
    markBook_->insertBeforeMark(mark, phoneNumber, name);
  } else {
    markBook_->insertAfterMark(mark, phoneNumber, name);
  }
}

void Parser::deleteMark(std::stringstream & sstream)
{
  std::string mark;
  try {
    mark = parseMark(sstream);
  } catch (const std::runtime_error & err) {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }
  
  markBook_->deleteMark(mark);
}

void Parser::show(std::stringstream & sstream)
{
  std::string mark;
  try {
    mark = parseMark(sstream);
  } catch (const std::runtime_error & err) {
    std::cout << "<INVALID COMMAND>" << std::endl;
    return;
  }

  markBook_->show(std::cout, mark);
}

void Parser::move(std::stringstream & sstream)
{
  std::string markName = parseMark(sstream);
  
  std::string position = "";
  sstream >> position;
  
  try {
    if (position == "first") {
      markBook_->move(markName, phoneBook_->begin());
    } else if (position == "last") {
      markBook_->move(markName, std::prev(phoneBook_->end()));
    } else {
      int step = std::stoi(position);
      markBook_->move(markName, step);
    }
  } catch (const std::exception & except) {
    std::cout << "<INVALID STEP>" << std::endl;
    return;
  }
  
}

std::string Parser::parsePhoneNumber(std::stringstream & sstream)
{
  std::string phoneNumber;
  sstream >> phoneNumber >> std::ws;
  
  if (phoneNumber.empty()) {
    throw std::runtime_error("Empty phone number!");
  }
  
  for (auto ch : phoneNumber) {
    if (!isdigit(ch)) {
      throw std::runtime_error("Phone number consists only of digits!");
    }
  }
  
  return phoneNumber;
}

std::string Parser::parseName(std::stringstream & sstream)
{
  std::string name;
  std::getline(sstream, name, '\0');
  
  if (name.empty()) {
    throw std::runtime_error("Empty name!");
  }
  
  if (name.front() != '\"' || name.back() != '\"') {
    throw std::runtime_error("Name must be in quotation marks!");
  }
  
  name.pop_back();
  name.erase(name.begin());
  
  if (name.find('\n') != std::string::npos) {
    throw std::runtime_error("Name can not have \\n !");
  }
  
  auto it = name.begin();
  while (it != name.end()) {
    if (*it == '\\') {
      if (((it + 1) != name.end()) && ((*(it + 1) == '\\') || (*(it + 1) == '\"'))){
        it = name.erase(it) + 1;
      }
    } else if (*it != '\"') {
      it++;
    }
  }
  
  return name;
}

std::string Parser::parseMark(std::stringstream & sstream)
{
  std::string mark;
  sstream >> mark >> std::ws;
  
  if (mark.empty()) {
    throw std::runtime_error("Empty mark name!");
  }
  
  for (auto ch : mark) {
    if (!isalnum(ch) && ch != '-') {
      throw std::runtime_error("Mark consists olnly of: alphas, digits, \"-\" !");
    }
  }

  return mark;
}

std::string Parser::parseInsertDirection(std::stringstream & sstream)
{
  std::string direction;
  sstream >> direction >> std::ws;
  if (direction == "before" || direction == "after") {
    return direction;
  } else {
    throw std::runtime_error("Invalid place to insert!");
  }
}
