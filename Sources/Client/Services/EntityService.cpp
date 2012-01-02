#include "Common/Logger/Logger.hpp"
#include "Common/Game/Object/Ship.hpp"
#include "Client/Services/EntityService.hpp"

using namespace Client::Services;

EntityService::EntityService(Network::Connection & connection, 
                             Game::PlayerInfo & playerInfo,
                             Common::Game::Universe & universe) :
    m_playerInfo(playerInfo),
    m_connection(connection),
    m_universe(universe)
{
}

void EntityService::fetchMyEntitiesInfo(MyEntitiesFetchedCallback callback)
{
    m_myEntitiesFetchedCallback = callback;
    Common::Messages::PlayerEntitiesStatusReq entitiesStatusReq;
    m_connection.send(entitiesStatusReq);
}

void EntityService::setCurrentEntity(Common::Game::Object::Ship & ship)
{
    m_currentShip = &ship;
}

Common::Game::Object::Ship & EntityService::getCurrentEntity()
{
    assert(m_currentShip);
    return **m_currentShip;
}

void EntityService::setCourse(Common::Game::Entity::Position course)
{
    assert(m_currentShip);

    (*m_currentShip)->setCourse(course);
    Common::Messages::EntityChangeCourseReq req;
    req.entityId = (*m_currentShip)->getId();
    req.courseX = course.getX();
    req.courseY = course.getY();
    req.courseZ = course.getZ();
    m_connection.send(req);
}

void EntityService::handle(const Common::Messages::PlayerEntitiesStatusResp & entitiesStatusResp)
{
    LOG_INFO << "Own units info received\n";

    BOOST_FOREACH(boost::tuple<int> entity, entitiesStatusResp.entities)
    {
       LOG_INFO << "  Entity (id: " << entity.get<0>() << ")\n";

       Common::Messages::EntityGetInfoReq entityGetInfoReq;
       entityGetInfoReq.id = entity.get<0>();
       m_connection.send(entityGetInfoReq);
       m_myEntities.insert(entity.get<0>());
    }
}

void EntityService::handle(const Common::Messages::EntityGetInfoResp & entityGetInfoResp)
{
    LOG_INFO << "Got entity info (id: " << entityGetInfoResp.id << ")\n";

    boost::shared_ptr<Common::Game::Object::ObjectBase> object(new Common::Game::Object::Ship);
    Common::Game::Object::Ship & ship = dynamic_cast<Common::Game::Object::Ship&>(*object);
    ship.setId(entityGetInfoResp.id);
    ship.setOwnerId(entityGetInfoResp.player_id);
    ship.setPosition(Common::Game::Position(entityGetInfoResp.x, entityGetInfoResp.y, entityGetInfoResp.z));

    m_universe.add(object);

    // are we waiting for this entity info?
    std::set<int>::iterator it = m_myEntities.find(entityGetInfoResp.id);
    if (it != m_myEntities.end())
    {
       LOG_INFO << "Entity is from player's entities list and we were expected this info\n";
       m_myEntities.erase(it); 

       if (m_myEntities.empty())
       {
          LOG_INFO << "And this was the last one\n";
          m_myEntitiesFetchedCallback();
       }
    }
}
