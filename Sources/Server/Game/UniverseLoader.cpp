#include "UniverseLoader.hpp"

using namespace Server::Game;

void UniverseLoader::load(Common::Game::Universe & universe, Server::DataBase::DataBase & db)
{
    LOG_INFO << "Loading universe state from db";

    auto & objects = db.getRoot().getFirstChild("objects");

    for (auto it = objects.getChilds().begin(); it != objects.getChilds().end(); it++)
    {
        Server::DataBase::DataBaseNode & node = **it;
        universe.add(m_objectFactory->create(node));
    }
}

void UniverseLoader::save(Common::Game::Universe & universe, Server::DataBase::DataBase & db)
{
    LOG_INFO << "Saving universe state from db";
    LOG_ERR << "Not implemented";
}
