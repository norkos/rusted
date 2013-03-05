#pragma once

#include "Point3.hpp"
#include <vector>
#include <boost/math/special_functions/binomial.hpp>
#include <cmath>

namespace Common
{
namespace Math
{

/**
 * Generic implementation for bezier curves.
 */
template<typename Point, typename CalcType = float> class Bezier
{
	std::vector<Point> points;

public:
	/**
	 * Adds control point for bezier curve. 
	 */
	void addControlPoint(const Point &point)
	{
		points.push_back(point);
	}

	void reset()
	{
        points.clear();
	}

	bool empty()
	{
        return points.empty();
	}

	/**
	 * Returns value for bezier function with t parameter.
	 */
	Point operator()(float t)
	{
        if (points.empty())
        {
            throw std::runtime_error("can't calculate bezier curve, no control points");
        }

		CalcType f = 0;
		CalcType p[3] = {0, 0, 0};
		size_t n = points.size() - 1;

		for (int i = 0; i <= n; i ++)
		{
			f = (CalcType)(boost::math::binomial_coefficient<CalcType>((unsigned int)n, i)*pow(1.0-t, (double)n - i)*pow(t, i));

			p[0] += points[i].getX() * f;
			p[1] += points[i].getY() * f;
			p[2] += points[i].getZ() * f;
		}

		return Point(p[0], p[1], p[2]);
	}

	unsigned getLength()
	{
        // according to http://www.gamedev.net/topic/313018-calculating-the-length-of-a-bezier-curve/ there
        // is no way to calculate length of the Bezier curve so we need to "measure" it

	    const float step = 0.1f;
	    float ret = 0;

	    for (float i = step; i < 1.0f + step; i += step)
	    {
	        Point p1 = (*this)(i - step);
	        Point p2 = (*this)(i);
	        ret += Point::distance(p1, p2);
        }

        return round(ret);
	}
};

}
}

