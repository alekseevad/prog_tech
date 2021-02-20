#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(test_rect)

const double EPS = 0.000001;
const double WIDTH = 4.8;
const double HEIGHT = 7.1;
const alekseev::point_t POS = { 0.0, 15.7 };
const double AREA = 34.08;


BOOST_AUTO_TEST_CASE(test_constructor_getters)
{
	alekseev::Rectangle test_rect(WIDTH, HEIGHT, POS);

	BOOST_CHECK_CLOSE(test_rect.getHeight(), HEIGHT, EPS);
	BOOST_CHECK_CLOSE(test_rect.getWidth(), WIDTH, EPS);
	BOOST_CHECK_CLOSE(test_rect.getPos().x, POS.x, EPS);
	BOOST_CHECK_CLOSE(test_rect.getPos().y, POS.y, EPS);
}

BOOST_AUTO_TEST_CASE(test_frame_rect)
{
	alekseev::Rectangle test_rect(WIDTH, HEIGHT, POS);

	BOOST_CHECK_CLOSE(test_rect.getFrameRect().height, HEIGHT, EPS);
	BOOST_CHECK_CLOSE(test_rect.getFrameRect().width, WIDTH, EPS);
	BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.x, POS.x, EPS);
	BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.y, POS.y, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_pos)
{
    alekseev::Rectangle test_rect(WIDTH, HEIGHT, POS);
    const alekseev::point_t new_pos = { 5, 10.5 };
    test_rect.move(new_pos);

    BOOST_CHECK_CLOSE(test_rect.getPos().x, new_pos.x, EPS);
    BOOST_CHECK_CLOSE(test_rect.getPos().y, new_pos.y, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.x, new_pos.x, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.y, new_pos.y, EPS);

    BOOST_CHECK_CLOSE(test_rect.getArea(), AREA, EPS);
    BOOST_CHECK_CLOSE(test_rect.getWidth(), WIDTH, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().height, HEIGHT, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().width, WIDTH, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_offset)
{
    alekseev::Rectangle test_rect(WIDTH, HEIGHT, POS);
    const double dx = 1.1;
    const double dy = 3.5;
    test_rect.move(dx, dy);

    BOOST_CHECK_CLOSE(test_rect.getPos().x, POS.x + dx, EPS);
    BOOST_CHECK_CLOSE(test_rect.getPos().y, POS.y + dy, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.x, POS.x + dx, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.y, POS.y + dy, EPS);

    BOOST_CHECK_CLOSE(test_rect.getArea(), AREA, EPS);
    BOOST_CHECK_CLOSE(test_rect.getWidth(), WIDTH, EPS);
    BOOST_CHECK_CLOSE(test_rect.getHeight(), HEIGHT, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().height, HEIGHT, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().width, WIDTH, EPS);
}

BOOST_AUTO_TEST_CASE(test_scale)
{
    alekseev::Rectangle test_rect(WIDTH, HEIGHT, POS);
    const double coef = 3;
    test_rect.scale(coef);

    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.x, POS.x, EPS);
    BOOST_CHECK_CLOSE(test_rect.getFrameRect().pos.y, POS.y, EPS);
    BOOST_CHECK_CLOSE(test_rect.getWidth(), WIDTH * coef, EPS);
    BOOST_CHECK_CLOSE(test_rect.getHeight(), HEIGHT * coef, EPS);
    BOOST_CHECK_CLOSE(test_rect.getArea(), AREA * std::pow(coef, 2), EPS);

    BOOST_CHECK_CLOSE(test_rect.getPos().x, test_rect.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(test_rect.getPos().y, test_rect.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(test_rect.getWidth(), test_rect.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(test_rect.getHeight(), test_rect.getFrameRect().height, EPS);
}

BOOST_AUTO_TEST_CASE(test_invalid_arguments)
{
    BOOST_CHECK_THROW(alekseev::Rectangle test_rect(5, -4, POS), std::invalid_argument);
    BOOST_CHECK_THROW(alekseev::Rectangle test_rect(4, 0, POS), std::invalid_argument);

    alekseev::Rectangle test_rectangle(4, 4, { 0.0, 0.0 });

    BOOST_CHECK_THROW(test_rectangle.scale(-3), std::invalid_argument);
    BOOST_CHECK_THROW(test_rectangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()