#include "rectangle.hpp"
#include <cassert>

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

void alekseev::Rectangle::scale(const double mult)
{
	assert((mult > 0) && ("Wrong multiplier"));
	width_ *= mult;
	height_ *= mult;
}
