#include <stdexcept>
#include <sstream>

#include "Cake/Diagnostics/Logger.hpp"
#include "ShipClassContainer.hpp"

using namespace Server::Game;

ShipClassContainer::ShipClassContainer()
{
    loadFromDataBase();
}

ShipClassContainer::~ShipClassContainer()
{
}

Server::Game::IShipClass & ShipClassContainer::getById(unsigned id) const
{
    auto it = m_shipClassMap.find(id);
    if (it != m_shipClassMap.end())
    {
        return *it->second;
    }
    else
    {
        std::stringstream ss;
        ss << "no ship class with id:" << id;
        throw std::runtime_error(ss.str());
    }
}

void ShipClassContainer::loadFromDataBase()
{
    LOG_INFO << "Loading ship classes from db";

    soci::rowset<soci::row> classes = (m_sociSession->prepare << "SELECT * FROM ship_classes");

    for (auto it = classes.begin(); it != classes.end(); it++)
    {
        std::shared_ptr<ShipClass> shipClass(new ShipClass(*it));
        auto ret = m_shipClassMap.insert(std::make_pair(shipClass->getId(), shipClass));
        if (!ret.second)
        {
            throw std::runtime_error("such ShipClass already exists");
        }
    }
}

