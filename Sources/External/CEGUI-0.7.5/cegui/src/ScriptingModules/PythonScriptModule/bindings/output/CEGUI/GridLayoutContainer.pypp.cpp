// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "GridLayoutContainer.pypp.hpp"

namespace bp = boost::python;

struct GridLayoutContainer_wrapper : CEGUI::GridLayoutContainer, bp::wrapper< CEGUI::GridLayoutContainer > {

    GridLayoutContainer_wrapper(::CEGUI::String const & type, ::CEGUI::String const & name )
    : CEGUI::GridLayoutContainer( boost::ref(type), boost::ref(name) )
      , bp::wrapper< CEGUI::GridLayoutContainer >(){
        // constructor
    
    }

    virtual void layout(  ) {
        if( bp::override func_layout = this->get_override( "layout" ) )
            func_layout(  );
        else{
            this->CEGUI::GridLayoutContainer::layout(  );
        }
    }
    
    void default_layout(  ) {
        CEGUI::GridLayoutContainer::layout( );
    }

    virtual void swapChildWindowPositions( ::size_t wnd1, ::size_t wnd2 ) {
        if( bp::override func_swapChildWindowPositions = this->get_override( "swapChildWindowPositions" ) )
            func_swapChildWindowPositions( wnd1, wnd2 );
        else{
            this->CEGUI::GridLayoutContainer::swapChildWindowPositions( wnd1, wnd2 );
        }
    }
    
    void default_swapChildWindowPositions( ::size_t wnd1, ::size_t wnd2 ) {
        CEGUI::GridLayoutContainer::swapChildWindowPositions( wnd1, wnd2 );
    }

    virtual void beginInitialisation(  ) {
        if( bp::override func_beginInitialisation = this->get_override( "beginInitialisation" ) )
            func_beginInitialisation(  );
        else{
            this->CEGUI::Window::beginInitialisation(  );
        }
    }
    
    void default_beginInitialisation(  ) {
        CEGUI::Window::beginInitialisation( );
    }

    virtual void cloneChildWidgetsTo( ::CEGUI::Window & target ) const  {
        if( bp::override func_cloneChildWidgetsTo = this->get_override( "cloneChildWidgetsTo" ) )
            func_cloneChildWidgetsTo( boost::ref(target) );
        else{
            this->CEGUI::Window::cloneChildWidgetsTo( boost::ref(target) );
        }
    }
    
    void default_cloneChildWidgetsTo( ::CEGUI::Window & target ) const  {
        CEGUI::Window::cloneChildWidgetsTo( boost::ref(target) );
    }

    virtual void clonePropertiesTo( ::CEGUI::Window & target ) const  {
        if( bp::override func_clonePropertiesTo = this->get_override( "clonePropertiesTo" ) )
            func_clonePropertiesTo( boost::ref(target) );
        else{
            this->CEGUI::Window::clonePropertiesTo( boost::ref(target) );
        }
    }
    
    void default_clonePropertiesTo( ::CEGUI::Window & target ) const  {
        CEGUI::Window::clonePropertiesTo( boost::ref(target) );
    }

    virtual void destroy(  ) {
        if( bp::override func_destroy = this->get_override( "destroy" ) )
            func_destroy(  );
        else{
            this->CEGUI::Window::destroy(  );
        }
    }
    
    void default_destroy(  ) {
        CEGUI::Window::destroy( );
    }

    virtual void endInitialisation(  ) {
        if( bp::override func_endInitialisation = this->get_override( "endInitialisation" ) )
            func_endInitialisation(  );
        else{
            this->CEGUI::Window::endInitialisation(  );
        }
    }
    
    void default_endInitialisation(  ) {
        CEGUI::Window::endInitialisation( );
    }

