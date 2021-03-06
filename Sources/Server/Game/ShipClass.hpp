#pragma once

#include <soci.h>

#include "Cake/DependencyInjection/Inject.hpp"
#include "Common/Game/Object/Ship.hpp"
#include "IShipClass.hpp"

namespace Server
{
namespace Game
{

class ShipClass : public IShipClass
{
public:
    ShipClass(const soci::row &);

    void applyTo(Common::Game::Object::Ship &);
    std::vector<AvailableAction> getAvailableActions();
    unsigned getId();
    std::string getName();
    unsigned getRequiredCarbon();
    unsigned getRequiredHelium();

private:
    unsigned m_id;
    std::string m_name;
    unsigned m_speed;
    unsigned m_integrity;
    std::string m_model;
    unsigned m_capacity;
    unsigned m_requiredCarbon;
    unsigned m_requiredHelium;
    std::vector<AvailableAction> m_availableActions;

    Cake::DependencyInjection::Inject<soci::session> m_sociSession;
};

}
}

