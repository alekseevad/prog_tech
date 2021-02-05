#include "base-types.hpp"
#include "rectangle.hpp"

Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
width_(width), height_(height), pos_(pos)
{ }

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
	tempRect.height = this->height_;
	tempRect.width = this->width_;
	tempRect.pos = this->pos_;
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