#include "Cake/Diagnostics/Logger.hpp"
#include "FlightTrajectory.hpp"
#include "Common/Math/KinematicParticle.hpp"

using namespace Common::Game::Object;
using namespace Common::Game;

FlightTrajectory::FlightTrajectory() : 
    m_speed(1),
    m_acceleration(100),
    m_cachedOrientation(Common::Math::Quaternion(0, std::make_tuple(0, 0, 1)))
{
}

FlightTrajectory::~FlightTrajectory()
{
}

void FlightTrajectory::fly(Common::Game::Position destination)
{
    TimeValue time = m_time->getCurrentTime();
    float progress = calculateProgress(time);
    auto position = calculatePosition(progress);

    m_description.controlPoints.clear();

    // TODO: is this be faster than derivative calc?
    auto direction = m_cachedOrientation * Common::Math::Point3(0, 0, 1);
    direction.normalize();

    auto p0 = position;
    auto p1 = position + (direction * 1000);
    auto p2 = destination;

    m_description.controlPoints.push_back(p0);
    m_description.controlPoints.push_back(p1);
    m_description.controlPoints.push_back(p2);

    m_description.startTime = time;

    configureBezier();

    LOG_DEBUG << "New trajectory: from " << position << " to " << destination << ", start time: " << time << ", speed: " << m_speed;
}

void FlightTrajectory::stop()
{
    auto time = m_time->getCurrentTime();
    auto progress = calculateProgress(time);

    calculateCachedPositionAndOrientation(progress);

    m_description.controlPoints.clear();
    configureBezier();

    LOG_DEBUG << "Stoped at: " << m_cachedPosition;
}

void FlightTrajectory::setPosition(Common::Game::Position position)
{
    m_cachedPosition = position;

    m_description.controlPoints.clear();
    configureBezier();
}

Common::Game::Position FlightTrajectory::getPosition()
{
    auto progress = calculateProgress(m_time->getCurrentTime());
    calculateCachedPositionAndOrientation(progress);
    revalidateProgress(progress);

    return m_cachedPosition;
}

Common::Game::Position FlightTrajectory::getCourseMarkerPosition()
{
    float progress = calculateProgress(m_time->getCurrentTime()) * 20;
    progress -= floor(progress);
    return calculatePosition(progress);
}

Common::Math::Quaternion FlightTrajectory::getCourseMarkerOrientation()
{
    return Common::Math::Quaternion();
}

Common::Math::Quaternion FlightTrajectory::getOrientation()
{
    auto progress = calculateProgress(m_time->getCurrentTime());
    calculateCachedPositionAndOrientation(progress);
    revalidateProgress(progress);

    return m_cachedOrientation;
}

void FlightTrajectory::setSpeed(unsigned speed)
{
    m_speed = speed;
}

unsigned FlightTrajectory::getSpeed()
{
    return m_speed;
}

unsigned FlightTrajectory::getCurrentSpeed()
{
    if (m_spline->empty())
    {
        return 0;
    }

    unsigned distance = m_spline->getLength();
    TimeValue timeTakenSoFar = m_time->getCurrentTime() - m_description.startTime;
    Common::Math::KinematicParticle kinematicParticle(m_speed, m_acceleration, distance);

    if (kinematicParticle.isInRange(timeTakenSoFar))
    {
        return kinematicParticle.calculateSpeed(timeTakenSoFar);
    }
    else
    {
        return 0;
    }
}

void FlightTrajectory::setAcceleration(unsigned acceleration)
{
    m_acceleration = acceleration;
}

bool FlightTrajectory::isMoving()
{
    auto progress = calculateProgress(m_time->getCurrentTime());
    calculateCachedPositionAndOrientation(progress);
    revalidateProgress(progress);
    
    return !m_spline->empty();
}

FlightTrajectory::Description FlightTrajectory::getDescription()
{
    return m_description;
}

void FlightTrajectory::applyDescription(FlightTrajectory::Description description)
{
    LOG_DEBUG << "Applying precalculated trajectory, description.startTime: "
              << description.startTime
              << ", now: " << m_time->getCurrentTime()
              << ", current position: " << getPosition();

    const unsigned positionMaxCompensationThreshold = 2000;
    const unsigned positionMinCompensationThreshold = 0;
    const TimeValue timeCompensationThreshold(1, 0);

    if (description.controlPoints.size() >= 3)
    {
        auto newStartingPosition = *description.controlPoints.begin();
        auto currentPosition = getPosition();
        auto offset = newStartingPosition - currentPosition;

        // if thresholds are met, add control point with current position at the beginning
        // of the curve
        if (offset.length() < positionMaxCompensationThreshold && offset.length() > positionMinCompensationThreshold)
        {
            LOG_DEBUG << "Position offset: " << offset << " (length: " << offset.length() << ") smaller than threshold, compensating";
            //description.controlPoints.insert(description.controlPoints.begin(), currentPosition);

            LOG_DEBUG << "  " << description.controlPoints[0] << " replacing with " << currentPosition << " at first control point";
            description.controlPoints[0] = currentPosition;
        
            // replace second control point
            // TODO: extract to some method to remove duplication
            auto direction = m_cachedOrientation * Common::Math::Point3(0, 0, 1);
            direction.normalize();

            description.controlPoints[1] = currentPosition + (direction * 1000);
        }

        auto now = m_time->getCurrentTime();
        auto timeOffset = now - description.startTime;
        if (timeOffset < timeCompensationThreshold)
        {
            LOG_DEBUG << "Time offset: " << timeOffset << " smaller than threshold, compensating";
            description.startTime = now;
        }
    }

    m_description = description;
    configureBezier();
}

Position FlightTrajectory::calculatePosition(float progress)
{
    if (m_spline->empty())
    {
        return m_cachedPosition;
    }
    else if (progress >= 1.0)
    {
        return m_spline->value(1.0);
    }
    else
    {
        return m_spline->value(progress);
    }
}

Common::Math::Quaternion FlightTrajectory::calculateOrientation(float progress)
{
    Common::Math::Point3 derivative;

    if (m_spline->empty())
    {
        return m_cachedOrientation;
    }
    else if (progress >= 1.0)
    {
        derivative = m_spline->derivative(1.0);
    }
    else
    {
        derivative = m_spline->derivative(progress);
    }

    return Common::Math::Quaternion(std::make_tuple(derivative.getX(), derivative.getY(), derivative.getZ()));
}

float FlightTrajectory::calculateProgress(TimeValue time)
{
    if (m_spline->empty())
    {
        return 0.0;
    }

    unsigned distance = m_spline->getLength();
    TimeValue timeTakenSoFar = time - m_description.startTime;
    Common::Math::KinematicParticle kinematicParticle(m_speed, m_acceleration, distance);

    if (kinematicParticle.isInRange(timeTakenSoFar))
    {
        return kinematicParticle.calculateDistance(timeTakenSoFar) / distance;
    }
    else
    {
        return 1.1; // invalid value
    }
}

void FlightTrajectory::configureBezier()
{
    m_spline->reset();
    
    LOG_DEBUG << "Configuring bezier:";

    for (const auto & p : m_description.controlPoints)
    {
        LOG_DEBUG << "  " << p;
        m_spline->addControlPoint(p);
    }
}

void FlightTrajectory::revalidateProgress(float progress)
{
    if (progress > 1.0)
    {
        m_description.controlPoints.clear();
        configureBezier();
    }
}

void FlightTrajectory::calculateCachedPositionAndOrientation(float progress)
{
    m_cachedPosition = calculatePosition(progress);
    m_cachedOrientation = calculateOrientation(progress);
}

