#include <iostream>
#include <stdexcept>

int completeTasks(int argc, const char *argv[]);

int main(int argc, const char * argv[])
{
  try {
    return completeTasks(argc, argv);

  } catch (const std::exception & except) {
    std::cerr << except.what() << std::endl;
    return 2;
  }
  
  return 0;
}
