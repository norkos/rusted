#include <functional>

#include "UniverseDataBaseFacade.hpp"
#include "Common/Game/Object/Ship.hpp"
#include "Common/Game/Object/Asteroid.hpp"
#include "Server/Game/Actions/Attack.hpp"

using namespace Server::Game;

UniverseDataBaseFacade::UniverseDataBaseFacade(IShipClassContainer & shipClassContainer) : 
    m_shipClassContainer(shipClassContainer)
{
    loadObjects();
}

void UniverseDataBaseFacade::loadObjects()
{
    LOG_INFO << "Loading universe state from db";

    int objectCount;
    m_sociSession->once << "SELECT COUNT(*) FROM objects", soci::into(objectCount);
    LOG_INFO << "  " << objectCount << " objects";

    soci::rowset<soci::row> objects = (m_sociSession->prepare << "SELECT * FROM objects");

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        loadObjectFromDb(*it);
    }
}

void UniverseDataBaseFacade::loadObjectFromDb(const soci::row & row)
{
    using namespace std::placeholders;

    std::string type = row.get<std::string>("type");
    unsigned id = row.get<int>("id");

    if (m_universe->has(id))
    {
        LOG_DEBUG << "Object id: " << id << " is already in the universe, doing nothing";
        return;
    }

    LOG_DEBUG << "Loading object id: " << id;

    if (type == "Ship")
    {
        std::shared_ptr<Common::Game::Object::ObjectBase> object = std::make_shared<Common::Game::Object::Ship>();
        Common::Game::Object::Ship & ship = dynamic_cast<Common::Game::Object::Ship&>(*object);

        object->setId(id);
        ship.setOwnerId(row.get<int>("owner"));
        object->setPosition(extractPosition(row));

        unsigned shipClassId = row.get<int>("class");
        auto & shipClass = m_shipClassContainer.getById(shipClassId);
        shipClass.applyTo(ship);
        ship.setClass(shipClassId);
        ship.writeCargoHold([&](Common::Game::Object::CargoHold & cargoHold)
        {
            fillCargoHold(row, cargoHold);
        });

        object->addCargoHoldSlot(boost::bind(&UniverseDataBaseFacade::saveCargoHold, this, object->getId(), boost::arg<1>()));
        m_universe->add(object);
    }
    else if (type == "Asteroid")
    {
        std::shared_ptr<Common::Game::Object::ObjectBase> object(new Common::Game::Object::Asteroid);

        object->setId(id);
        object->setModel(row.get<std::string>("model"));
        object->setPosition(extractPosition(row));
        object->setIntegrity(row.get<int>("integrity"));

        // set unlimited capacity for asteroids
        object->writeCargoHold([&](Common::Game::Object::CargoHold & cargoHold)
        {
            fillCargoHold(row, cargoHold);
            cargoHold.setCapacity(99999999);
        });

        m_universe->add(object);
    }
    else
    {
        std::stringstream ss;
        ss << "invalid object type: " << type;
        throw std::runtime_error(ss.str());
    }
}

std::shared_ptr<Common::Game::Object::ObjectBase> UniverseDataBaseFacade::createShip(unsigned shipClassId, unsigned ownerId)
{
    LOG_DEBUG << "Creating ship with shipClass:" << shipClassId << ", owner:" << ownerId;

    // INSERT INTO objects VALUES(1,   "Ship",     1,     NULL,             1,    2000, 1,     1,    100,      0,     0);

    unsigned id = preInsertObjectToDb(shipClassId, ownerId);

    LOG_DEBUG << "  id from the database: " << id;

    auto & shipClass = m_shipClassContainer.getById(shipClassId);

    std::shared_ptr<Common::Game::Object::ObjectBase> object(new Common::Game::Object::Ship);
    auto & ship = dynamic_cast<Common::Game::Object::Ship&>(*object);

    object->setId(id);
    ship.setOwnerId(ownerId);
    shipClass.applyTo(ship);
    ship.setClass(shipClassId);

    m_universe->add(object);

    return object;
}

Common::Game::Position UniverseDataBaseFacade::extractPosition(const soci::row & row)
{
    Common::Game::Position position;
    position.setX(row.get<int>("x"));
    position.setY(row.get<int>("y"));
    position.setZ(row.get<int>("z"));
    return position;
}

void UniverseDataBaseFacade::fillCargoHold(const soci::row & row, Common::Game::Object::CargoHold & cargoHold)
{
    LOG_DEBUG << "Filling cargoHold";

    try
    {
        cargoHold.setCarbon(row.get<int>("carbon"));
        cargoHold.setHelium(row.get<int>("helium"));
    }
    catch (std::exception & ex)
    {
        LOG_WARN << "Error filling cargohold, reason: " << ex.what();
    }
}

void UniverseDataBaseFacade::saveCargoHold(Common::Game::Object::ObjectBase::Id id, const Common::Game::Object::CargoHold & cargoHold)
{
    LOG_DEBUG << "Saving CargoHold for object: " << id;

    int carbon = cargoHold.getCarbon();
    int helium = cargoHold.getHelium();

    m_sociSession->once <<
        "UPDATE objects SET carbon=:carbon, helium=:helium WHERE id=:id",
        soci::use(carbon),
        soci::use(helium),
        soci::use(id.get());

    LOG_DEBUG << "done.";
}

unsigned UniverseDataBaseFacade::preInsertObjectToDb(unsigned shipClassId, unsigned ownerId)
{
    // INSERT INTO objects VALUES(1,   "Ship",     1,     NULL,             1,    2000, 1,     1,    100,      0,     0);

    std::string type = "Ship";
    unsigned id = 0;

    m_sociSession->begin();

    m_sociSession->once <<
        "INSERT INTO objects(type, class, owner, x, y, z) VALUES(:type, :class, :owner, 0, 0, 0)",
        soci::use(type),
        soci::use(shipClassId),
        soci::use(ownerId);

    m_sociSession->once <<
        "SELECT id FROM objects ORDER BY id DESC LIMIT 1",
        soci::into(id);

    m_sociSession->commit();

    return id;
}

