#include "composite-shape.hpp"

alekseev::CompositeShape::CompositeShape() :
    array_(nullptr),
    size_(0)
{ }

alekseev::CompositeShape::CompositeShape(const CompositeShape& another) :
    array_(nullptr),
    size_(another.size_)
{
    if(size_ != 0)
    {
        array_ = shape_array(new shape_ptr[size_]);
        for(size_t i = 0; i < size_; ++i)
        {
            array_[i] = another.array_[i];
        }
    }
}

