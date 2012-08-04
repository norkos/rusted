#include <gtest/gtest.h>

#include "Game/ObjectFactory.hpp"
#include "Common/Game/Object/Ship.hpp"
#include "Common/Game/Object/StaticObject.hpp"
#include "DataBase/DataBaseNode.hpp"
#include "Game/UnitTests/RustedTimeStub.hpp"

using namespace testing;

class ObjectFactoryTest : public Test
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

TEST_F(ObjectFactoryTest, TestLoadShip)
{
    Server::DataBase::DataBaseNode node("object");
    node.setValue("type", "Ship");
    node.setValue("id", 1);
    node.setValue("owner", 2);
    node.setValue("x", 3);
    node.setValue("y", 4);
    node.setValue("z", 5);
    node.setValue("integrity", 100);
    Server::Game::ObjectFactory factory;

    boost::shared_ptr<Common::Game::Object::ObjectBase> object = factory.create(node);

    ASSERT_EQ(typeid(Common::Game::Object::Ship), typeid(*object));
    ASSERT_EQ(1, object->getId());
    ASSERT_EQ(2, dynamic_cast<Common::Game::Object::OwnedObjectBase&>(*object).getOwnerId());

    Common::Game::Position position = object->getPosition();
    ASSERT_EQ(3, position.getX());
    ASSERT_EQ(4, position.getY());
    ASSERT_EQ(5, position.getZ());

    ASSERT_EQ(100, object->getIntegrity());
}

TEST_F(ObjectFactoryTest, LoadStaticObject)
{
    Server::DataBase::DataBaseNode node("object");
    node.setValue("type", "StaticObject");
    node.setValue("id", 1);
    node.setValue("x", 3);
    node.setValue("y", 4);
    node.setValue("z", 5);
    node.setValue("integrity", 100);
    Server::Game::ObjectFactory factory;

    boost::shared_ptr<Common::Game::Object::ObjectBase> object = factory.create(node);

    ASSERT_EQ(typeid(Common::Game::Object::StaticObject), typeid(*object));
    Common::Game::Position position = object->getPosition();
    ASSERT_EQ(3, position.getX());
    ASSERT_EQ(4, position.getY());
    ASSERT_EQ(5, position.getZ());

    ASSERT_EQ(100, object->getIntegrity());
}