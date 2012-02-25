#pragma once

#include "Common/Game/Object/StaticObject.hpp"
#include "Client/Views/IView.hpp"
#include "Client/Services/ObjectService.hpp"
#include "Client/Graphics/IGraphics.hpp"
#include "Object.hpp"

namespace Client
{
namespace Views
{

class ObjectsView : public IView
{
public:
    ObjectsView(Services::ObjectService &,
                Graphics::IGraphics &,
                Common::Game::Universe &);

    void activate();
    void deactivate();
    void frameStarted();

    void objectAdded(Common::Game::Object::ObjectBase &);

private:
    Services::ObjectService & m_objectService;
    Graphics::IGraphics & m_graphics;
    Common::Game::Universe & m_universe;
    std::vector<boost::shared_ptr<Object> > m_objects;
};

}
}