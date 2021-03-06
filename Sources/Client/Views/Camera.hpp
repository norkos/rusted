#pragma once

#include "Common/Math/AnimatedVariable.hpp"
#include "Common/Game/Player.hpp"
#include "Client/Input/IInput.hpp"
#include "Client/Graphics/IGraphics.hpp"

namespace Client
{
namespace Views
{

class Camera : public Input::IMouseListener
{
public:
    Camera(Graphics::IGraphics &, Input::IInput &, Common::Game::Player &);
    ~Camera();

    void update();
    void zoomIn();
    void zoomOut();
    Ogre::Vector3 getPosition() const;
    Ogre::Quaternion getOrientation() const;
    bool isUserOrientationChanging() const;
    void resetUserOrientation();

    void mouseMoved(const OIS::MouseState &);
    void mousePressed(const OIS::MouseButtonID &, const OIS::MouseEvent &, unsigned x, unsigned y);
    void mouseReleased(const OIS::MouseButtonID &, unsigned x, unsigned y);

private:
    void recalculateUserOrientation();

    Graphics::IGraphics & m_graphics;
    Common::Game::Player & m_player;
    Common::Math::AnimatedVariable<int> m_distance;
    Ogre::Quaternion m_userOrientation;
    bool m_userOrientationChanging;
    Common::Math::AnimatedVariable<Common::Math::Real> m_userXAngle;
    Common::Math::AnimatedVariable<Common::Math::Real> m_userYAngle;
    Ogre::Light * m_cameraLight;
};

}
}
