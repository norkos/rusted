#pragma once

#include "Common/Game/Universe.hpp"

#include "Server/Services/AbstractService.hpp"
#include "Server/Services/StaticObjectsService.hpp"
#include "Server/Game/StaticObjectContainer.hpp"

namespace Server
{
namespace Services
{

class StaticObjectsService : public Server::AbstractService<StaticObjectsService>
{
public:
    StaticObjectsService(Common::Game::Universe & universe, Game::StaticObjectContainer &);
    void handle(const Common::Messages::StaticObjectStatusReq &, Server::Network::IConnection &);
    void handle(const Common::Messages::StaticObjectInfoReq &, Server::Network::IConnection &);
    void handle(const Common::Messages::AbstractMessage &, Network::IConnection &) {}

private:
    Game::StaticObjectContainer & m_staticObjectContainer;
    Common::Game::Universe & m_universe;
};

}
}
