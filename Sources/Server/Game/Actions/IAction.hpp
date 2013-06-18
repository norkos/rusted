#pragma once

#include "Common/Game/TimeValue.hpp"

namespace Server 
{
namespace Game
{
namespace Actions
{

class IAction
{
public:
    /* @returns Time after which finish() is expected to call */
    virtual Common::Game::TimeValue start() = 0;

    /* @returns Time when another action of this type can be executed */
    virtual Common::Game::TimeValue finish() = 0;

    virtual ~IAction() {}
};

}
}
}
