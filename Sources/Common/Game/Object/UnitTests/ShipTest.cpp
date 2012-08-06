#include <gtest/gtest.h>

#include "Cake/DependencyInjection/Registry.hpp"

#include "Game/Object/Ship.hpp"
#include "Game/UnitTests/RustedTimeStub.hpp"
#include "Game/Object/UnitTests/ShipMock.hpp"

using namespace testing;
using namespace Common::Game;

class ShipTest : public Test
{
public:
    void SetUp()
    {
        Cake::DependencyInjection::clear();
        m_time.reset(new RustedTimeStub);
        Cake::DependencyInjection::forInterface<Common::Game::IRustedTime>().use(m_time);
    }

    RustedTimeStub & getRustedTimeStub()
    {
        return dynamic_cast<RustedTimeStub &>(*m_time);
    }

private:
    boost::shared_ptr<Common::Game::IRustedTime> m_time;
};

TEST_F(ShipTest, TestMoveByVector)
{
    Common::Game::Object::Ship ship;

    ship.setPosition(Common::Game::Position(0, 0, 0));

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(0, 0)));
    ship.setCourse(Common::Game::Position(100, 0, 0));
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(50, 0)));
    ASSERT_EQ(Common::Game::Position(50, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(100, 0)));
    ASSERT_EQ(Common::Game::Position(100, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(100, 0)));
    ship.setCourse(Common::Game::Position(100, 100, 0));
    Mock::VerifyAndClear(&getRustedTimeStub());

    // still the same place
    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(100, 0)));
    ASSERT_EQ(Common::Game::Position(100, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());

    // should be half the way
    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(150, 0)));
    ASSERT_EQ(Common::Game::Position(100, 50, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(200, 0)));
    ASSERT_EQ(Common::Game::Position(100, 100, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());
}

TEST_F(ShipTest, HighPrecisionTimer)
{
    Common::Game::Object::Ship ship;

    ship.setPosition(Common::Game::Position(0, 0, 0));
    ship.setSpeed(2);

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(0, 0)));
    ship.setCourse(Common::Game::Position(2, 0, 0));
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(0, 500)));
    ASSERT_EQ(Common::Game::Position(1, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());
}

TEST_F(ShipTest, MoveToTheSamePosition)
{
    Common::Game::Object::Ship ship;

    ship.setPosition(Common::Game::Position(1, 2, 3));

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(100, 0)));
    ship.setCourse(Common::Game::Position(1, 2, 3));
    Mock::VerifyAndClear(&getRustedTimeStub());

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(100, 0)));
    ASSERT_EQ(Common::Game::Position(1, 2, 3), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());
}

/* When ship is destroyed somewhere, it should stop moving and stay in place where it
 * was when it happened. 
 */
TEST_F(ShipTest, ShipDestroyedDuringFlight)
{
    Common::Game::Object::Ship ship;

    ship.setPosition(Common::Game::Position(0, 0, 0));

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(0, 0)));
    ship.setCourse(Common::Game::Position(100, 0, 0));
    Mock::VerifyAndClear(&getRustedTimeStub());

    ON_CALL(getRustedTimeStub(), getCurrentTime()).WillByDefault(Return(TimeValue(50, 0)));
    ASSERT_EQ(Common::Game::Position(50, 0, 0), ship.getPosition());
    ship.setIntegrity(0);
    Mock::VerifyAndClear(&getRustedTimeStub());

    ON_CALL(getRustedTimeStub(), getCurrentTime()).WillByDefault(Return(TimeValue(100, 0)));
    ASSERT_EQ(Common::Game::Position(50, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());
}

/* Now, damaging ship doesn't affect anything 
 */
TEST_F(ShipTest, ShipDamagedDuringFlight)
{
    Common::Game::Object::Ship ship;

    ship.setPosition(Common::Game::Position(0, 0, 0));

    EXPECT_CALL(getRustedTimeStub(), getCurrentTime()).Times(1).WillOnce(Return(TimeValue(0, 0)));
    ship.setCourse(Common::Game::Position(100, 0, 0));
    Mock::VerifyAndClear(&getRustedTimeStub());

    ON_CALL(getRustedTimeStub(), getCurrentTime()).WillByDefault(Return(TimeValue(50, 0)));
    ASSERT_EQ(Common::Game::Position(50, 0, 0), ship.getPosition());
    ship.setIntegrity(10);
    Mock::VerifyAndClear(&getRustedTimeStub());

    ON_CALL(getRustedTimeStub(), getCurrentTime()).WillByDefault(Return(TimeValue(100, 0)));
    ASSERT_EQ(Common::Game::Position(100, 0, 0), ship.getPosition());
    Mock::VerifyAndClear(&getRustedTimeStub());
}
