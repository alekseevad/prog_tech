#ifndef _SHAPE_HPP_
#define _SHAPE_HPP_
#include "base-types.hpp"

namespace alekseev
{
    class Shape
    {
    public:
        virtual ~Shape() = default;

        virtual void move(const point_t& pos) = 0;
        virtual void move(const double dx, const double dy) = 0;

        virtual rectangle_t getFrameRect() const = 0;
        virtual double getArea() const = 0;
    };
}

#endif