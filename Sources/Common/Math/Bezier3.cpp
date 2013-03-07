#include "Bezier3.hpp"

using namespace Common::Math;

void Bezier3::addControlPoint(const PointType & point)
{
    m_points.push_back(point);
}

void Bezier3::reset()
{
    m_points.clear();
}

bool Bezier3::empty()
{
    return m_points.empty();
}

Bezier3::PointType Bezier3::operator()(float t)
{
    if (empty())
    {
        throw std::runtime_error("can't calculate bezier curve, no control points");
    }

    CalcType p[3] = {0, 0, 0};
    size_t n = m_points.size() - 1;

    for (size_t i = 0; i <= n; i++)
    {
        CalcType f = bernsteinPolynomial(i, n, t);

        p[0] += m_points[i].getX() * f;
        p[1] += m_points[i].getY() * f;
        p[2] += m_points[i].getZ() * f;
    }

    return PointType(p[0], p[1], p[2]);
}

unsigned Bezier3::getLength()
{
    // according to http://www.gamedev.net/topic/313018-calculating-the-length-of-a-bezier-curve/ there
    // is no way to calculate length of the Bezier curve so we need to "measure" it

    const float step = 0.1f;
    float ret = 0;

    for (float i = step; i < 1.0f + step; i += step)
    {
        PointType p1 = (*this)(i - step);
        PointType p2 = (*this)(i);
        ret += PointType::distance(p1, p2);
    }

    return round(ret);
}

Bezier3::CalcType Bezier3::bernsteinPolynomial(unsigned i, unsigned n, CalcType t)
{
    return (CalcType)(boost::math::binomial_coefficient<CalcType>((unsigned int)n, i)*pow(1.0-t, (double)n - i)*pow(t, i));
}
