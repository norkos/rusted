#pragma once

#include <unistd.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Connection.hpp"

namespace SCT
{

class Component
{
public:
	Component();
    Component(const std::string & database);
	~Component();
    void setConfigValue(const std::string & name, const std::string & value);
    void start();
	boost::shared_ptr<Connection> createConnection();

private:
	pid_t m_pid;
	int m_port;
    std::map<std::string, std::string> m_cmdLineOptions;
};

}

