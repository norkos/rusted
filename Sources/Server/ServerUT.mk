TARGET:=ServerUT
TYPE:=application

SOURCES+=../Common/UnitTests/mainGoogleTestUT.cpp
SOURCES+=Game/UnitTests/PlayerContainerTest.cpp
SOURCES+=Game/Actions/UnitTests/AttackTest.cpp
SOURCES+=Game/Actions/UnitTests/BuildShipTest.cpp
SOURCES+=Game/Actions/UnitTests/ActionBuilderTest.cpp
SOURCES+=Game/Actions/UnitTests/ActionPerformerTest.cpp
SOURCES+=Game/UnitTests/UniverseLoaderTest.cpp
SOURCES+=Game/UnitTests/ObjectFactoryTest.cpp
SOURCES+=UnitTests/ConnectionStub.cpp
SOURCES+=DataBase/UnitTests/DataBaseModuleTest.cpp
SOURCES+=DataBase/UnitTests/DataBaseNodeTest.cpp
SOURCES+=DataBase/UnitTests/XmlDataProviderTest.cpp

CFLAGS+=-I$(TARGET_BASE)
CFLAGS+=-I$(TARGET_BASE)/../
CFLAGS+=-I$(TARGET_BASE)/../Common
CFLAGS+=-I$(TARGET_BASE)/../External 
CFLAGS+=-I/usr/include/libxml2

LDFLAGS=-L. -L$(BUILD) -lServer -lCommon -lCake -lpthread -lboost_system -lxml2 -lgtest -lgmock 

DEPENDENCIES+=libServer.a
DEPENDENCIES+=libCommon.a
DEPENDENCIES+=libCake.a
