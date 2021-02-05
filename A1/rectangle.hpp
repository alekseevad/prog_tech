#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_
#include "shape.hpp"
#include <cassert>
//#include "base-types.hpp"

class Rectangle : public Shape
{
public:
	Rectangle(const double width, const double height, const point_t& pos);

	void move(const point_t& pos) override;
	void move(const double dx, const double dy) override;

	rectangle_t getFrameRect() const override;
	double getArea() const override;

	point_t getPos() const;
	double getWidth() const;
	double getHeight() const;
private:
	double width_;
	double height_;
	point_t pos_;
};

#endif