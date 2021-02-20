#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_
#include "shape.hpp"

namespace alekseev
{
	class Triangle : public Shape
	{
	public:
		Triangle(const point_t& a, const point_t& b, const point_t& c);

		void move(const point_t& pos) override;
		void move(const double dx, const double dy) override;

		point_t getPosition() const override;
		rectangle_t getFrameRect() const override;
		double getArea() const override;
		void scale(const double mult) override;

		point_t getCentre() const; 
		point_t getPoint(const size_t index) const;
	private:
		point_t arr_[3];
	};
}

#endif
