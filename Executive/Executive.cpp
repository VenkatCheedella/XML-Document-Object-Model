/////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point of the application                  //
//                                                                 //
// Application: CSE687 - Object Oriented Design-XML Document Model //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013         //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity    //
//              vcheedel@syr.edu                                   //
/////////////////////////////////////////////////////////////////////

/*
  Package Operations
  =========================

  Build a XML tree for a given the given input. The input can be either string or filename.
  
  Required Files
  ==================

  Executive, FileSystem.h, FileSystem.cpp, FileReader.h, FileReader.cpp, TextXmlDocument.h
  TextXmlDOcument.cpp, XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlReader.h, XMlReader.cpp
  Display.h, Display.cpp

  Build Process
  ===============
  From the Visual Studio Developer's Command Prompt:
  devenv XmlDocument.sln /rebuild debug

  Maintenance History
  =========================

  ver 1.0  : 23 Mar 2015
  - First Release

*/

#include <iostream>
#include <string>
#include <memory>
#include "../TestXmlDocument/TestXMLDocument.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include "../XmlReader/XmlReader.h"
#include "../FileReader/FileReader.h"
#include "../Display/Display.h"

using namespace std;

class Executive
{
public:
	Executive(int argc, char* argv[]);
	void procCommandLine();
private:	
	std::vector<std::string> cmdargs;
	string filename;
};

Executive::Executive(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			cmdargs.push_back(argv[i]);
	}	
}

void Executive::procCommandLine()
{
	std::string inputXML;
	if (cmdargs.size() != 0)
	{
		FileReader freader(cmdargs[0]);
		inputXML = freader.convertoString();
		filename = cmdargs[0];
	}
	else
	{
		string body1 = "<?xml version=\"1.1\" encoding=\"UTF - 8\" ?><?xml-proc color=\"black\" background=\"white\" ?><!--  XML test case  -->";
		string body2 = "<LectureNote course=\"CSE681\"><title>XML Example #1</title><reference><title>Programming Microsoft .Net</title><author>";
		inputXML = body1 + body2 + "Jeff Prosise<note Company=\"Wintellect\"/></author><publisher name=\"venkat\">MicrosoftPress</publisher><date>2002</date><page>608</page></reference><comment>Description ofPCDATA</comment></LectureNote>";
	}			
	if (inputXML != "")
	{
		XmlProcessing::XmlDocument xmlDocument(inputXML);
		xmlDocument.controller();
		TestXMLDocument testXMLDoc(xmlDocument);
		testXMLDoc.testStub(filename);
	}
	else
		Display::printStatus("The file is not present in the given path");
}

int main(int argc, char* argv[])
{
	try
	{
		Executive exec(argc, argv);
		exec.procCommandLine();
		/*if (argc < 2)
		{			
			Display::printStatus("Please provide the XML file or XMLstring in the commandline");
		}*/
	}		
	catch (std::exception& ex)
	{
		std::cout << "\n  threw std::exception due to ill-formed XML: " << ex.what() << "\n\n";
	}
	catch (...)
	{
		std::cout << "\n  threw non-standard exception due to ill-formed XML: ";
		std::cout << "\n\n";
	}
}