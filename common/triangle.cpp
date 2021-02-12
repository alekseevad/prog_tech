#include "triangle.hpp"
#include <cassert>
#include <iostream>


alekseev::Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c) :
	arr_{a, b, c}
{
	assert((this->getArea() != 0) && "Enter valid points");
}

void alekseev::Triangle::move(const point_t& pos)
{
	const point_t destination = { pos.x - getCentre().x, pos.y - getCentre().y };
	alekseev::Triangle::move(destination.x, destination.y);
}

void alekseev::Triangle::move(const double dx, const double dy)
{
	for (point_t& current : arr_)
	{
		current.x += dx;
		current.y += dy;
	}
}

alekseev::rectangle_t alekseev::Triangle::getFrameRect() const
{
	const double minX = std::min(std::min(arr_[0].x, arr_[1].x), arr_[2].x);
	const double maxX = std::max(std::max(arr_[0].x, arr_[1].x), arr_[2].x);
	const double minY = std::min(std::min(arr_[0].y, arr_[1].y), arr_[2].y);
	const double maxY = std::max(std::max(arr_[0].y, arr_[1].y), arr_[2].y);
	return rectangle_t{ maxX - minX, maxY - minY, {minX + (maxX - minX) / 2,  minY + (maxY - minY) / 2 } };
}

double alekseev::Triangle::getArea() const
{
	return(0.5 * ((arr_[0].x - arr_[2].x) * (arr_[1].y - arr_[2].y) - (arr_[1].x - arr_[2].x) * (arr_[0].y - arr_[2].y)));
}

alekseev::point_t alekseev::Triangle::getCentre() const
{
	return point_t{ (arr_[0].x + arr_[1].x + arr_[2].x) / 3, (arr_[0].y + arr_[1].y + arr_[2].y) / 3 };
}

void alekseev::Triangle::scale(const double mult)
{
	const point_t centre = this->getCentre();
	assert((mult > 0) && "Wrong multyplier");
	for (point_t& temp : arr_)
	{
		temp.x = centre.x + (temp.x - centre.x) * mult;
		temp.y = centre.y + (temp.y - centre.y) * mult;
	}
}
