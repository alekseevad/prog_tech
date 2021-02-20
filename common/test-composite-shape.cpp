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



BOOST_AUTO_TEST_SUITE_END()