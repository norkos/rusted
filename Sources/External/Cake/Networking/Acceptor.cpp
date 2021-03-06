#include <stdexcept>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/un.h>
#endif

#include <errno.h>
#include <sstream>
#include <string.h>
#include <cstdio>

#include "Utils/BuildString.hpp"
#include "Detail/Error.hpp"
#include "Acceptor.hpp"

using namespace Cake::Networking;

Acceptor::Acceptor(int sockFd, ClientConnected clientConnected) :
    m_sockFd(sockFd),
    m_clientConnected(clientConnected)
{
}

auto Acceptor::createTcpServer(unsigned port,
                               ClientConnected clientConnected) -> std::shared_ptr<Acceptor>
{
    int sockFd = createDescriptor(PF_INET);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(sockFd, (sockaddr*)&addr, sizeof(addr)) == -1)
    {
        throw std::runtime_error(BUILD_STRING << "can't bind socket, reason: " << Detail::Error::lastError());
    }

    listen(sockFd);

    // can't use make_shared due to private constructor
    return std::shared_ptr<Acceptor>(new Acceptor(sockFd, clientConnected));
}

auto Acceptor::createUnixServer(const std::string & path,
                                ClientConnected clientConnected) -> std::shared_ptr<Acceptor>
{
#ifdef _WIN32
    throw std::runtime_error("WIN32 doesn't support UNIX sockets");
#else
    int sockFd = createDescriptor(PF_UNIX);

    sockaddr_un local_addr;
    local_addr.sun_family = PF_UNIX;
    ::strcpy(local_addr.sun_path, path.c_str());
    ::remove(local_addr.sun_path);

    int ret = ::bind(sockFd,
        (sockaddr *)(&local_addr),
        sizeof(local_addr.sun_family) + strlen(local_addr.sun_path));

    if (ret == -1)
    {
        throw std::runtime_error(BUILD_STRING << "can't bind socket, reason: " << Detail::Error::lastError());
    }

    listen(sockFd);

    // can't use make_shared due to private constructor
    return std::shared_ptr<Acceptor>(new Acceptor(sockFd, clientConnected));
#endif
}

auto Acceptor::accept() -> std::shared_ptr<Socket>
{
    int sockFd = ::accept(m_sockFd, NULL, NULL);

    if (sockFd == -1)
    {
        throw std::runtime_error(BUILD_STRING << "can't accept new connection, reason: " << Detail::Error::lastError());
    }

    return std::shared_ptr<Socket>(new Socket(sockFd));
}

void Acceptor::act()
{
    auto socket = accept();

    if (m_clientConnected)
    {
        m_clientConnected(socket);
    }
}

auto Acceptor::nativeHandle() -> int const
{
    return m_sockFd;
}

int Acceptor::createDescriptor(int family)
{
    int descriptor = socket(family, SOCK_STREAM, 0);

    if (descriptor == -1)
    {
        throw std::runtime_error("can't create socket");
    }

    return descriptor;
}

void Acceptor::listen(int descriptor)
{
    int ret = ::listen(descriptor, 5);

    if (ret == -1)
    {
        throw std::runtime_error("can't listen to the socket");
    }
}