    virtual void fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        if( bp::override func_fireEvent = this->get_override( "fireEvent" ) )
            func_fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        else{
            this->CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        }
    }
    
    void default_fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
    }

    virtual void getRenderingContext_impl( ::CEGUI::RenderingContext & ctx ) const  {
        if( bp::override func_getRenderingContext_impl = this->get_override( "getRenderingContext_impl" ) )
            func_getRenderingContext_impl( boost::ref(ctx) );
        else{
            this->CEGUI::Window::getRenderingContext_impl( boost::ref(ctx) );
        }
    }
    
    void default_getRenderingContext_impl( ::CEGUI::RenderingContext & ctx ) const  {
        CEGUI::Window::getRenderingContext_impl( boost::ref(ctx) );
    }

    virtual ::CEGUI::Rect getUnclippedInnerRect_impl(  ) const  {
        if( bp::override func_getUnclippedInnerRect_impl = this->get_override( "getUnclippedInnerRect_impl" ) )
            return func_getUnclippedInnerRect_impl(  );
        else{
            return this->CEGUI::LayoutContainer::getUnclippedInnerRect_impl(  );
        }
    }
    
    ::CEGUI::Rect default_getUnclippedInnerRect_impl(  ) const  {
        return CEGUI::LayoutContainer::getUnclippedInnerRect_impl( );
    }

    virtual void initialiseComponents(  ) {
        if( bp::override func_initialiseComponents = this->get_override( "initialiseComponents" ) )
            func_initialiseComponents(  );
        else{
            this->CEGUI::Window::initialiseComponents(  );
        }
    }
    
    void default_initialiseComponents(  ) {
        CEGUI::Window::initialiseComponents( );
    }

    virtual bool isHit( ::CEGUI::Vector2 const & position, bool const allow_disabled=false ) const  {
        if( bp::override func_isHit = this->get_override( "isHit" ) )
            return func_isHit( boost::ref(position), allow_disabled );
        else{
            return this->CEGUI::Window::isHit( boost::ref(position), allow_disabled );
        }
    }
    
    bool default_isHit( ::CEGUI::Vector2 const & position, bool const allow_disabled=false ) const  {
        return CEGUI::Window::isHit( boost::ref(position), allow_disabled );
    }

    virtual void layoutIfNecessary(  ) {
        if( bp::override func_layoutIfNecessary = this->get_override( "layoutIfNecessary" ) )
            func_layoutIfNecessary(  );
        else{
            this->CEGUI::LayoutContainer::layoutIfNecessary(  );
        }
    }
    
    void default_layoutIfNecessary(  ) {
        CEGUI::LayoutContainer::layoutIfNecessary( );
    }

    virtual void performChildWindowLayout(  ) {
        if( bp::override func_performChildWindowLayout = this->get_override( "performChildWindowLayout" ) )
            func_performChildWindowLayout(  );
        else{
            this->CEGUI::Window::performChildWindowLayout(  );
        }
    }
    
    void default_performChildWindowLayout(  ) {
        CEGUI::Window::performChildWindowLayout( );
    }

    virtual void setLookNFeel( ::CEGUI::String const & look ) {
        if( bp::override func_setLookNFeel = this->get_override( "setLookNFeel" ) )
            func_setLookNFeel( boost::ref(look) );
        else{
            this->CEGUI::Window::setLookNFeel( boost::ref(look) );
        }
    }
    
    void default_setLookNFeel( ::CEGUI::String const & look ) {
        CEGUI::Window::setLookNFeel( boost::ref(look) );
    }

    virtual void setMargin( ::CEGUI::UBox const & margin ) {
        if( bp::override func_setMargin = this->get_override( "setMargin" ) )
            func_setMargin( boost::ref(margin) );
        else{
            this->CEGUI::Window::setMargin( boost::ref(margin) );
        }
    }
    
    void default_setMargin( ::CEGUI::UBox const & margin ) {
        CEGUI::Window::setMargin( boost::ref(margin) );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
    }

    virtual void update( float elapsed ) {
        if( bp::override func_update = this->get_override( "update" ) )
            func_update( elapsed );
        else{
            this->CEGUI::LayoutContainer::update( elapsed );
        }
    }
    
    void default_update( float elapsed ) {
        CEGUI::LayoutContainer::update( elapsed );
    }

    virtual void writeXMLToStream( ::CEGUI::XMLSerializer & xml_stream ) const  {
        if( bp::override func_writeXMLToStream = this->get_override( "writeXMLToStream" ) )
            func_writeXMLToStream( boost::ref(xml_stream) );
        else{
            this->CEGUI::Window::writeXMLToStream( boost::ref(xml_stream) );
        }
    }
    
    void default_writeXMLToStream( ::CEGUI::XMLSerializer & xml_stream ) const  {
        CEGUI::Window::writeXMLToStream( boost::ref(xml_stream) );
    }

};

