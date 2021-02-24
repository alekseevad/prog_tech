#ifndef _NUMBERS_VECTOR_HPP
#define _NUMBERS_VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

enum class Order
{
	ASCENDING,
	DESCENDING
};

template <typename T>
class Numbers
{
public:
	Numbers<T>(int s, const Order order) :
		sort_type_(s),
		sort_order_(order)
	{

		size_ = 0;
		switch (sort_type_) {
			case 1:
				sort(order);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				throw std::invalid_argument("Wrong type of sort");
				break;
		}
	}
	template <typename T1>
	friend std::ostream& operator<<(std::ostream& out, const Numbers<T1>& data);
	template <typename T1>
	friend std::istream& operator>>(std::istream& in, Numbers<T1>& data);
	void readData();
	void sort(const Order order, const int type);

private:
	std::size_t size_ ;
	Order sort_order_;
	int sort_type_;
	T arr_;
	T list_;
};

template <typename T>
void Numbers<T>::readData()
{
	if (std::cin.eof() == false)
		throw std::invalid_argument("File must end up with EOF char");
}

template <typename T>
void Numbers<T>::sort(const Order order, const int type)
{

}

template <typename T1>
std::ostream& operator<<(std::ostream& out, const Numbers<T1>& data)
{
	for(std::size_t i = 0; i < data.size_; ++i)
		out << data.arr_[i] << " ";
	return out;
}

template <typename T1>
std::istream& operator>>(std::istream& in, Numbers<T1>& data)
{
	int pars = 0;
	while (pars != -1)
	{
		std::cin >> pars;
		data.arr_.push_back(pars);
		++data.size_;
	}
	return in;
}

#endif