#pragma once

#include "Common/Configuration/Configuration.hpp"
#include "Common/Game/RustedTime.hpp"
#include "Common/DataBase/DataBaseFactory.hpp"
#include "Server/Network/IConnection.hpp"

#include "Server/Game/StaticObjectContainer.hpp"

#include "Server/Services/IServiceDeployment.hpp"
#include "Server/Services/ServerInfoService.hpp"
#include "Server/Services/RustedTimeService.hpp"
#include "Server/Services/AuthorizationService.hpp"
#include "Server/Services/PlayerService.hpp"
#include "Server/Services/EntityService.hpp"
#include "Server/Services/StaticObjectsService.hpp"

#include "Common/Game/Universe.hpp"

namespace Server
{
namespace Services
{

class ServiceDeployment : public IServiceDeployment
{
public:
    ServiceDeployment(Common::Configuration::Configuration &);
    void deployNewConnection(Server::Network::IConnection &);
    void deployAuthorizedConnection(Server::Network::IConnection &);

private:
    Common::Game::RustedTime m_time;
    Common::DataBase::DataBaseFactory m_dbFactory;
    Common::DataBase::DataBase & m_db;
    Common::Game::Universe m_universe;
    Common::Game::EntityContainer m_entities;
    Game::PlayerContainer m_players;
    Game::StaticObjectContainer m_staticObjectContainer;

    Server::Services::ServerInfoService m_serverInfoService;
    Server::Services::RustedTimeService m_rustedTimeService;
    Server::Services::AuthorizationService m_authorizationService;
    Services::PlayerService m_playerService;
    Services::EntityService m_entityService;
    Services::StaticObjectsService m_staticObjectsService;
};

}
}
