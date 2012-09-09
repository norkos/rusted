#include <gtest/gtest.h>

#include <iostream>
#include <boost/foreach.hpp>

#include "Core/Component.hpp"
#include "Core/Connection.hpp"
#include "Preconditions.hpp"
#include "UserFunctions.hpp"

TEST(UserSct, Authorize)
{
	using namespace ::Common::Messages;

    std::string dbFile = "SampleDataBase.xml";

	SCT::Component component;
    component.setConfigValue("--database.provider", "xml");
    component.setConfigValue("--database.xml.filename", dbFile);
    component.start();
	boost::shared_ptr<SCT::Connection> connection = component.createConnection();

	// authorize user
	{
		Common::Messages::UserAuthorizationReq msg;
		msg.login = "user1";
		msg.password = "password";
		connection->send(msg);

		auto resp = connection->receive<Common::Messages::UserAuthorizationResp>();
		EXPECT_EQ(true, resp->success);
		EXPECT_EQ(1, resp->player_id);
	}

	// check player's resources
	{
		Common::Messages::PlayerResourcesStatusReq resourcesStatusReq;
		connection->send(resourcesStatusReq);

		auto resp = connection->receive<Common::Messages::PlayerResourcesStatusResp>();
		EXPECT_EQ(0xf00d, resp->carbon);
		EXPECT_EQ(0xf00d, resp->uranium);
		EXPECT_EQ(0xf00d, resp->credits);
	}
}

TEST(UserSct, TwoUsersEntitiesStatusReq)
{
    std::string dbFile = "SampleDataBase.xml";

	SCT::Component component;
    component.setConfigValue("--database.provider", "xml");
    component.setConfigValue("--database.xml.filename", dbFile);
    component.start();

    boost::shared_ptr<SCT::Connection> connection1 = authorizeUser(component, "user1", "password"); 
    boost::shared_ptr<SCT::Connection> connection2 = authorizeUser(component, "user2", "password"); 

    // first player
    {
        Common::Messages::FetchPlayerShips msg;
        connection1->send(msg);

        auto playerShips = connection1->receive<Common::Messages::PlayerShips>();
        ASSERT_EQ(1, playerShips->ships.size()); 
        EXPECT_EQ(1, playerShips->ships[0].get<0>());
    }

    // second player
    {
        Common::Messages::FetchPlayerShips msg;
        connection2->send(msg);

        auto playerShips = connection2->receive<Common::Messages::PlayerShips>();
        ASSERT_EQ(2, playerShips->ships.size()); 
    }
}
