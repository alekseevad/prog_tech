#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(test_circle)

const double EPS = 0.000001;
const alekseev::point_t POSITION = { 5.5, 10 };
const double RAD = 4.25;
const double AREA = M_PI * 18.0625;

BOOST_AUTO_TEST_CASE(test_constructor_getters)
{
    BOOST_CHECK_NO_THROW(alekseev::Circle test_cir(RAD, POSITION));

    alekseev::Circle test_circle(RAD, POSITION);

    BOOST_CHECK_CLOSE(test_circle.getPos().x, POSITION.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getPos().y, POSITION.y, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad(), RAD, EPS);
}

BOOST_AUTO_TEST_CASE(test_frame_rect)
{
    alekseev::Circle test_circle(RAD, POSITION);

    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.x, POSITION.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.y, POSITION.y, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().width, RAD * 2, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().height, RAD * 2, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_pos)
{
    alekseev::Circle test_circle(RAD, POSITION);
    const alekseev::point_t new_pos = {5, 10.5};
    test_circle.move(new_pos);

    BOOST_CHECK_CLOSE(test_circle.getPos().x, new_pos.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getPos().y, new_pos.y, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.x, new_pos.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.y, new_pos.y, EPS);

    BOOST_CHECK_CLOSE(test_circle.getArea(), AREA, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad(), RAD, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().height, RAD * 2, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().width, RAD * 2, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_offset)
{
    alekseev::Circle test_circle(RAD, POSITION);
    const double dx = 1.1;
    const double dy = 3.5;
    test_circle.move(dx, dy);

    BOOST_CHECK_CLOSE(test_circle.getPos().x, POSITION.x + dx, EPS);
    BOOST_CHECK_CLOSE(test_circle.getPos().y, POSITION.y + dy, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.x, POSITION.x + dx, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().pos.y, POSITION.y + dy, EPS);

    BOOST_CHECK_CLOSE(test_circle.getArea(), AREA, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad(), RAD, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().height, RAD * 2, EPS);
    BOOST_CHECK_CLOSE(test_circle.getFrameRect().width, RAD * 2, EPS);
}

BOOST_AUTO_TEST_CASE(test_scale)
{
    alekseev::Circle test_circle(RAD, POSITION);
    const double coef = 5;
    test_circle.scale(coef);

    BOOST_CHECK_CLOSE(test_circle.getPos().x, POSITION.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getPos().y, POSITION.y, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad(), RAD * coef, EPS);
    BOOST_CHECK_CLOSE(test_circle.getArea(), AREA * std::pow(coef, 2), EPS);

    BOOST_CHECK_CLOSE(test_circle.getPos().x, test_circle.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(test_circle.getPos().y, test_circle.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad() * 2, test_circle.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(test_circle.getRad() * 2, test_circle.getFrameRect().height, EPS);
}


BOOST_AUTO_TEST_CASE(test_invalid_arguments)
{
    BOOST_CHECK_THROW(alekseev::Circle test_cir(-4, POSITION), std::invalid_argument);
    BOOST_CHECK_THROW(alekseev::Circle test_cir(0, POSITION), std::invalid_argument);

    alekseev::Circle test_circle(RAD, POSITION);

    BOOST_CHECK_THROW(test_circle.scale(-3), std::invalid_argument);
    BOOST_CHECK_THROW(test_circle.scale(0), std::invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END()