#include "Utils.hpp"

#include "Common/Game/Object/Asteroid.hpp"

using namespace Server::Services;

void Utils::sendObjectInfo(unsigned id, Common::Game::Universe & universe, Network::IConnection & connection)
{
    using namespace Common::Game::Object;

    ObjectBase & object = universe.getById<ObjectBase>(id);
    sendObjectInfo(object, connection);
}

void Utils::sendObjectInfo(Common::Game::Object::ObjectBase & object, Network::IConnection & connection)
{
    using namespace Common::Game::Object;

    LOG_DEBUG << "Getting info about object id: " << object.getId() << ", type: " << TYPENAME(object);

    if (object.is<Ship>())
    {
        auto & ship = dynamic_cast<Ship&>(object);
        sendShipInfo(ship, connection);
        sendShipCourseInfo(ship, connection);
        sendObjectCargoInfo(ship, connection);
    }
    else if (object.is<Asteroid>())
    {
        Common::Messages::AsteroidInfo asteroidInfo;

        auto & asteroid = dynamic_cast<Common::Game::Object::Asteroid&>(object);

        Common::Game::Position position = object.getPosition();
        asteroidInfo.objectId = object.getId();
        asteroidInfo.model = object.getModel();
        asteroidInfo.x = position.getX();
        asteroidInfo.y = position.getY();
        asteroidInfo.z = position.getZ();

        connection.send(asteroidInfo);

        sendObjectCargoInfo(asteroid, connection);
    }
}

void Utils::sendShipCourseInfo(Common::Game::Object::Ship & ship, Network::IConnection & connection)
{
    auto description = ship.getTrajectoryDescription();

    Common::Messages::ShipCourseInfo shipCourseInfo;
    shipCourseInfo.objectId = ship.getId();

    for (const auto & point : description.controlPoints)
    {
        Common::Messages::Position p;
        p.x = point.getX();
        p.y = point.getY();
        p.z = point.getZ();
        shipCourseInfo.controlPoints.push_back(p);
    }

    shipCourseInfo.startTimeSeconds = description.startTime.getSeconds();
    shipCourseInfo.startTimeMiliseconds = description.startTime.getMiliseconds();
    shipCourseInfo.initialSpeed = description.initialSpeed;

    connection.send(shipCourseInfo);
}

void Utils::sendShipInfo(Common::Game::Object::Ship & ship, Network::IConnection & connection)
{
    Common::Messages::ShipInfo shipInfo;

    Common::Game::Position position = ship.getPosition();
    shipInfo.id = ship.getId();
    shipInfo.player_id = ship.getOwnerId();
    shipInfo.model = ship.getModel();
    shipInfo.x = position.getX();
    shipInfo.y = position.getY();
    shipInfo.z = position.getZ();
    shipInfo.integrity = ship.getIntegrity();
    shipInfo.speed = ship.getMaxSpeed();

    auto orientation = ship.getOrientation();
    shipInfo.orientationW = orientation.getW();
    shipInfo.orientationX = orientation.getX();
    shipInfo.orientationY = orientation.getY();
    shipInfo.orientationZ = orientation.getZ();

    connection.send(shipInfo);
}

void Utils::sendObjectCargoInfo(Common::Game::Object::ObjectBase & object, Network::IConnection & connection)
{
    Common::Messages::ObjectCargoInfo objectCargoInfo;
    objectCargoInfo.id = object.getId();

    object.readCargoHold([&objectCargoInfo](const Common::Game::Object::CargoHold & cargoHold) -> void
    {
        objectCargoInfo.capacity = cargoHold.getCapacity();
        objectCargoInfo.carbon = cargoHold.getCarbon();
        objectCargoInfo.helium = cargoHold.getHelium();
    });

    connection.send(objectCargoInfo);
}

void Utils::sendObjectIntegrity(Common::Game::Object::ObjectBase & object, Network::IConnection & connection)
{
    Common::Messages::ObjectIntegrity objectIntegrity;
    objectIntegrity.id = object.getId();
    objectIntegrity.integrity = object.getIntegrity();

    connection.send(objectIntegrity);
}

void Utils::sendVisibleObjects(Common::Game::Universe & universe, Network::IConnection & connection)
{
    Common::Messages::VisibleObjects visibleObjects;

    LOG_DEBUG << "Filling visible objects";

    auto objects = universe.getAll();
    for (auto object: objects)
    {
        LOG_DEBUG << "  id: " << object->getId() << ", type: " << TYPENAME(*object);

        Common::Messages::ObjectId objectId;
        objectId.id = object->getId();

        visibleObjects.objects.push_back(objectId);
    }

    connection.send(visibleObjects);
}

