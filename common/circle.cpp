#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

alekseev::Circle::Circle(const double rad, const point_t& pos) :
	rad_(rad),
	pos_(pos)
{
	if (rad <= 0)
	{
		throw std::invalid_argument("Radius is zero or negative");
	}
}

void alekseev::Circle::move(const point_t& pos)
{
	pos_ = pos;
}

void alekseev::Circle::move(const double dx, const double dy)
{
	pos_.x += dx;
	pos_.y += dy;
}

double alekseev::Circle::getArea() const
{
	return ( M_PI * rad_ * rad_ );
}

alekseev::rectangle_t alekseev::Circle::getFrameRect() const
{
	rectangle_t tempRect;
	tempRect.width = 2 * rad_;
	tempRect.height = 2 * rad_;
	tempRect.pos = pos_;
	return tempRect;
}

void alekseev::Circle::scale(const double mult)
{
	if (mult <= 0)
	{
		throw std::invalid_argument("Multyplier must be positive");
	}
	rad_ *= mult;
}

alekseev::point_t alekseev::Circle::getPos() const
{
	return pos_;
}

double alekseev::Circle::getRad() const 
{
	return rad_;
}