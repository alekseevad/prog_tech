#include "composite-shape.hpp"
#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include <math.h>
#include <iostream>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_SUITE(test_compositeshape)

const double EPS = 0.000001;

struct fixture_t
{
	fixture_t() :
        circlePtr(std::make_shared<alekseev::Circle>(2.0, alekseev::point_t{ 0.0, -3.0 })),
        rectanglePtr(std::make_shared<alekseev::Rectangle>(2.0, 4.0, alekseev::point_t{0.0, 2.0} )),
        trianglePtr(std::make_shared<alekseev::Triangle>(alekseev::point_t{ -1.0, 0.0 }, alekseev::point_t{ 1.0, 0.0 }, alekseev::point_t{ 0.0, -4.0 })),
        circlePtr1(std::make_shared<alekseev::Circle>(1.0, alekseev::point_t{ -1.0, 4.0 })),
        circlePtr2(std::make_shared<alekseev::Circle>(1.0, alekseev::point_t{ 1.0, 4.0 })),
        compositeShapePtr(std::make_shared<alekseev::CompositeShape>())
    {
        compositeShapePtr->addShape(circlePtr1);
        compositeShapePtr->addShape(circlePtr2);
        testCmpShape.addShape(circlePtr);
        testCmpShape.addShape(rectanglePtr);
        testCmpShape.addShape(trianglePtr);
        testCmpShape.addShape(compositeShapePtr);
    }

    alekseev::Shape::shape_ptr circlePtr, rectanglePtr, trianglePtr, circlePtr1, circlePtr2;
	std::shared_ptr<alekseev::CompositeShape> compositeShapePtr;
	alekseev::CompositeShape testCmpShape;
};

struct empty_fixture
{
    empty_fixture() : 
        circlePtr(std::make_shared<alekseev::Circle>(4.0, alekseev::point_t{ 10.0, -3.5 })),
        rectanglePtr(std::make_shared<alekseev::Rectangle>(2.0, 8.0, alekseev::point_t{ 12.0, 2.0 })),
        trianglePtr(std::make_shared<alekseev::Triangle>(alekseev::point_t{ -4.0, 0.0 }, alekseev::point_t{ 2.0, 0.0 }, alekseev::point_t{ 0.0, -4.0 })),
        circlePtr1(std::make_shared<alekseev::Circle>(1.5, alekseev::point_t{ -1.0, 4.0 })),
        circlePtr2(std::make_shared<alekseev::Circle>(4.25, alekseev::point_t{ 1.0, 4.0 })),
        compositeShapePtr(std::make_shared<alekseev::CompositeShape>())
    { }
    alekseev::Shape::shape_ptr circlePtr, rectanglePtr, trianglePtr, circlePtr1, circlePtr2;
    std::shared_ptr<alekseev::CompositeShape> compositeShapePtr;
    alekseev::CompositeShape testCmpShape;
};

BOOST_FIXTURE_TEST_CASE(test_construct_adding_removing, empty_fixture)
{
    BOOST_CHECK_NO_THROW(alekseev::CompositeShape testCmpShape);

    BOOST_CHECK(testCmpShape.getSize() == 0);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), 0.0, EPS);

    testCmpShape.addShape(rectanglePtr);

    BOOST_CHECK(testCmpShape.getSize() == 1);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, rectanglePtr->getPosition().x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, rectanglePtr->getPosition().y, EPS);

    testCmpShape.removeShape(0);

    BOOST_CHECK(testCmpShape.getSize() == 0);

    testCmpShape.addShape(circlePtr);

    BOOST_CHECK(testCmpShape.getSize() == 1);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, circlePtr->getPosition().x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, circlePtr->getPosition().y, EPS);

    testCmpShape.removeShape(0);
    compositeShapePtr->addShape(rectanglePtr);
    compositeShapePtr->addShape(circlePtr);
    testCmpShape.addShape(compositeShapePtr);

    BOOST_CHECK(testCmpShape.getSize() == 1);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, compositeShapePtr->getPosition().x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, compositeShapePtr->getPosition().y, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_frame_rect_getter, fixture_t)
{
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().width, 4, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().height, 10, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().pos.x, 0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().pos.y, 0, EPS);
}