void register_GridLayoutContainer_class(){

    { //::CEGUI::GridLayoutContainer
        typedef bp::class_< GridLayoutContainer_wrapper, bp::bases< CEGUI::LayoutContainer >, boost::noncopyable > GridLayoutContainer_exposer_t;
        GridLayoutContainer_exposer_t GridLayoutContainer_exposer = GridLayoutContainer_exposer_t( "GridLayoutContainer", "*!\n\
        \n\
            A Layout Container window layouting it's children into a grid\n\
        *\n", bp::init< CEGUI::String const &, CEGUI::String const & >(( bp::arg("type"), bp::arg("name") ), "*************************************************************************\n\
            Construction and Destruction\n\
        *************************************************************************\n\
        *!\n\
        \n\
            Constructor for GUISheet windows.\n\
        *\n") );
        bp::scope GridLayoutContainer_scope( GridLayoutContainer_exposer );
        bp::enum_< CEGUI::GridLayoutContainer::AutoPositioning>("AutoPositioning")
            .value("AP_Disabled", CEGUI::GridLayoutContainer::AP_Disabled)
            .value("AP_LeftToRight", CEGUI::GridLayoutContainer::AP_LeftToRight)
            .value("AP_TopToBottom", CEGUI::GridLayoutContainer::AP_TopToBottom)
            .export_values()
            ;
        { //::CEGUI::GridLayoutContainer::addChildWindowToPosition
        
            typedef void ( ::CEGUI::GridLayoutContainer::*addChildWindowToPosition_function_type )( ::CEGUI::Window *,::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "addChildWindowToPosition"
                , addChildWindowToPosition_function_type( &::CEGUI::GridLayoutContainer::addChildWindowToPosition )
                , ( bp::arg("window"), bp::arg("gridX"), bp::arg("gridY") )
                , "*!\n\
                \n\
                    Add the specified Window to specified grid position as a child of\n\
                    this Grid Layout Container.  If the Window  window is already\n\
                    attached to a Window, it is detached before being added to this Window.\n\
            \n\
                \n\
                    If something is already in given grid cell, it gets removed!\n\
            \n\
                \n\
                    This disabled auto positioning from further usage! You need to call\n\
                    setAutoPositioning(..) to set it back to your desired value and use\n\
                    setAutoPositioningIdx(..) to set it's starting point back\n\
            \n\
                @see\n\
                    Window.addChildWindow\n\
                *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::addChildWindowToPosition
        
            typedef void ( ::CEGUI::GridLayoutContainer::*addChildWindowToPosition_function_type )( ::CEGUI::String const &,::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "addChildWindowToPosition"
                , addChildWindowToPosition_function_type( &::CEGUI::GridLayoutContainer::addChildWindowToPosition )
                , ( bp::arg("name"), bp::arg("gridX"), bp::arg("gridY") )
                , "*!\n\
                \n\
                    Add the named Window to specified grid position as a child of\n\
                    this Grid Layout Container.  If the Window  window is already\n\
                    attached to a Window, it is detached before being added to this Window.\n\
            \n\
                \n\
                    If something is already in given grid cell, it gets removed!\n\
            \n\
                \n\
                    This disabled auto positioning from further usage! You need to call\n\
                    setAutoPositioning(..) to set it back to your desired value and use\n\
                    setAutoPositioningIdx(..) to set it's starting point back\n\
            \n\
                @see\n\
                    Window.addChildWindow\n\
                *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::autoPositioningSkipCells
        
            typedef void ( ::CEGUI::GridLayoutContainer::*autoPositioningSkipCells_function_type )( ::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "autoPositioningSkipCells"
                , autoPositioningSkipCells_function_type( &::CEGUI::GridLayoutContainer::autoPositioningSkipCells )
                , ( bp::arg("cells") )
                , "*!\n\
            \n\
                Skips given number of cells in the auto positioning sequence\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::getAutoPositioning
        
            typedef ::CEGUI::GridLayoutContainer::AutoPositioning ( ::CEGUI::GridLayoutContainer::*getAutoPositioning_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getAutoPositioning"
                , getAutoPositioning_function_type( &::CEGUI::GridLayoutContainer::getAutoPositioning )
                , "*!\n\
            \n\
                Retrieves current auto positioning method.\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::getChildWindowAtPosition
        
            typedef ::CEGUI::Window * ( ::CEGUI::GridLayoutContainer::*getChildWindowAtPosition_function_type )( ::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "getChildWindowAtPosition"
                , getChildWindowAtPosition_function_type( &::CEGUI::GridLayoutContainer::getChildWindowAtPosition )
                , ( bp::arg("gridX"), bp::arg("gridY") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
            \n\
                Retrieves child window that is currently at given grid position\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::getGridHeight
        
            typedef ::size_t ( ::CEGUI::GridLayoutContainer::*getGridHeight_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getGridHeight"
                , getGridHeight_function_type( &::CEGUI::GridLayoutContainer::getGridHeight )
                , "*!\n\
            \n\
                Retrieves grid height, the amount of rows in the grid\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::getGridWidth
        
            typedef ::size_t ( ::CEGUI::GridLayoutContainer::*getGridWidth_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getGridWidth"
                , getGridWidth_function_type( &::CEGUI::GridLayoutContainer::getGridWidth )
                , "*!\n\
            \n\
                Retrieves grid width, the amount of cells in one row\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::getNextAutoPositioningIdx
        
            typedef ::size_t ( ::CEGUI::GridLayoutContainer::*getNextAutoPositioningIdx_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getNextAutoPositioningIdx"
                , getNextAutoPositioningIdx_function_type( &::CEGUI::GridLayoutContainer::getNextAutoPositioningIdx )
                , "*!\n\
            \n\
                Retrieves auto positioning sequence position, this will be used next\n\
                time when addChildWindow is called.\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::layout
        
            typedef void ( ::CEGUI::GridLayoutContainer::*layout_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_layout_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "layout"
                , layout_function_type(&::CEGUI::GridLayoutContainer::layout)
                , default_layout_function_type(&GridLayoutContainer_wrapper::default_layout) );
        
        }
        { //::CEGUI::GridLayoutContainer::moveChildWindowToPosition
        
            typedef void ( ::CEGUI::GridLayoutContainer::*moveChildWindowToPosition_function_type )( ::CEGUI::Window *,::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "moveChildWindowToPosition"
                , moveChildWindowToPosition_function_type( &::CEGUI::GridLayoutContainer::moveChildWindowToPosition )
                , ( bp::arg("wnd"), bp::arg("gridX"), bp::arg("gridY") )
                , "*!\n\
            \n\
                Moves given child window to given grid position\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::moveChildWindowToPosition
        
            typedef void ( ::CEGUI::GridLayoutContainer::*moveChildWindowToPosition_function_type )( ::CEGUI::String const &,::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "moveChildWindowToPosition"
                , moveChildWindowToPosition_function_type( &::CEGUI::GridLayoutContainer::moveChildWindowToPosition )
                , ( bp::arg("wnd"), bp::arg("gridX"), bp::arg("gridY") )
                , "*!\n\
            \n\
                Moves named child window to given grid position\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::removeChildWindowFromPosition
        
            typedef void ( ::CEGUI::GridLayoutContainer::*removeChildWindowFromPosition_function_type )( ::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "removeChildWindowFromPosition"
                , removeChildWindowFromPosition_function_type( &::CEGUI::GridLayoutContainer::removeChildWindowFromPosition )
                , ( bp::arg("gridX"), bp::arg("gridY") )
                , "*!\n\
                \n\
                    Removes the child window that is currently at given grid position\n\
            \n\
                @see\n\
                    Window.removeChildWindow\n\
                *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::setAutoPositioning
        
            typedef void ( ::CEGUI::GridLayoutContainer::*setAutoPositioning_function_type )( ::CEGUI::GridLayoutContainer::AutoPositioning ) ;
            
            GridLayoutContainer_exposer.def( 
                "setAutoPositioning"
                , setAutoPositioning_function_type( &::CEGUI::GridLayoutContainer::setAutoPositioning )
                , ( bp::arg("positioning") )
                , "*!\n\
                \n\
                    Sets new auto positioning method.\n\
            \n\
                \n\
                    The newly set auto positioning sequence will start over!\n\
                    Use setAutoPositioningIdx to set it's starting point\n\
                *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::setGridDimensions
        
            typedef void ( ::CEGUI::GridLayoutContainer::*setGridDimensions_function_type )( ::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "setGridDimensions"
                , setGridDimensions_function_type( &::CEGUI::GridLayoutContainer::setGridDimensions )
                , ( bp::arg("width"), bp::arg("height") )
                , "*!\n\
            \n\
                Sets grid's dimensions.\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::setNextAutoPositioningIdx
        
            typedef void ( ::CEGUI::GridLayoutContainer::*setNextAutoPositioningIdx_function_type )( ::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "setNextAutoPositioningIdx"
                , setNextAutoPositioningIdx_function_type( &::CEGUI::GridLayoutContainer::setNextAutoPositioningIdx )
                , ( bp::arg("idx") )
                , "*!\n\
            \n\
                Sets the next auto positioning sequence position, this will be used\n\
                next time when addChildWindow is called.\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::swapChildWindowPositions
        
            typedef void ( ::CEGUI::GridLayoutContainer::*swapChildWindowPositions_function_type )( ::size_t,::size_t ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_swapChildWindowPositions_function_type )( ::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "swapChildWindowPositions"
                , swapChildWindowPositions_function_type(&::CEGUI::GridLayoutContainer::swapChildWindowPositions)
                , default_swapChildWindowPositions_function_type(&GridLayoutContainer_wrapper::default_swapChildWindowPositions)
                , ( bp::arg("wnd1"), bp::arg("wnd2") ) );
        
        }
        { //::CEGUI::GridLayoutContainer::swapChildWindowPositions
        
            typedef void ( ::CEGUI::GridLayoutContainer::*swapChildWindowPositions_function_type )( ::size_t,::size_t,::size_t,::size_t ) ;
            
            GridLayoutContainer_exposer.def( 
                "swapChildWindowPositions"
                , swapChildWindowPositions_function_type( &::CEGUI::GridLayoutContainer::swapChildWindowPositions )
                , ( bp::arg("gridX1"), bp::arg("gridY1"), bp::arg("gridX2"), bp::arg("gridY2") )
                , "*!\n\
            \n\
                Swaps positions of 2 windows given by grid positions\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::swapChildWindows
        
            typedef void ( ::CEGUI::GridLayoutContainer::*swapChildWindows_function_type )( ::CEGUI::Window *,::CEGUI::Window * ) ;
            
            GridLayoutContainer_exposer.def( 
                "swapChildWindows"
                , swapChildWindows_function_type( &::CEGUI::GridLayoutContainer::swapChildWindows )
                , ( bp::arg("wnd1"), bp::arg("wnd2") )
                , "*!\n\
            \n\
                Swaps positions of given windows\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::swapChildWindows
        
            typedef void ( ::CEGUI::GridLayoutContainer::*swapChildWindows_function_type )( ::CEGUI::Window *,::CEGUI::String const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "swapChildWindows"
                , swapChildWindows_function_type( &::CEGUI::GridLayoutContainer::swapChildWindows )
                , ( bp::arg("wnd1"), bp::arg("wnd2") )
                , "*!\n\
            \n\
                Swaps positions of given windows\n\
            *\n" );
        
        }
        { //::CEGUI::GridLayoutContainer::swapChildWindows
        
            typedef void ( ::CEGUI::GridLayoutContainer::*swapChildWindows_function_type )( ::CEGUI::String const &,::CEGUI::Window * ) ;
            
            GridLayoutContainer_exposer.def( 
                "swapChildWindows"
                , swapChildWindows_function_type( &::CEGUI::GridLayoutContainer::swapChildWindows )
                , ( bp::arg("wnd1"), bp::arg("wnd2") )
                , "*!\n\
            \n\
                Swaps positions of given windows\n\
            *\n" );
        
        }
        GridLayoutContainer_exposer.add_static_property( "DummyNameSuffix"
                        , bp::make_getter( &CEGUI::GridLayoutContainer::DummyNameSuffix
                                , bp::return_value_policy< bp::return_by_value >() ) );
        GridLayoutContainer_exposer.add_static_property( "EventChildWindowOrderChanged"
                        , bp::make_getter( &CEGUI::GridLayoutContainer::EventChildWindowOrderChanged
                                , bp::return_value_policy< bp::return_by_value >() ) );
        { //::CEGUI::Window::beginInitialisation
        
            typedef void ( ::CEGUI::Window::*beginInitialisation_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_beginInitialisation_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "beginInitialisation"
                , beginInitialisation_function_type(&::CEGUI::Window::beginInitialisation)
                , default_beginInitialisation_function_type(&GridLayoutContainer_wrapper::default_beginInitialisation) );
        
        }
        { //::CEGUI::Window::cloneChildWidgetsTo
        
            typedef void ( ::CEGUI::Window::*cloneChildWidgetsTo_function_type )( ::CEGUI::Window & ) const;
            typedef void ( GridLayoutContainer_wrapper::*default_cloneChildWidgetsTo_function_type )( ::CEGUI::Window & ) const;
            
            GridLayoutContainer_exposer.def( 
                "cloneChildWidgetsTo"
                , cloneChildWidgetsTo_function_type(&::CEGUI::Window::cloneChildWidgetsTo)
                , default_cloneChildWidgetsTo_function_type(&GridLayoutContainer_wrapper::default_cloneChildWidgetsTo)
                , ( bp::arg("target") ) );
        
        }
        { //::CEGUI::Window::clonePropertiesTo
        
            typedef void ( ::CEGUI::Window::*clonePropertiesTo_function_type )( ::CEGUI::Window & ) const;
            typedef void ( GridLayoutContainer_wrapper::*default_clonePropertiesTo_function_type )( ::CEGUI::Window & ) const;
            
            GridLayoutContainer_exposer.def( 
                "clonePropertiesTo"
                , clonePropertiesTo_function_type(&::CEGUI::Window::clonePropertiesTo)
                , default_clonePropertiesTo_function_type(&GridLayoutContainer_wrapper::default_clonePropertiesTo)
                , ( bp::arg("target") ) );
        
        }
        { //::CEGUI::Window::destroy
        
            typedef void ( ::CEGUI::Window::*destroy_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_destroy_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "destroy"
                , destroy_function_type(&::CEGUI::Window::destroy)
                , default_destroy_function_type(&GridLayoutContainer_wrapper::default_destroy) );
        
        }
        { //::CEGUI::Window::endInitialisation
        
            typedef void ( ::CEGUI::Window::*endInitialisation_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_endInitialisation_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "endInitialisation"
                , endInitialisation_function_type(&::CEGUI::Window::endInitialisation)
                , default_endInitialisation_function_type(&GridLayoutContainer_wrapper::default_endInitialisation) );
        
        }
        { //::CEGUI::EventSet::fireEvent
        
            typedef void ( ::CEGUI::EventSet::*fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "fireEvent"
                , fireEvent_function_type(&::CEGUI::EventSet::fireEvent)
                , default_fireEvent_function_type(&GridLayoutContainer_wrapper::default_fireEvent)
                , ( bp::arg("name"), bp::arg("args"), bp::arg("eventNamespace")="" ) );
        
        }
        { //::CEGUI::Window::getRenderedStringParser
        
            typedef ::CEGUI::RenderedStringParser & ( ::CEGUI::Window::*getRenderedStringParser_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getRenderedStringParser"
                , getRenderedStringParser_function_type(&::CEGUI::Window::getRenderedStringParser)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::CEGUI::Window::getRenderingContext_impl
        
            typedef void ( ::CEGUI::Window::*getRenderingContext_impl_function_type )( ::CEGUI::RenderingContext & ) const;
            typedef void ( GridLayoutContainer_wrapper::*default_getRenderingContext_impl_function_type )( ::CEGUI::RenderingContext & ) const;
            
            GridLayoutContainer_exposer.def( 
                "getRenderingContext_impl"
                , getRenderingContext_impl_function_type(&::CEGUI::Window::getRenderingContext_impl)
                , default_getRenderingContext_impl_function_type(&GridLayoutContainer_wrapper::default_getRenderingContext_impl)
                , ( bp::arg("ctx") ) );
        
        }
        { //::CEGUI::LayoutContainer::getUnclippedInnerRect_impl
        
            typedef ::CEGUI::Rect ( ::CEGUI::LayoutContainer::*getUnclippedInnerRect_impl_function_type )(  ) const;
            typedef ::CEGUI::Rect ( GridLayoutContainer_wrapper::*default_getUnclippedInnerRect_impl_function_type )(  ) const;
            
            GridLayoutContainer_exposer.def( 
                "getUnclippedInnerRect_impl"
                , getUnclippedInnerRect_impl_function_type(&::CEGUI::LayoutContainer::getUnclippedInnerRect_impl)
                , default_getUnclippedInnerRect_impl_function_type(&GridLayoutContainer_wrapper::default_getUnclippedInnerRect_impl) );
        
        }
        { //::CEGUI::Window::initialiseComponents
        
            typedef void ( ::CEGUI::Window::*initialiseComponents_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_initialiseComponents_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "initialiseComponents"
                , initialiseComponents_function_type(&::CEGUI::Window::initialiseComponents)
                , default_initialiseComponents_function_type(&GridLayoutContainer_wrapper::default_initialiseComponents) );
        
        }
        { //::CEGUI::Window::isHit
        
            typedef bool ( ::CEGUI::Window::*isHit_function_type )( ::CEGUI::Vector2 const &,bool const ) const;
            typedef bool ( GridLayoutContainer_wrapper::*default_isHit_function_type )( ::CEGUI::Vector2 const &,bool const ) const;
            
            GridLayoutContainer_exposer.def( 
                "isHit"
                , isHit_function_type(&::CEGUI::Window::isHit)
                , default_isHit_function_type(&GridLayoutContainer_wrapper::default_isHit)
                , ( bp::arg("position"), bp::arg("allow_disabled")=(bool const)(false) ) );
        
        }
        { //::CEGUI::LayoutContainer::layoutIfNecessary
        
            typedef void ( ::CEGUI::LayoutContainer::*layoutIfNecessary_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_layoutIfNecessary_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "layoutIfNecessary"
                , layoutIfNecessary_function_type(&::CEGUI::LayoutContainer::layoutIfNecessary)
                , default_layoutIfNecessary_function_type(&GridLayoutContainer_wrapper::default_layoutIfNecessary) );
        
        }
        { //::CEGUI::Window::performChildWindowLayout
        
            typedef void ( ::CEGUI::Window::*performChildWindowLayout_function_type )(  ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_performChildWindowLayout_function_type )(  ) ;
            
            GridLayoutContainer_exposer.def( 
                "performChildWindowLayout"
                , performChildWindowLayout_function_type(&::CEGUI::Window::performChildWindowLayout)
                , default_performChildWindowLayout_function_type(&GridLayoutContainer_wrapper::default_performChildWindowLayout) );
        
        }
        { //::CEGUI::Window::setLookNFeel
        
            typedef void ( ::CEGUI::Window::*setLookNFeel_function_type )( ::CEGUI::String const & ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_setLookNFeel_function_type )( ::CEGUI::String const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "setLookNFeel"
                , setLookNFeel_function_type(&::CEGUI::Window::setLookNFeel)
                , default_setLookNFeel_function_type(&GridLayoutContainer_wrapper::default_setLookNFeel)
                , ( bp::arg("look") ) );
        
        }
        { //::CEGUI::Window::setMargin
        
            typedef void ( ::CEGUI::Window::*setMargin_function_type )( ::CEGUI::UBox const & ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_setMargin_function_type )( ::CEGUI::UBox const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "setMargin"
                , setMargin_function_type(&::CEGUI::Window::setMargin)
                , default_setMargin_function_type(&GridLayoutContainer_wrapper::default_setMargin)
                , ( bp::arg("margin") ) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( GridLayoutContainer_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&GridLayoutContainer_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( GridLayoutContainer_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            
            GridLayoutContainer_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&GridLayoutContainer_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("group"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::LayoutContainer::update
        
            typedef void ( ::CEGUI::LayoutContainer::*update_function_type )( float ) ;
            typedef void ( GridLayoutContainer_wrapper::*default_update_function_type )( float ) ;
            
            GridLayoutContainer_exposer.def( 
                "update"
                , update_function_type(&::CEGUI::LayoutContainer::update)
                , default_update_function_type(&GridLayoutContainer_wrapper::default_update)
                , ( bp::arg("elapsed") ) );
        
        }
        { //::CEGUI::Window::writeXMLToStream
        
            typedef void ( ::CEGUI::Window::*writeXMLToStream_function_type )( ::CEGUI::XMLSerializer & ) const;
            typedef void ( GridLayoutContainer_wrapper::*default_writeXMLToStream_function_type )( ::CEGUI::XMLSerializer & ) const;
            
            GridLayoutContainer_exposer.def( 
                "writeXMLToStream"
                , writeXMLToStream_function_type(&::CEGUI::Window::writeXMLToStream)
                , default_writeXMLToStream_function_type(&GridLayoutContainer_wrapper::default_writeXMLToStream)
                , ( bp::arg("xml_stream") ) );
        
        }
    }

}
