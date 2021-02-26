#include "numbers.hpp"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include "utilities.hpp"

void number2(const char* file_name)
{
  if (file_name == nullptr)
  {
    throw std::invalid_argument("Missing file name!");
  }
  
  std::ifstream file(file_name);

  if (file.is_open() == false)
  {
    throw std::ios_base::failure("File opening error!");
  }
  
  std::size_t array_size = 128;
  auto array = std::make_unique<char[]>(array_size);
  std::size_t symb_count = 0;

  while (file.eof() == false)
  {
    if (array_size > symb_count)
    {
      file.read(array.get() + symb_count, array_size - symb_count);
      symb_count += file.gcount();
    }
    else
    {
      std::size_t temp_array_size = array_size * 1.8;
      auto temp_array = std::make_unique<char[]>(temp_array_size);
      
      for(std::size_t i = 0; i < array_size; ++i)
      {
        temp_array[i] = array[i];
      }
      
      array = std::move(temp_array);
      array_size = temp_array_size;
    }
  }
  
  std::vector<char> vector(array.get(), array.get() + symb_count);
  
  for(std::size_t i = 0; i < vector.size(); ++i)
  {
    std::cout << vector.at(i);
  }
}
