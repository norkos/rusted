#include <stdexcept>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Socket.hpp"
#include "System/AtomicSyscall.hpp"
#include "DnsResolver.hpp"
#include "Detail/SockFdGuard.hpp"
#include "Diagnostics/Throw.hpp"

using namespace Cake::Networking;

Socket::Socket(int sockFd) : m_sockFd(sockFd)
{
}

Socket::~Socket()
{
    ::close(m_sockFd);
}

std::shared_ptr<Socket> Socket::connectToUnixSocket(const std::string & path)
{
    Detail::SockFdGuard sockFd;
    ATOMIC_SYSCALL(::socket(AF_UNIX, SOCK_STREAM, 0), sockFd, == -1);

    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path.c_str());

    int result;
    ATOMIC_SYSCALL(::connect(*sockFd, (sockaddr*)&addr, strlen(addr.sun_path) + sizeof(addr.sun_family)), result, == -1);

    return std::shared_ptr<Socket>(new Socket(sockFd.release()));
}

std::shared_ptr<Socket> Socket::connectToTcpSocket(const std::string & address, int port)
{
    Detail::SockFdGuard sockFd;
    ATOMIC_SYSCALL(::socket(PF_INET, SOCK_STREAM, 0), sockFd, == -1);

    DnsResolver resolver;
    sockaddr_in addr = resolver.resolve(address, port);

    int result;
    ATOMIC_SYSCALL(::connect(*sockFd, (sockaddr*)&addr, sizeof(sockaddr_in)), result, == -1);

    return std::shared_ptr<Socket>(new Socket(sockFd.release()));
}

void Socket::send(const void * buf, size_t size)
{
    int ret = ::send(m_sockFd, buf, size, MSG_NOSIGNAL);

    if (ret == -1)
    {
        std::stringstream ss;
        ss << "send: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }
}

void Socket::receive(void * buf, size_t size)
{
    char * charBuf = static_cast<char *>(buf);

    while (size)
    {
        int ret = ::recv(m_sockFd, charBuf, size, 0);

        if (ret == 0)
        {
            throw std::runtime_error("connection closed by remote during recv");
        }
        else if (ret == -1)
        {
            THROW(std::runtime_error) << "recv returned error: " << strerror(errno);
        }

        charBuf += ret;
        size -= ret;
    }
}

Socket & Socket::operator>>(unsigned & value)
{
    receive(&value, sizeof(value));
    return *this;
}

Socket & Socket::operator<<(unsigned value)
{
    send(&value, sizeof(value));
    return *this;
}

Socket & Socket::operator>>(std::string & str)
{
    // TODO: we can operate on the string directly
    str.clear();

    size_t size;
    receive(&size, sizeof(size));

    if (size > 0)
    {
        if (size > 1024 * 1024) // 1MB
        {
            throw std::runtime_error("size of string exceeded 1MB, can't receive");
        }

        std::vector<char> buf(size + 1);
        buf.back() = 0;
        receive(&buf[0], size);
        str = &buf[0];
    }

    return *this;
}

Socket & Socket::operator<<(const std::string & str)
{
    size_t size = str.length();
    send(&size, sizeof(size));

    if (size > 0)
    {
        send(str.c_str(), size);
    }

    return *this;
}

Socket & Socket::operator>>(StringMap & map)
{
    map.clear();

    size_t size;
    receive(&size, sizeof(size));

    for (size_t i = 0; i < size; i++)
    {
        std::string key;
        std::string val;
        *this >> key >> val;
        map.insert(std::make_pair(key, val));
    }

    return *this;
}

Socket & Socket::operator<<(const StringMap & map)
{
    size_t size = map.size();
    send(&size, sizeof(size));

    if (size > 0)
    {
        for (StringMap::const_iterator it = map.begin(); it != map.end(); it++)
        {
            *this << it->first << it->second;
        }
    }

    return *this;
}

