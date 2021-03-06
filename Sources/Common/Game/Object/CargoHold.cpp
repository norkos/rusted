#include <stdexcept>

#include "Cake/Diagnostics/Logger.hpp"
#include "CargoHold.hpp"

using namespace Common::Game::Object;

CargoHold::CargoHold() : m_capacity(0), m_helium(0), m_carbon(0)
{
}

void CargoHold::setCapacity(unsigned capacity)
{
    m_capacity = capacity;
}

unsigned CargoHold::getCapacity() const
{
    return m_capacity;
}

unsigned CargoHold::getUsedCapacity() const
{
    return m_carbon + m_helium;
}

unsigned CargoHold::getHelium() const
{
    return m_helium;
}

void CargoHold::setHelium(unsigned value)
{
    m_helium = value;
}

void CargoHold::changeHelium(int delta)
{
    if (getUsedCapacity() + delta > getCapacity())
    {
        LOG_WARN << "Capacity overloaded, used:" << getUsedCapacity() << ", total:" << getCapacity();
        throw std::runtime_error("capacity overloaded");
    }
    m_helium += delta;
}

unsigned CargoHold::getCarbon() const
{
    return m_carbon;
}

void CargoHold::setCarbon(unsigned value)
{
    m_carbon = value;
}

void CargoHold::changeCarbon(int delta)
{
    if (getUsedCapacity() + delta > getCapacity())
    {
        LOG_WARN << "Capacity overloaded, used:" << getUsedCapacity() << ", total:" << getCapacity();
        throw std::runtime_error("capacity overloaded");
    }
    m_carbon += delta;
}

