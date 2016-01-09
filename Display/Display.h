#ifndef DISPLAY_H
#define DISPLAY_H

/////////////////////////////////////////////////////////////////////
// Display.h - Display the results to console                      //
//                                                                 //
// Application: CSE687 - Object Oriented Design-XML Document Model //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013         //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity    //
//              vcheedel@syr.edu                                   //
/////////////////////////////////////////////////////////////////////

/*


Purpose: To provide a facility to demonstrate the requirements to the user.

Public Interfaces
=================

void title(const string& titlebar);					--> An utility to display the headline of a specific test
void printStatement(const string& statement);		--> Display a string
void displayXMLToString();							--> Display the XML tree structure to user
void disElemIDInfo(sPtr tempPtr);					--> Display the elements information where a given ID is present
void getElementsForTagInfo(vector<sPtr> tagElementsVec);--> Display the elements where the given tag.
void addElementToTreeInfo(bool status);				--> Display the tree after a new element added to the XML tree by ID
void addElementtoTreebyIdInfo(bool status);			--> Display the tree after a new element added to the XML tree by Tag
void removeElemFromTreebyTagInfo(bool delStatus);   --> Display the tree after an element is removed for a given tag
void removeElemFromTreebyIDInfo(bool delStatus);    --> Display the tree after an element is removed for a given id
void getAttributesOfElemInfo(attribs elemattribs);	--> Display the attributes for a given element
void addAttribStatusInfo(bool addAttribStatus);		--> Display the tree after an attribute is added to the tree
void deleteAttributeInfo(bool delAttribStatus);		--> Display the tree after an attribute is removd from the tree


///////////////////////////////////////////////////////////////
//  Required files:                                          //
//    TestXMLDocument.h, TestXMLDocument.cpp,XmlDocument.h   //
//	  XmlDocument.cpp, XmlElement.h, XmlElement.cpp          //
//                                                           //
//                                                           //
///////////////////////////////////////////////////////////////


Build Process
===============
From the Visual Studio Developer's Command Prompt:
devenv XmlDocument.sln /rebuild debug

Maintenance History
==========================

ver 1.0  : 23 feb 2015
- First Release

*/

#include "../TestXmlDocument/TestXMLDocument.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include <iostream>
#include <string>

using sPtr = std::shared_ptr < XmlProcessing::AbstractXmlElement >;
using attribs = std::vector<std::pair<std::string, std::string>>;

class Display
{
public:	
	Display(XmlProcessing::XmlDocument& xmlDoc);
	~Display();
	void title(const string& titlebar);
    void printStatement(const string& statement);
    void displayXMLToString();
	void disElemIDInfo(sPtr tempPtr);
	void getElementsForTagInfo(vector<sPtr> tagElementsVec);
	void addElementToTreeInfo(bool status);
	void addElementtoTreebyIdInfo(bool status);
	void removeElemFromTreebyTagInfo(bool delStatus);
	void removeElemFromTreebyIDInfo(bool delStatus);
	void getAttributesOfElemInfo(attribs elemattribs);
	void addAttribStatusInfo(bool addAttribStatus);
	void deleteAttributeInfo(bool delAttribStatus);
	void dispChildren(vector<sPtr> children);
	static void printStatus(const string& stat){ std::cout << "\n" << stat << endl; }
private:
	XmlProcessing::XmlDocument _xmlDoc;
	sPtr tempPtr;
};

#endif