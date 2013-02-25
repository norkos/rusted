#include "Cake/Diagnostics/Logger.hpp"

#include "ShipClass.hpp"

using namespace Server::Game;

ShipClass::ShipClass(DataBase::DataBaseNode & node) :
    m_id(node.getValue<unsigned>("id")),
    m_name(node.getValue<std::string>("name")),
    m_speed(node.getValue<unsigned>("speed")),
    m_integrity(node.getValue<unsigned>("integrity")),
    m_mesh(node.getValue<std::string>("mesh")),
    m_capacity(node.getValue<unsigned>("capacity", 0))
{
    LOG_DEBUG << "Ship class loaded, id: " << m_id 
              << ", name: " << m_name
              << ", speed: " << m_speed 
              << ", integrity: " << m_integrity
              << ", mesh: " << m_mesh
              << ", capacity: " << m_capacity;

    try
    {
        LOG_DEBUG << "Loading available actions";

        for (auto & actionNode: node.getFirstChild("actions").getChilds())
        {
            AvailableAction action;
            action.type = actionNode->getValue<unsigned>("type");
            action.parameter = actionNode->getValue<unsigned>("parameter");
            m_availableActions.push_back(action);

            LOG_DEBUG << "  available action: " << action.type << ", parameter: " << action.parameter;
        }
    }
    catch (std::exception & ex)
    {
        LOG_WARN << "Couldn't load available actions, reason: " << ex.what();
    }
}

void ShipClass::applyTo(Common::Game::Object::Ship & ship)
{
    LOG_DEBUG << "Applying class:" << m_id << " to ship:" << ship.getId();

    ship.setSpeed(m_speed);
    ship.setIntegrity(m_integrity);
    ship.setMesh(m_mesh);
    ship.visitCargoHold([&](Common::Game::Object::CargoHold & cargoHold) -> void
    {
        cargoHold.setCapacity(m_capacity);
    });
}

std::vector<AvailableAction> ShipClass::getAvailableActions()
{
    return m_availableActions;
}

unsigned ShipClass::getId()
{
    return m_id;
}

std::string ShipClass::getName()
{
    return m_name;
}

