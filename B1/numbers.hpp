#ifndef _NUMBERS_VECTOR_HPP
#define _NUMBERS_VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

enum class Order
{
	ASCENDING,
	DESCENDING
};

class Numbers
{
public:
	void printData();
	void readData();

	void sort1(const char* order);
	void sort2(const char* order);
	void sort3();

	void setType(int type);

	~Numbers();
private:
	int type_;
	std::vector<int> arr_;
	std::list<int> list_;
};

Order checkOrder(const char* order);

#endif