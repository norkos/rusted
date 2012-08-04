#include "ActionBuilder.hpp"
#include "Attack.hpp"

using namespace Server::Game::Actions;

boost::shared_ptr<IAction> ActionBuilder::build(
        Server::Network::IConnection & connection,
        Server::Game::IPlayerContainer & playerContainer,
        Common::Game::Universe & universe,
        unsigned id, 
        Common::Game::Object::Ship & focusedShip,
        Common::Game::Object::ObjectBase * selectedObject)
{
    boost::shared_ptr<IAction> ret;

    switch (id)
    {
    case 1:
        assert(selectedObject);
        ret = boost::shared_ptr<IAction>(new Attack(playerContainer, focusedShip, *selectedObject));
        break;

    default:
        LOG_WARN << "Unknown action: " << id;
    }

    if (ret)
    {
        LOG_DEBUG << "Constructed action: " << id << "/" << CAKE_DEPENDENCY_INJECTION_TYPENAME(*ret);
    }

    return ret;
}

