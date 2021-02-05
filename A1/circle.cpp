#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>

Circle::Circle(const double rad, const point_t pos) :
	rad_(rad),
	pos_(pos)
{
	assert((rad > 0) && "Radius is zero or negative");
}

void Circle::move(const point_t& pos)
{
	pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
	pos_.x += dx;
	pos_.y += dy;
}

double Circle::getArea() const
{
	return ( M_PI * rad_ * rad_ );
}

rectangle_t Circle::getFrameRect() const
{
	rectangle_t tempRect;
	tempRect.width = 2 * rad_;
	tempRect.height = 2 * rad_;
	tempRect.pos = pos_;
	return tempRect;
}