#ifndef _BASE_TYPES_HPP_
#define _BASE_TYPES_HPP_

namespace alekseev
{
	struct point_t
	{
		double x;
		double y;
	};

	struct rectangle_t
	{
		double width;
		double height;
		point_t pos;
	};
}

#endif