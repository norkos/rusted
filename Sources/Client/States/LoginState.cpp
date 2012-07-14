#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Cake/Diagnostics/Logger.hpp"

#include "Client/States/IState.hpp"
#include "Client/States/LoginState.hpp"

using namespace Client::States;

LoginState::LoginState(IStateManagerStack & stateManagerStack,
                       Gui::Gui & gui, 
                       IState & entitySelect,
                       Services::AuthorizationService & authorizationService,
                       Services::RustedTimeService & rustedTimeService,
                       States::IStateDeployment & stateDeployment) : 
    m_gui(gui),
    m_authorizationService(authorizationService),
    m_rustedTimeService(rustedTimeService),
    m_stateManagerStack(stateManagerStack),
    m_entitySelectState(entitySelect),
    m_stateDeployment(stateDeployment)
{
}

void LoginState::activate()
{
    m_gui.setLayout("LoginScreen.layout");

    m_gui->findWidget<MyGUI::Button>("LoginButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::loginButtonClicked);
    m_gui->findWidget<MyGUI::Button>("QuitButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &LoginState::quitButtonClicked);
}

void LoginState::deactivate()
{
}

void LoginState::frameStarted()
{
}

void LoginState::loginButtonClicked(MyGUI::WidgetPtr)
{
    LOG_DEBUG << "Login button clicked, let's make the connection!";
    try
    {
        m_stateDeployment.deployNewConnection();

        CEGUI::Window * loginEditbox = m_gui.getLayoutWindow().getChildRecursive("LoginEditbox");
        CEGUI::Window * passwordEditbox = m_gui.getLayoutWindow().getChildRecursive("PasswordEditbox");

        assert(loginEditbox);
        assert(passwordEditbox);
 
        m_authorizationService.login(boost::lexical_cast<std::string>(loginEditbox->getText()), 
                                     boost::lexical_cast<std::string>(passwordEditbox->getText()),
                                     boost::bind(&LoginState::loggedIn, this, _1));
    }
    catch (...)
    {
        LOG_ERR << "Can't connect";
    }
}

void LoginState::quitButtonClicked(MyGUI::WidgetPtr)
{
    ::exit(0);
}

void LoginState::loggedIn(bool success)
{
    if (success)
    {
        LOG_INFO << "Logged in";
        m_stateDeployment.deployAuthorizedConnection();
        m_rustedTimeService.synchronize();
        m_stateManagerStack.pushState(m_entitySelectState);
    }
    else
    {
        LOG_WARN << "Server refused authorization, sorry.";
    }
}

