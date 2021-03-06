#pragma once

#include <gmock/gmock.h>

namespace Server
{
namespace Game
{
namespace Actions
{

class ActionMock : public IAction
{
public:
    MOCK_METHOD0(start, Common::Game::TimeValue());
    MOCK_METHOD0(finish, Common::Game::TimeValue());
    MOCK_METHOD0(isAbleToStart, bool());
    MOCK_CONST_METHOD0(getName, std::string());
    MOCK_CONST_METHOD0(getDescription, std::string());
};

}
}
}

