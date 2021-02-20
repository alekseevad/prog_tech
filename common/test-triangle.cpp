#include "triangle.hpp"
#define _USE_MATH_DEFINES
#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <math.h>

BOOST_AUTO_TEST_SUITE(triangle_test)

const double EPS = 0.000001;
const alekseev::point_t A = { 7.0, 3.0 };
const alekseev::point_t B = { 3.0, 2.0 };
const alekseev::point_t C = { 5.0, -2.0 };
const alekseev::point_t CENTRE = { (A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3 };
const alekseev::rectangle_t FRAME = { 4.0, 5.0, {5.0, 0.5} };
const double AREA = 9.0;

BOOST_AUTO_TEST_CASE(test_construct_getters)
{
	const alekseev::Triangle test_tri(A, B, C);

	BOOST_CHECK_CLOSE(test_tri.getCentre().x, CENTRE.x, EPS);
	BOOST_CHECK_CLOSE(test_tri.getCentre().y, CENTRE.y, EPS);
	BOOST_CHECK_CLOSE(test_tri.getArea(), AREA, EPS);

	BOOST_CHECK_CLOSE(test_tri.getPoint(0).x, A.x, EPS);
	BOOST_CHECK_CLOSE(test_tri.getPoint(0).y, A.y, EPS);
	BOOST_CHECK_CLOSE(test_tri.getPoint(1).x, B.x, EPS);
	BOOST_CHECK_CLOSE(test_tri.getPoint(1).y, B.y, EPS);
	BOOST_CHECK_CLOSE(test_tri.getPoint(2).x, C.x, EPS);
	BOOST_CHECK_CLOSE(test_tri.getPoint(2).y, C.y, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_pos)
{
	alekseev::Triangle test_tri(A, B, C);
	const alekseev::point_t new_pos = { 2.0, 3.0 };

	test_tri.move(new_pos);

	BOOST_CHECK_CLOSE(test_tri.getCentre().x, new_pos.x, EPS);
	BOOST_CHECK_CLOSE(test_tri.getCentre().y, new_pos.y, EPS);
	BOOST_CHECK_CLOSE(test_tri.getArea(), AREA, EPS);

	BOOST_CHECK_CLOSE(test_tri.getFrameRect().width, FRAME.width, EPS);
	BOOST_CHECK_CLOSE(test_tri.getFrameRect().height, FRAME.height, EPS);
}

BOOST_AUTO_TEST_CASE(test_move_to_offset)
{
	const double dx = 12;
	const double dy = -20;

	alekseev::Triangle test_tri(A, B, C);
	test_tri.move(12, -20);

	BOOST_CHECK_CLOSE(test_tri.getCentre().x, CENTRE.x + dx, EPS);
	BOOST_CHECK_CLOSE(test_tri.getCentre().y, CENTRE.y + dy, EPS);
	BOOST_CHECK_CLOSE(test_tri.getArea(), AREA, EPS);

	BOOST_CHECK_CLOSE(test_tri.getFrameRect().width, FRAME.width, EPS);
	BOOST_CHECK_CLOSE(test_tri.getFrameRect().height, FRAME.height, EPS);
}

BOOST_AUTO_TEST_CASE(test_scale)
{
	const double coef = 2;
	alekseev::Triangle test_tri(A, B, C);
	test_tri.scale(coef);

	BOOST_CHECK_CLOSE(test_tri.getArea(), AREA * std::pow(coef,2), EPS);
	
	BOOST_CHECK_CLOSE(test_tri.getFrameRect().width, FRAME.width * coef, EPS);
	BOOST_CHECK_CLOSE(test_tri.getFrameRect().height, FRAME.height * coef, EPS);

	BOOST_CHECK_EQUAL(test_tri.getCentre().x, CENTRE.x);
	BOOST_CHECK_EQUAL(test_tri.getCentre().y, CENTRE.y);
}

BOOST_AUTO_TEST_CASE(test_invalid_args)
{
	alekseev::Triangle test_triangle(A, B, C);

	BOOST_CHECK_THROW(alekseev::Triangle test_tri({ 1.0, 0.0 }, { 3.5, 0.0 }, { 12.5, 0.0 }), std::invalid_argument);
	BOOST_CHECK_THROW(test_triangle.scale(-3), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()