#include <gtest/gtest.h>

#include "Common/Game/Object/UnitTests/ShipMock.hpp"
#include "Common/Game/UnitTests/RustedTimeStub.hpp"
#include "Server/Network/UnitTests/ConnectionMock.hpp"
#include "Server/Game/UnitTests/PlayerContainerMock.hpp"
#include "Game/Actions/Attack.hpp"

using namespace testing;

class AttackTest : public Test
{
public:
    void SetUp()
    {
        Cake::DependencyInjection::clear();
        boost::shared_ptr<Common::Game::IRustedTime> time(new RustedTimeStub);
        Cake::DependencyInjection::forInterface<Common::Game::IRustedTime>().use(time);

        ON_CALL(dynamic_cast<RustedTimeStub&>(*time), getCurrentTime()).WillByDefault(Return(Common::Game::TimeValue()));
    }
};

TEST_F(AttackTest, JustAttack)
{
    Server::Network::ConnectionMock connection;
    Server::Game::PlayerContainerMock playerContainer;
    Common::Game::Object::ShipMock focusedShip;
    Common::Game::Object::ShipMock selectedShip;

    std::vector<Server::Network::IConnection *> allConnections{&connection};
    ON_CALL(playerContainer, getAllConnections(_)).WillByDefault(Return(allConnections));

    // AttackObject, ShipInfo
    EXPECT_CALL(connection, send(_)).Times(2);

    // doesn't matter if this is called, might be cached or something
    // the thing is what to return if it's called
    ON_CALL(selectedShip, getIntegrity()).WillByDefault(Return(100));

    EXPECT_CALL(selectedShip, setIntegrity(90)).Times(1);

    Server::Game::Actions::Attack attack(playerContainer, focusedShip, selectedShip);
    attack.execute();
}
