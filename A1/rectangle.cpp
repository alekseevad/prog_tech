#include "rectangle.hpp"

Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
	width_(width),
	height_(height),
	pos_(pos)
{
	assert((width > 0) && (height > 0) && "Wrong args for rectangle");
}

void Rectangle::move(const point_t& pos)
{
	pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
	pos_.x += dx;
	pos_.y += dy;
}

rectangle_t Rectangle::getFrameRect() const
{
	rectangle_t tempRect;
	tempRect.height = height_;
	tempRect.width = width_;
	tempRect.pos = pos_;
	return( tempRect );
}

double Rectangle::getArea() const
{
	return ( width_ * height_ );
}

point_t Rectangle::getPos() const
{
	return ( pos_ );
}

double Rectangle::getWidth() const
{
	return ( width_ );
}

double Rectangle::getHeight() const
{
	return ( height_ );
}