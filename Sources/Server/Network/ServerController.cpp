#include <stdexcept>
#include <signal.h>

#include "Cake/Diagnostics/Logger.hpp"
#include "Cake/Networking/Acceptor.hpp"
#include "Cake/Networking/MainLoop.hpp"

#include "Server/Network/ServerController.hpp"

using namespace Server::Network;

ServerController::ServerController() :
    m_serviceDeployment(*m_cfg, m_playerContainer)
{
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(sigact));

    sigact.sa_handler = handleSignal;
    ::sigaction(15, &sigact, 0);
}

int ServerController::start()
{
    int tcpPort = m_cfg->getValue<int>("network.port");
    std::string administrationSocketPath = m_cfg->getValue<std::string>("network.administration_socket_path");

    LOG_INFO << "Setting up player socket on TCP:" << tcpPort;

    using namespace Cake::Networking;

    auto server = Acceptor::createTcpServer(tcpPort, [this](std::shared_ptr<Socket> socket)
    {
        LOG_DEBUG << "New client connection established";

        std::shared_ptr<ConnectionContext> connectionContext(new ConnectionContext(socket, m_serviceDeployment));

        m_connections.push_back(connectionContext);
        m_playerContainer.add(connectionContext->getConnection());
        m_serviceDeployment.deployNewConnection(connectionContext->getConnection());
        connectionContext->getThread().start();
    });

    LOG_INFO << "Setting up administrative socket on UNIX:" << administrationSocketPath;

    auto administrationServer = Acceptor::createUnixServer(administrationSocketPath, [this](std::shared_ptr<Socket> socket)
    {
        LOG_INFO << "New administration connection established";

        std::shared_ptr<ConnectionContext> connectionContext(new ConnectionContext(socket, m_serviceDeployment));

        m_administrationConnections.push_back(connectionContext);
        m_serviceDeployment.deployAdministrationConnection(connectionContext->getConnection());
        connectionContext->getThread().start();
    });

    try
    {
        MainLoop loop({server, administrationServer});
        loop.run();
    }
    catch (std::exception & ex)
    {
        LOG_WARN << "Server is shutting down, reason: " << ex.what();
    }

    LOG_INFO << "Server is done";

    return 0;
}

void ServerController::gc()
{
    // TODO: make weak_ptr of a connection and put it in playerContainer

    auto it = m_connections.begin();
    while (it != m_connections.end())
    {
        if (not (*it)->getThread().isRunning())
        {
            LOG_DEBUG << "Collecting innactive connection: " << (*it);

            m_playerContainer.remove((*it)->getConnection());
            it = m_connections.erase(it);
        }
        else
        {
            ++it;
        }
    }

    it = m_administrationConnections.begin();
    while (it != m_administrationConnections.end())
    {
        if (not (*it)->getThread().isRunning())
        {
            LOG_DEBUG << "Collecting innactive administration connection: " << (*it);
            it = m_administrationConnections.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ServerController::handleSignal(int signum)
{
	if (signum == 15)
	{
		LOG_WARN << "SIGINT catched";
	}
}

