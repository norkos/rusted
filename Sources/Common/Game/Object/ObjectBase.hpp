#pragma once

#include <typeinfo>
#include <boost/signals2.hpp>

#include "Common/Math/Quaternion.hpp"
#include "Cake/DependencyInjection/Inject.hpp"
#include "Common/Game/Position.hpp"
#include "CargoHold.hpp"
#include "Common/Game/Utilities/Id.hpp"

namespace Common
{
namespace Game
{
namespace Object
{

class ObjectBase
{
public:
    typedef Common::Game::Utilities::Id<ObjectBase> Id;
    typedef Common::Game::Utilities::StrictId<ObjectBase> StrictId;

    typedef boost::signals2::signal<void(const CargoHold &)> CargoHoldSignal;

    ObjectBase();

    virtual unsigned getId();
    virtual void setId(unsigned id);

    virtual void setModel(std::string mesh);
    virtual std::string getModel();

    virtual Position getPosition() = 0;
    virtual void setPosition(const Position &) = 0;
    virtual bool isMoving() = 0;

    virtual unsigned getIntegrity();
    virtual void setIntegrity(unsigned integrity);

    virtual Common::Math::Quaternion getOrientation();
    virtual void setOrientation(const Common::Math::Quaternion &);

    void writeCargoHold(std::function<void(CargoHold &)>);
    void readCargoHold(std::function<void(const CargoHold &)>) const;

    boost::signals2::connection addCargoHoldSlot(CargoHoldSignal::slot_type);

    template <class ObjectType> bool is()
    {
        return dynamic_cast<ObjectType*>(this) != nullptr;
    }

    virtual ~ObjectBase();

private:
    unsigned m_id;
    unsigned m_integrity;
    std::string m_model;
    CargoHold m_cargoHold;
    CargoHoldSignal m_cargoHoldSignal;
};

inline std::ostream & operator<<(std::ostream & os, Common::Game::Object::ObjectBase & object)
{
    os << CAKE_DEPENDENCY_INJECTION_TYPENAME(object) << " " << object.getPosition();
    return os;
}

}
}
}
