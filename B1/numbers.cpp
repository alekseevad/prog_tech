#include "numbers.hpp"

void Numbers::sort1(const char* order)
{
	const Order right_order = checkOrder(order);

	this->readData();

	if (right_order == Order::ASCENDING)
	{
		for (std::size_t startIndex = 0; startIndex < arr_.size(); ++startIndex)
		{
			int smallestIndex = startIndex;

			for (std::size_t currentIndex = startIndex + 1; currentIndex < arr_.size(); ++currentIndex)
			{
				if (arr_[currentIndex] < arr_[smallestIndex])
					smallestIndex = currentIndex;
			}

			std::swap(arr_[startIndex], arr_[smallestIndex]);
		}
	}
	else if (right_order == Order::DESCENDING)
	{
		for (std::size_t startIndex = 0; startIndex < arr_.size(); ++startIndex)
		{
			int smallestIndex = startIndex;

			for (std::size_t currentIndex = startIndex + 1; currentIndex < arr_.size(); ++currentIndex)
			{
				if (arr_[currentIndex] > arr_[smallestIndex])
					smallestIndex = currentIndex;
			}

			std::swap(arr_[startIndex], arr_[smallestIndex]);
		}
	}
}

/*void Numbers::sort2(const Order order)
{
	std::vector<int> vector2;
	if (order == Order::ASCENDING)
	{
		for (int startIndex = 0; startIndex < size_; ++startIndex)
		{
			int smallestIndex = startIndex;

			for (int currentIndex = startIndex + 1; currentIndex < size_; ++currentIndex)
			{
				if (arr_[currentIndex] < arr_[smallestIndex])
					smallestIndex = currentIndex;
			}

			std::swap(arr_.at(startIndex), arr_.at(smallestIndex));
		}
	}
	else if (order == Order::DESCENDING)
	{
		for (int startIndex = 0; startIndex < size_; ++startIndex)
		{
			int smallestIndex = startIndex;

			for (int currentIndex = startIndex + 1; currentIndex < size_; ++currentIndex)
			{
				if (arr_[currentIndex] > arr_[smallestIndex])
					smallestIndex = currentIndex;
			}

			std::swap(arr_.at(startIndex), arr_.at(smallestIndex));
		}
	}
} */

void Numbers::printData()
{

}

void Numbers::readData()
{
	int pars;

	if (type_ == 0)
	{
		while (std::cin >> pars)
		{
			arr_.push_back(pars);
		}
	} 
	else
	{
		while (std::cin >> pars)
		{
			list_.push_back(pars);
		}
	}
	
	/*if (std::cin.eof() == false)
	{
		throw std::invalid_argument("File must end up with EOF char");
	}*/
}

void Numbers::setType(int type)
{
	type_ = type;
}

Numbers::~Numbers()
{

}

Order checkOrder(const char* order)
{
	if (order == nullptr)
	{
		throw std::invalid_argument("Invalid order!");
	}
	if (std::strcmp(order, "ascending") == 0)
	{
		return Order::ASCENDING;
	}
	else if (std::strcmp(order, "descending") == 0)
	{
		return Order::DESCENDING;
	}
	else
	{
		throw std::invalid_argument("Invalid order!");
	}
}