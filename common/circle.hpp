#ifndef _CIRCLE_HPP_
#define _CIRCLE_HPP_
#include "shape.hpp"

namespace alekseev
{
	class Circle : public Shape
	{
	public:
		Circle(const double rad, const point_t pos);

		void move(const point_t& pos) override;
		void move(const double x, const double y) override;

		double getArea() const override;
		rectangle_t getFrameRect() const override;
		void scale(const double mult) override;
	private:
		point_t pos_;
		double rad_;
	};
}

#endif