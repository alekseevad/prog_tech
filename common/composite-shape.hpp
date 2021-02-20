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
        CompositeShape(CompositeShape&& another) noexcept;

        CompositeShape& operator=(const CompositeShape& another);
        CompositeShape& operator=(CompositeShape&& another) noexcept;
        shape_ptr operator[](const size_t index) const;
        
        point_t getPosition() const override;
        double getArea() const override;
        rectangle_t getFrameRect() const override;

        void addShape(const shape_ptr new_shape);
        void removeShape(const size_t index);

        void move(const double dx, const double dy) override;
        void move(const point_t& pos) override;
        void scale(const double mult) override;

        std::size_t getSize() const;
    private:
        shape_array array_;
        std::size_t size_;
    };
}

#endif
