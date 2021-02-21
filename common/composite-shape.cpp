#include "composite-shape.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>
#include <algorithm>

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

alekseev::CompositeShape::CompositeShape(CompositeShape&& another) noexcept :
    array_(nullptr),
    size_(another.size_)
{
    if(size_ != 0)
    {
        array_ = std::move(another.array_);
        another.size_ = 0;
    }
}

alekseev::Shape::shape_ptr alekseev::CompositeShape::operator[](const size_t index) const
{
    if((index < 0) || (index >= size_))
    {
        throw std::out_of_range("Out of range");
    }
    return array_[index];
}

alekseev::CompositeShape& alekseev::CompositeShape::operator=(const CompositeShape& another)
{
    if(&another != this)
    {
        if(another.size_ != 0)
        {
            shape_array temp(new shape_ptr[another.size_]);
            for(size_t i = 0; i < size_; ++i)
            {
                temp[i] = another.array_[i];
            }
            array_ = std::move(temp);
            size_ = another.size_;
        }
    }
    else
    {
        array_ = nullptr;
        size_ = 0;
    }
    return *this;
}

alekseev::CompositeShape& alekseev::CompositeShape::operator=(CompositeShape&& another) noexcept
{
    if(&another.size_ != 0)
    {
        array_ = std::move(another.array_);
        another.size_ = 0;
    }
    else 
    {
        array_ = nullptr;
        size_ = 0;
    }
    return *this;
}

void alekseev::CompositeShape::addShape(const shape_ptr new_shape)
{
    if ((new_shape.get() == this) || (new_shape == nullptr))
    {
        throw std::invalid_argument("Shape cannot be part of itself");
    }
    shape_array tempArr(new shape_ptr[size_ + 1]);
    for (size_t i = 0; i < size_; i++)
    {
        tempArr[i] = array_[i];
    }
    tempArr[size_] = new_shape;
    size_++;
    array_ = std::move(tempArr);
}

void alekseev::CompositeShape::removeShape(const size_t index)
{
    if ((index >= size_) || (index < 0))
    {
        throw std::out_of_range("Out of range");
    }

    for (size_t i = index; i < size_ - 1; i++)
    {
        array_[i] = array_[i + 1];
    }
    size_--;
    array_[size_].reset();
}

double alekseev::CompositeShape::getArea() const
{
    double result = 0.0;
    if(size_ != 0)
    {
        for(size_t i = 0; i < size_; ++i)
        {
            result += array_[i]->getArea();
        }
    }
    return result;
}

alekseev::rectangle_t alekseev::CompositeShape::getFrameRect() const
{
    if(size_ == 0)
    {
        throw std::logic_error("Can't get frame out of nothing");
    }
    rectangle_t frame = array_[0]->getFrameRect();
    double minX = frame.pos.x - frame.width / 2;
    double maxX = frame.pos.x + frame.width / 2;
    double minY = frame.pos.y - frame.height / 2;
    double maxY = frame.pos.y + frame.height / 2;
    for (size_t i = 1; i < size_; i++)
    {
        frame = array_[i]->getFrameRect();
        minX = std::min(minX, frame.pos.x - frame.width / 2);
        maxX = std::max(maxX, frame.pos.x + frame.width / 2);
        minY = std::min(minY, frame.pos.y - frame.height / 2);
        maxY = std::max(maxY, frame.pos.y + frame.height / 2);
    }
    return rectangle_t{ maxX - minX, maxY - minY, { maxX - (maxX - minX) / 2, maxY - (maxY - minY) / 2 } };
}

void alekseev::CompositeShape::move(const double dx, const double dy)
{
    if(size_ == 0)
    {
        throw std::logic_error("Can't move empty shape");
    }
    for(size_t i = 0; i < size_; ++i)
    {
        array_[i]->move(dx, dy);
    }
}

void alekseev::CompositeShape::move(const point_t& pos)
{
    if(size_ == 0)
    {
        throw std::logic_error("Can't move empty shape");
    }
    const point_t old_pos = getFrameRect().pos;
    move(pos.x - old_pos.x, pos.y - old_pos.y);
}

void alekseev::CompositeShape::scale(const double mult)
{
    if(mult <= 0)
    {
        throw std::invalid_argument("Negative or zero argument");
    }
    if(size_ == 0)
    {
        throw std::logic_error("Can't scale empty shape");
    }
    const point_t pos = getFrameRect().pos;
    for (size_t i = 0; i < size_; ++i)
    {
        array_[i]->move({ pos.x + (array_[i]->getFrameRect().pos.x - pos.x) * mult,
        pos.y + (array_[i]->getFrameRect().pos.y - pos.y) * mult });
        array_[i]->scale(mult);
    }
}


alekseev::point_t alekseev::CompositeShape::getPosition() const
{
    if (size_ == 0)
    {
        throw std::logic_error("Empty Shape can't have a position");
    }
    return getFrameRect().pos;
}

std::size_t alekseev::CompositeShape::getSize() const
{
    return size_;
}