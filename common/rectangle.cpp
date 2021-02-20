#include "rectangle.hpp"
#include <stdexcept>

alekseev::Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
	width_(width),
	height_(height),
	pos_(pos)
{
	if ((width <= 0) || (height <= 0))
	{
		throw std::invalid_argument("Width/Height must be positive");
	}
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
	if (mult <= 0)
	{
		throw std::invalid_argument("Multyplier must be positive");
	}
	width_ *= mult;
	height_ *= mult;
}

alekseev::point_t alekseev::Rectangle::getPosition() const
{
	return getFrameRect().pos;
}

double alekseev::Rectangle::getHeight() const
{
	return height_;
}

double alekseev::Rectangle::getWidth() const
{
	return width_;
}
