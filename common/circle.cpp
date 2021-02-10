#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>

alekseev::Circle::Circle(const double rad, const point_t pos) :
	rad_(rad),
	pos_(pos)
{
	assert((rad > 0) && "Radius is zero or negative");
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