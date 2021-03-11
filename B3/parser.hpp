#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <memory>

#include "mark-book.hpp"

class Parser
{
public:
  Parser(MarkBook *markBook, PhoneBook *phoneBook);
  
  void parseInStream(std::istream & inStream);
  
  void add(std::stringstream & sstream);
  void storeMark(std::stringstream & sstream);
  void insertMark(std::stringstream & sstream);
  void deleteMark(std::stringstream & sstream);
  void show(std::stringstream & sstream);
  void move(std::stringstream & sstream);

private:
  
  void parseCommand(std::stringstream & sstream);
  std::string parsePhoneNumber(std::stringstream & sstream);
  std::string parseName(std::stringstream & sstream);
  std::string parseMark(std::stringstream & sstream);
  std::string parseInsertDirection(std::stringstream & sstream);
  
  MarkBook *markBook_;
  PhoneBook *phoneBook_;
};

#endif /* PARSER_HPP */
