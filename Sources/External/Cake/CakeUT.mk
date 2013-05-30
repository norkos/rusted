TARGET:=CakeUT
TYPE:=application

CFLAGS+=-I. -I.. -I$(TARGET_BASE) -I$(TARGET_BASE)/..
LDFLAGS+=-L. -L$(BUILD) -lCake -lpthread -lgtest -lgmock

SOURCES+=Serialization/UnitTests/TmsTest.cpp
SOURCES+=Networking/Protocol/UnitTests/ProtocolTest.cpp
SOURCES+=Utils/UnitTests/StringListTest.cpp
SOURCES+=mainUT.cpp

DEPENDENCIES+=libCake.a
DEPENDENCIES+=$(TARGET_BASE)/Networking/Protocol/UnitTests/SampleProtocol.hpp

PROTOC=$(TARGET_BASE)/Networking/Protocol/protoc.py
PROTO_XML=$(TARGET_BASE)/Networking/Protocol/UnitTests/SampleProtocol.xml

$(TARGET_BASE)/Networking/Protocol/UnitTests/SampleProtocol.hpp: $(PROTOC) $(PROTO_XML)
	$(PROTOC) --output $@ $(PROTO_XML) --namespace Cake::Networking::Protocol