BOOST_FIXTURE_TEST_CASE(test_area_getter, fixture_t)
{
    BOOST_CHECK_CLOSE(testCmpShape.getArea(),
        rectanglePtr->getArea() + circlePtr->getArea() + trianglePtr->getArea() + compositeShapePtr->getArea(), EPS);
}

BOOST_FIXTURE_TEST_CASE(test_copy_constructor, fixture_t)
{
    alekseev::CompositeShape testCmpShape2(testCmpShape);

    BOOST_CHECK(testCmpShape2.getSize() == testCmpShape.getSize());
    BOOST_CHECK_CLOSE(testCmpShape2.getPosition().x, testCmpShape.getPosition().x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getPosition().y, testCmpShape.getPosition().y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().width, testCmpShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().height, testCmpShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.x, testCmpShape.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.y, testCmpShape.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getArea(), testCmpShape.getArea(), EPS);
}


BOOST_FIXTURE_TEST_CASE(test_copy_operator, fixture_t)
{
    alekseev::CompositeShape testCmpShape2 = testCmpShape;

    BOOST_CHECK(testCmpShape2.getSize() == testCmpShape.getSize());
    BOOST_CHECK_CLOSE(testCmpShape2.getPosition().x, testCmpShape.getPosition().x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getPosition().y, testCmpShape.getPosition().y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().width, testCmpShape.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().height, testCmpShape.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.x, testCmpShape.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.y, testCmpShape.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getArea(), testCmpShape.getArea(), EPS);
}

BOOST_FIXTURE_TEST_CASE(test_move_constructor, fixture_t)
{
    alekseev::CompositeShape testCmpShape2(std::move(testCmpShape));

    BOOST_CHECK(testCmpShape2.getSize() == 4);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().width, 4.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().height, 10.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.x, 0.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getArea(),
        rectanglePtr->getArea() + trianglePtr->getArea() + circlePtr->getArea() + compositeShapePtr->getArea(), EPS);
    BOOST_CHECK(testCmpShape.getSize() == 0);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), 0, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_move_operator, fixture_t)
{
    alekseev::CompositeShape testCmpShape2 = std::move(testCmpShape);

    BOOST_CHECK(testCmpShape2.getSize() == 4);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().width, 4.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().height, 10.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.x, 0.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE(testCmpShape2.getArea(),
        rectanglePtr->getArea() + trianglePtr->getArea() + circlePtr->getArea() + compositeShapePtr->getArea(), EPS);
    BOOST_CHECK(testCmpShape.getSize() == 0);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), 0, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_brackets, fixture_t)
{
    BOOST_CHECK_EQUAL(testCmpShape[0], circlePtr);
    BOOST_CHECK_EQUAL(testCmpShape[1], rectanglePtr);
    BOOST_CHECK_EQUAL(testCmpShape[2], trianglePtr);
    BOOST_CHECK_EQUAL(testCmpShape[3], compositeShapePtr);
}

BOOST_FIXTURE_TEST_CASE(test_move_to_point, fixture_t)
{
    const std::size_t old_size = testCmpShape.getSize();
    const alekseev::rectangle_t old_frame = testCmpShape.getFrameRect();
    const double old_area = testCmpShape.getArea();
    const alekseev::point_t pos = { -5.0, 3.0 };

    testCmpShape.move(pos);

    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, pos.y, EPS);

    BOOST_CHECK(testCmpShape.getSize() == old_size);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().width, old_frame.width, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().height, old_frame.height, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), old_area, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_moving_to_offset, fixture_t)
{
    const std::size_t old_size = testCmpShape.getSize();
    const alekseev::point_t old_pos = testCmpShape.getPosition();
    const alekseev::rectangle_t old_frame = testCmpShape.getFrameRect();
    const double old_area = testCmpShape.getArea();
    const double dx = 0.0;
    const double dy = 19.0;

    testCmpShape.move(dx, dy);

    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, old_pos.x + dx, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, old_pos.y + dy, EPS);

    BOOST_CHECK(testCmpShape.getSize() == old_size);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().width, old_frame.width, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().height, old_frame.height, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), old_area, EPS);
}


