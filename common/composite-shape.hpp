#ifndef _COMPOSITE_SHAPE_HPP_
#define _COMPOSITE_SHAPE_HPP_
#include "../common/shape.hpp"

namespace alekseev 
{ 
    struct point_t;
    struct rectangle_t;
    
    class CompositeShape : public Shape
    {
    public:
        CompositeShape();
        CompositeShape(const CompositeShape& another);
        CompositeShape(CompositeShape&& another);

        CompositeShape& operator=(const CompositeShape& another);
        CompositeShape& operator=(CompositeShape&& another);
        shape_ptr operator[](const size_t index) const;

        double getArea() const override;
        rectangle_t getFrameRect() const override;

        void move(const double dx, const double dy) override;
        void move(const point_t& pos) override;
        void scale(const double mult) override;
    private:
        shape_array array_;
        std::size_t size_;
    };
}

#endif