APPNAME=Client

SOURCES+=main.cpp

LDFLAGS+=-L$(BUILD)
LDFLAGS+=-L../External/CEGUI-0.7.5/cegui/src/.libs/
LDFLAGS+=-L../External/CEGUI-0.7.5/cegui/src/RendererModules/Ogre/.libs/
LDFLAGS+=-lClient
LDFLAGS+=-lOgreMain
LDFLAGS+=-lCEGUIBase
LDFLAGS+=-lCEGUIOgreRenderer
LDFLAGS+=-lOIS
LDFLAGS+=-lCommon
LDFLAGS+=-lCake
LDFLAGS+=-lpthread
LDFLAGS+=-lboost_system
LDFLAGS+=-lxml2 

CFLAGS+=-I../ -I. 
CFLAGS+=-I../Common 
CFLAGS+=-I../External
CFLAGS+=-I/usr/include/libxml2
CFLAGS+=-I/usr/include/OGRE
CFLAGS+=-I$(BUILD)/CEGUI-0.7.5/cegui/include/RendererModules/Ogre
CFLAGS+=-I$(BUILD)/CEGUI-0.7.5/cegui/include/

DEPENDENCIES+=libClient.a libCommon.a libCake.a

RESOURCES+=runClient
RESOURCES+=runTestClient

include Makefile.leaf

