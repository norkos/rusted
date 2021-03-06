#pragma once

#include "Common/Game/TimeValue.hpp"

namespace Common
{
namespace Math
{

/**
 * KinematicParticle represents particle movement in 1 dimension. It takes
 * under consideration maximum speed, acceleration and deceleration.
 *
 * To take into account deceleration, this object needs to know what is
 * the target distance for the particle.
 */
class KinematicParticle
{
public:
    KinematicParticle(float maxSpeed, float acceleration, float targetDistance, float initialSpeed = 0);

    float calculateDistance(Common::Game::TimeValue deltaTime) const;
    float calculateSpeed(Common::Game::TimeValue deltaTime) const;
    bool isInRange(Common::Game::TimeValue deltaTime) const;
    Common::Game::TimeValue getEta(Common::Game::TimeValue currentTime) const;

private:
    float getTimeInSeconds(Common::Game::TimeValue time) const;
    float calculateTmax() const;
    float calculateRoadDuringLinearAcceleration(float a, float t, float initialSpeed = 0) const;

    float m_maxSpeed;
    float m_acceleration;
    float m_targetDistance;
    float m_initialSpeed;

    // precalculated stuff
    float m_t1;
    bool m_willReachMaxSpeed;
    float m_Tmax;
    float m_t2;
};

}
}

