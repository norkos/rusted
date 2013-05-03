#! /usr/bin/env python

import sys
from xml.dom import minidom

messagesHpp = open("Messages/UnitTests/MessagesTest.cpp", "w")
messages = minidom.parse('Messages/Messages.xml')

def genHeader():
	messagesHpp.write(
		"/* this file is autogenerated, do not edit! */\n\n"
		"#include <gtest/gtest.h>\n"
		"#include <iostream>\n\n"
        "#include \"Cake/Diagnostics/Logger.hpp\"\n"
		"#include <RustedCodec/SimpleWriteBuffer.hpp>\n"
		"#include <RustedCodec/SimpleReadBuffer.hpp>\n\n"
		"#include <Messages/Messages.hpp>\n\n"
	)

def genTests():
	for message in messages.childNodes[0].getElementsByTagName("message"):
		messagesHpp.write(
			"TEST(MessagesTest, Message_" + message.getAttribute("id") + ")\n"
			"{\n"
			"\tusing ::Common::RustedCodec::SimpleWriteBuffer;\n"
			"\tusing ::Common::RustedCodec::SimpleReadBuffer;\n"
			"\tusing ::Common::Messages::AbstractMessage;\n"
			"\tusing ::Common::Messages::" + message.getAttribute("id") + ";\n\n"
			"\t" + message.getAttribute("id") + " inMessage;\n"
		)

		for param in message.getElementsByTagName("param"):
			messagesHpp.write("\t")
			if param.getAttribute("type") == "boolean":
				messagesHpp.write("inMessage." + param.getAttribute("name") + " = true;\n")
			elif param.getAttribute("type") == "string":
				messagesHpp.write("inMessage." + param.getAttribute("name") + " = \"some test string\";\n")
			elif param.getAttribute("type") == "int32":
				messagesHpp.write("inMessage." + param.getAttribute("name") + " = 0xf00d;\n")
			else:
				print "unknown param type: " + param.getAttribute("type") + "!"
				sys.exit(1)

		messagesHpp.write(
			"\n"
			"\tstd::vector<char> raw_buf;\n"
			"\tSimpleWriteBuffer buf(raw_buf);\n"
			"\tinMessage.serialize(buf);\n\n"
			"\tSimpleReadBuffer read_buf(raw_buf);\n"
			"\tboost::shared_ptr<AbstractMessage> outMessage = ::Common::Messages::MessageFactory::create(read_buf);\n\n"
			"\tEXPECT_TRUE(0 != dynamic_cast<" + message.getAttribute("id") + " *>(outMessage.get()));\n"
			"\tEXPECT_EQ(::Common::Messages::Id::" + message.getAttribute("id") + ", outMessage->getId());\n"
		)

		messagesHpp.write(
			"\tLOG_INFO << *dynamic_cast<" + message.getAttribute("id") + " *>(outMessage.get());\n")

		for param in message.getElementsByTagName("param"):
			messagesHpp.write(
				"\tEXPECT_TRUE(inMessage." + param.getAttribute("name") + " == dynamic_cast<" + message.getAttribute("id") +
				" *>(outMessage.get())->" + param.getAttribute("name") + ");\n"
			)

		messagesHpp.write(
			"}\n\n"
		)

genHeader()
genTests()

print "Messages/UnitTests/MessagesTest.cpp written"

