#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    Iterator(size_t index);
    
    Iterator(const Iterator & other) = default;
    Iterator & operator=(const Iterator & other) = default;
    
    Iterator & operator++();
    Iterator operator++(int);
    Iterator & operator--();
    Iterator operator--(int);

    bool operator==(const Iterator & other) const;
    bool operator!=(const Iterator & other) const;

    const unsigned int & operator*() const;
    
  private:
    unsigned int calculateFactorial(size_t index) const;
    size_t index_;
    unsigned int value_;
  };
  
  FactorialContainer(size_t max);
  
  Iterator begin();
  Iterator end();
  
private:
  Iterator min_;
  Iterator max_;
};



#endif /* FACTORIAL_CONTAINER_HPP */
