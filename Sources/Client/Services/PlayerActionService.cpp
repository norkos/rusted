#include "Cake/Diagnostics/Logger.hpp"

#include "Common/Game/Object/Ship.hpp"
#include "Client/Services/PlayerActionService.hpp"

using namespace Client::Services;

PlayerActionService::PlayerActionService(Network::IConnection & connection, 
                             Game::PlayerInfo & playerInfo,
                             Common::Game::Universe & universe) :
    m_playerInfo(playerInfo),
    m_connection(connection),
    m_universe(universe)
{
}

void PlayerActionService::focusObject(Common::Game::Object::ObjectBase & ship)
{
    m_focusedObject = &ship;
}

Common::Game::Object::ObjectBase & PlayerActionService::getFocusedObject()
{
    assert(m_focusedObject);

    return **m_focusedObject;
}

void PlayerActionService::setFocusedObjectCourse(Common::Game::Position course)
{
    assert(m_focusedObject);

    dynamic_cast<Common::Game::Object::Ship&>(**m_focusedObject).setCourse(course);

    Common::Messages::EntityChangeCourseReq req;

    req.entityId = (*m_focusedObject)->getId();
    req.courseX = course.getX();
    req.courseY = course.getY();
    req.courseZ = course.getZ();

    m_connection.send(req);
}

