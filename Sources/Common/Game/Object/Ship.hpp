#pragma once

#include <boost/utility.hpp>

#include "Cake/DependencyInjection/Inject.hpp"

#include "Common/Math/Quaternion.hpp"
#include "Common/Game/Object/ObjectBase.hpp"
#include "Common/Game/Object/OwnedObjectBase.hpp"
#include "Common/Game/IRustedTime.hpp"
#include "IFlightTrajectory.hpp"

namespace Common
{
namespace Game
{
namespace Object
{

class Ship : public ObjectBase, public OwnedObjectBase, public boost::noncopyable
{
public:
    Ship();
    virtual ~Ship();

    virtual Position getPosition();
    void setPosition(const Position &);
    bool isMoving();
    Position getDestination();
    virtual void setCourse(Position course);
    virtual void setMaxSpeed(unsigned speed);
    unsigned getMaxSpeed();
    unsigned getCurrentSpeed();
    void setIntegrity(unsigned); //override;
    Common::Math::Quaternion getOrientation();
    void setOrientation(const Common::Math::Quaternion &);
    bool isWrecked();

    virtual void setClass(unsigned);
    virtual unsigned getClass();

    virtual IFlightTrajectory::Description getTrajectoryDescription();
    void applyTrajectoryDescription(IFlightTrajectory::Description);

private:
    Cake::DependencyInjection::Inject<IRustedTime> m_time;
    Cake::DependencyInjection::Inject<IFlightTrajectory> m_trajectory;

    unsigned m_class;
};

}
}
}

