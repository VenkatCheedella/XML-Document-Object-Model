#ifndef TESTXMLDOCUMENT_H
#define TESTXMLDOCUMENT_H


/////////////////////////////////////////////////////////////////////
// TestXMLDocument.h - To provide public interfaces to the XML tree//
//                                                                 //
// Application: CSE687 - Object Oriented Design-XML Document Model //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013         //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity    //
//              vcheedel@syr.edu                                   //
/////////////////////////////////////////////////////////////////////


/*

Package Operations
===================

It provide interfaces to the client to get the requiered information from the tree
such as attributes, desired tag information, children for an element. A child can be
added or removed for a certain element.
Demonstrated the above stated functionality.

Required Files
===============

FileSystem.h, FileSystem.cpp, FileReader.h, FileReader.cpp, TextXmlDocument.h
TextXmlDOcument.cpp, XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp, XmlReader.h, XmlReader.cpp
Display.h, Display.cpp

Build Process
===============
From the Visual Studio Developer's Command Prompt:
devenv XmlDocument.sln /rebuild debug


Public Interfaces
==================

sPtr getElementforID(std::string id);							--> Retreive an element for an Id provided if present
sPtr recursiveSearchForId(std::string id, sPtr tPtr);			--> To search recursively a tree to find an element of an ID
vector<sPtr>& getElementsforTag(std::string tag, vector<sPtr>& tagElemsVector);	--> Retrieve a list of element for a tag provided if present
vector<sPtr>& recursiveSearchForTag(std::string tag, sPtr s, vector<sPtr>& tagElemsVector); --> Search the recursively for a tag				
bool addElementToTree(string elem, string stag, unsigned int type);		--> To add an element to a parent in the given tree
bool removeElemFromTree(sPtr elemPtr);									--> Remove an element from tree if present
bool removeElemFromTreebyTag(string parentTag, string childTag);		--> Remove a child element from a tree for a given parent if present by tag
bool removeElemFromTreebyID(string parentId, string childTag);			--> Remove a child element from a tree for a given parent if present by ID
bool recSrchForDelElem(sPtr _pElem, sPtr elemPtr);						--> Search tree recursively for an element
attribs getAttributesOfElem(sPtr pElem);								--> Get the attributes of an element
bool addAttribute(string tag, pair<string, string> attrib);				--> Add the attribute of an element
bool deleteAttribute(string tag, string value);							--> Delete the attributes of an element
void WriteXMLtoFile();


Maintenance History
=========================

ver 1.0  : 23 Mar 2015
- First Release
*/


#include <iostream>
#include "../XmlDocument/XmlDocument.h"
#include <string>
#include "../XmlElement/XmlElement.h"
#include "../Display/Display.h"
#include <memory>
#include <vector>

using namespace std;
using sPtr = std::shared_ptr < XmlProcessing::AbstractXmlElement >;

class TestXMLDocument
{
public:	
	using attribs = std::vector<std::pair<std::string, std::string>>;
	//TestXMLDocument():_xmlDoc(new XmlProcessing::XmlDocument()){}
	TestXMLDocument(XmlProcessing::XmlDocument& xmlDoc);
	~TestXMLDocument();
	void testStub(string input);
	sPtr getElementforID(std::string id);
	sPtr recursiveSearchForId(std::string id, sPtr tPtr);
	vector<sPtr>& getElementsforTag(std::string tag, vector<sPtr>& tagElemsVector);
	vector<sPtr>& recursiveSearchForTag(std::string tag, sPtr s, vector<sPtr>& tagElemsVector);
	void setpDocElem(sPtr pDocE){ _pDocElem = pDocE; }	
	bool addElementToTree(string elem, string stag, unsigned int type);	
	bool removeElemFromTree(sPtr elemPtr);	
	bool removeElemFromTreebyTag(string parentTag, string childTag);
	bool removeElemFromTreebyID(string parentId, string childTag);
	bool recSrchForDelElem(sPtr _pElem, sPtr elemPtr);	
	attribs getAttributesOfElem(sPtr pElem);
	void testStub2(string input);
	//attribs getAttributes(sPtr elemPtr);
	bool addAttribute(string tag, pair<string, string> attrib);
	bool deleteAttribute(string tag, string value);
	void WriteXMLtoFile(string filename);
	vector<sPtr>& getChildren(string tag, vector<sPtr>& childPtrs);
	void moveOpsForTaggedElem();
	void createTreeWithoutSrc();
private:
	sPtr _pDocElem = nullptr;
	vector<sPtr> tagElementsVec;
	XmlProcessing::XmlDocument& _xmlDoc;
	sPtr _pRootTagElem = nullptr;
	attribs attributes;
	void addElemToTree(sPtr pElemPtr, string elem);
	bool getAttributeElem(XmlProcessing::ProcInstrElement* pPtr, string id);
	bool getAttributeElem(XmlProcessing::XmlDeclarElement* pPtr, string id);
	
};

#endif