#include "rectangle.hpp"

alekseev::Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
	width_(width),
	height_(height),
	pos_(pos)
{
	assert((width > 0) && (height > 0) && "Wrong args for rectangle");
}

void alekseev::Rectangle::move(const point_t& pos)
{
	pos_ = pos;
}

void alekseev::Rectangle::move(const double dx, const double dy)
{
	pos_.x += dx;
	pos_.y += dy;
}

alekseev::rectangle_t alekseev::Rectangle::getFrameRect() const
{
	rectangle_t tempRect;
	tempRect.height = height_;
	tempRect.width = width_;
	tempRect.pos = pos_;
	return( tempRect );
}

double alekseev::Rectangle::getArea() const
{
	return ( width_ * height_ );
}

alekseev::point_t alekseev::Rectangle::getPos() const
{
	return ( pos_ );
}

double alekseev::Rectangle::getWidth() const
{
	return ( width_ );
}

double alekseev::Rectangle::getHeight() const
{
	return ( height_ );
}