BOOST_FIXTURE_TEST_CASE(test_scale_increase, fixture_t)
{
    const std::size_t old_size = testCmpShape.getSize();
    const alekseev::point_t old_pos = testCmpShape.getPosition();
    const alekseev::rectangle_t old_frame = testCmpShape.getFrameRect();
    const double old_area = testCmpShape.getArea();
    const alekseev::point_t old_circle_pos = testCmpShape[0]->getPosition();
    const alekseev::point_t old_rectangle_pos = testCmpShape[1]->getPosition();
    const alekseev::point_t old_composite_shape_pos = testCmpShape[3]->getPosition();
    const double coef = 3;

    testCmpShape.scale(coef);

    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().width, old_frame.width * coef, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().height, old_frame.height * coef, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), old_area * std::pow(coef, 2), EPS);
    BOOST_CHECK_CLOSE(testCmpShape[0]->getPosition().x, (old_circle_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[0]->getPosition().y, (old_circle_pos.y - old_pos.y) * coef + old_pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[1]->getPosition().x, (old_rectangle_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[1]->getPosition().y, (old_rectangle_pos.y - old_pos.y) * coef + old_pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[3]->getPosition().x, (old_composite_shape_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[3]->getPosition().y, (old_composite_shape_pos.y - old_pos.y) * coef + old_pos.y, EPS);

    BOOST_CHECK(testCmpShape.getSize() == old_size);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, old_pos.y, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_scale_reduction, fixture_t)
{
    const std::size_t old_size = testCmpShape.getSize();
    const alekseev::point_t old_pos = testCmpShape.getPosition();
    const alekseev::rectangle_t old_frame = testCmpShape.getFrameRect();
    const double old_area = testCmpShape.getArea();
    const alekseev::point_t old_circle_pos = testCmpShape[0]->getPosition();
    const alekseev::point_t old_rectangle_pos = testCmpShape[1]->getPosition();
    const alekseev::point_t old_composite_shape_pos = testCmpShape[3]->getPosition();
    const double coef = 0.5;

    testCmpShape.scale(coef);

    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().width, old_frame.width * coef, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getFrameRect().height, old_frame.height * coef, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getArea(), old_area * std::pow(coef, 2), EPS);
    BOOST_CHECK_CLOSE(testCmpShape[0]->getPosition().x, (old_circle_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[0]->getPosition().y, (old_circle_pos.y - old_pos.y) * coef + old_pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[1]->getPosition().x, (old_rectangle_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[1]->getPosition().y, (old_rectangle_pos.y - old_pos.y) * coef + old_pos.y, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[3]->getPosition().x, (old_composite_shape_pos.x - old_pos.x) * coef + old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape[3]->getPosition().y, (old_composite_shape_pos.y - old_pos.y) * coef + old_pos.y, EPS);

    BOOST_CHECK(testCmpShape.getSize() == old_size);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().x, old_pos.x, EPS);
    BOOST_CHECK_CLOSE(testCmpShape.getPosition().y, old_pos.y, EPS);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_arguments, fixture_t)
{
    BOOST_CHECK_THROW(testCmpShape.addShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(testCmpShape.scale(0), std::invalid_argument);
    BOOST_CHECK_THROW(testCmpShape.scale(-1), std::invalid_argument);

    std::shared_ptr<alekseev::CompositeShape> testCmpPtr
        = std::make_shared<alekseev::CompositeShape>(alekseev::CompositeShape());

    BOOST_CHECK_THROW(testCmpPtr->addShape(testCmpPtr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_out_of_range, fixture_t)
{
    BOOST_CHECK_THROW(testCmpShape[4], std::out_of_range);
    BOOST_CHECK_THROW(testCmpShape[5], std::out_of_range);
    BOOST_CHECK_THROW(testCmpShape.removeShape(4), std::out_of_range);
    BOOST_CHECK_THROW(testCmpShape.removeShape(5), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(test_logic_errors, empty_fixture)
{
    BOOST_CHECK_THROW(testCmpShape.getPosition(), std::logic_error);
    BOOST_CHECK_THROW(testCmpShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(testCmpShape.move({ 5, -4.3 }), std::logic_error);
    BOOST_CHECK_THROW(testCmpShape.move(-9, 2), std::logic_error);
    BOOST_CHECK_THROW(testCmpShape.scale(7), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()