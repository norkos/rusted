#pragma once

#include "Client/States/IState.hpp"
#include "Client/States/IStateManagerStack.hpp"
#include "Client/Gui/Gui.hpp"
#include "Client/Services/EntityService.hpp"
#include "Client/Graphics/IGraphics.hpp"
#include "Client/Views/StaticObjectView.hpp"
#include "Client/Views/PilotView.hpp"

namespace Client
{
namespace States
{

class PilotState : public IState
{
public:
    PilotState(IStateManagerStack &, 
               Graphics::IGraphics &,
               Client::Gui::Gui &, 
               Client::Services::EntityService &,
               Views::StaticObjectView &,
               Views::PilotView &);
    void activate();
    void deactivate();
    void frameStarted();

private:
    Graphics::IGraphics & m_graphics;
    Client::Gui::Gui & m_gui;
    Views::StaticObjectView & m_staticObjectView;
    Views::PilotView & m_pilotView;
};

}
}
