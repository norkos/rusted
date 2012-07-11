#pragma once

#include <OgreRenderWindow.h>

#include "Gui/CEGUIIncludes.hpp"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

namespace Client
{
namespace Gui
{

class Gui
{
public:
    Gui(Ogre::RenderWindow &, Ogre::SceneManager &);

    CEGUI::WindowManager & getCeguiWindowManager();
    void setLayout(const std::string &);
    CEGUI::Window & getLayoutWindow();
private:
    void initResources();
    void initRenderer();

    Ogre::RenderWindow & m_ogreRenderWindow;
    Ogre::SceneManager & m_ogreSceneManager;
    CEGUI::Window * m_layoutWindow;

    MyGUI::Gui m_myGui;
    MyGUI::OgrePlatform m_myGuiOgrePlatform;
};

}
}
