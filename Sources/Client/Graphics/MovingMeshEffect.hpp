#pragma once

#include "Common/Game/Position.hpp"
#include "Common/Game/IRustedTime.hpp"
#include "Common/Game/TimeValue.hpp"

#include "IGraphics.hpp"
#include "IEffect.hpp"

namespace Client
{
namespace Graphics
{

class MovingMeshEffect : public IEffect
{
public:
    MovingMeshEffect(
        IGraphics &, 
        Common::Game::Position start,
        Common::Game::Position end);

    void frameStarted(); 
    bool isAlive();

private:
    IGraphics & m_graphics;
    Ogre::Entity * m_entity;
    Ogre::SceneNode * m_node;
    Common::Game::Position m_start;
    Common::Game::Position m_end;
    Common::Game::TimeValue m_startTime;
    Cake::DependencyInjection::Inject<Common::Game::IRustedTime> m_time;
};

}
}

