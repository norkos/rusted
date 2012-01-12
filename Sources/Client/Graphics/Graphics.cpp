#include "Cake/Diagnostics/Logger.hpp"
#include "Client/Graphics/Graphics.hpp"

using namespace Client::Graphics;

Graphics::Graphics()
{
    initOgre();
    initResources();
}

Ogre::Root & Graphics::getOgreRoot()
{
    return *m_ogreRoot;
}

Ogre::SceneManager & Graphics::getSceneManager()
{
    return *m_ogreSceneManager;
}

Ogre::RenderWindow & Graphics::getRenderWindow()
{
    return *m_ogreRenderWindow;
}

Ogre::Camera & Graphics::getCamera()
{
    return *m_ogreCamera;
}

unsigned Graphics::getWidth()
{
    return m_ogreRenderWindow->getWidth();
}

unsigned Graphics::getHeight()
{
    return m_ogreRenderWindow->getHeight();
}

OgreObject & Graphics::createOgreObject()
{
    LOG_ERR << "Not implemented";
}

void Graphics::initOgre()
{
    m_ogreRoot = new Ogre::Root("", "");

    //TODO: This application uses hardcoded OGRE library: /usr/lib/OGRE/RenderSystem_GL.so
    m_ogreRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL.so");

    if (m_ogreRoot->getAvailableRenderers().begin() == m_ogreRoot->getAvailableRenderers().end())
    {
        LOG_ERR << "No OGRE renderers available";
    }

    m_ogreRoot->setRenderSystem(*m_ogreRoot->getAvailableRenderers().begin());
    m_ogreRoot->initialise(false);

    initResources();

    Ogre::NameValuePairList videoOptions;
    m_ogreRenderWindow = m_ogreRoot->createRenderWindow("Rusted", 800, 600, false, &videoOptions);

    Ogre::SceneManager * sm = m_ogreRoot->createSceneManager(Ogre::ST_GENERIC, "SceneMgr");
    m_ogreSceneManager = sm;
    Ogre::Camera * camera = sm->createCamera("SampleCam");
    m_ogreCamera = camera;
    camera->setPosition(Ogre::Vector3(0,0,500));
    camera->lookAt(Ogre::Vector3(0,0,-300));

    Ogre::Viewport * vp = m_ogreRenderWindow->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void Graphics::initResources()
{
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Contents/meshes", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Contents/materials", "FileSystem", "General");
}
