#ifndef _SHAPE_HPP_
#define _SHAPE_HPP_

#include "base-types.hpp"
#include <memory>

namespace alekseev
{
    class Shape
    {
    public:
        typedef std::shared_ptr<Shape> shape_ptr;
        typedef std::unique_ptr<shape_ptr[]> shape_array;

        virtual ~Shape() = default;

        virtual void move(const point_t& pos) = 0;
        virtual void move(const double dx, const double dy) = 0;

        virtual rectangle_t getFrameRect() const = 0;
        virtual double getArea() const = 0;
        virtual void scale(const double mult) = 0;
    };
}

#endif