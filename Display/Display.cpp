/////////////////////////////////////////////////////////////////////
// Display.cpp - Implementation of display class                   //
//                                                                 //
// Application: CSE687 - Object Oriented Design-XML Document Model //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013         //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity    //
//              vcheedel@syr.edu                                   //
/////////////////////////////////////////////////////////////////////



#include "Display.h"
using namespace std;


//------------<Promotion constructor>-----------------------------

Display::Display(XmlProcessing::XmlDocument& xmlDoc):_xmlDoc(xmlDoc)
{

}

//--------------<Destructor>------------------------------

Display::~Display()
{
}

//-----------------<Utility for title>-----------------------

void Display::title(const string& titlebar)
{
	std::cout << "\n" << titlebar << endl;
	for (unsigned int i = 0; i < titlebar.length(); i++)
		std::cout << "=";
}

//-----------------<To display the XML-Tree constructed>-----------------

void Display::displayXMLToString()
{
	std::cout << "\n" << _xmlDoc.getDocElement()->toString() << endl;
}


//-----------------<Display the information after attributes get deleted>----------

void Display::deleteAttributeInfo(bool delAttribStatus)
{
	if (delAttribStatus == true)
	{
		std::cout << "\n" << "XML Tree after deletion of an attribute, name = venkat";
		displayXMLToString();
	}		
	else
		std::cout << "\n" << "XML doesn't have given tag" << endl;
}

//---------------------<Display the tree after attributes get added>----------------

void Display::addAttribStatusInfo(bool addAttribStatus)
{
	if (addAttribStatus == true)
	{
		std::cout << "\n" << "XML Tree after addition of attribute{name= Jim} to given element";
		displayXMLToString();
	}		
	else
		std::cout << "\n" << "Given element is not present in the XML tree" << endl;
}

//-------------------------<Display the retrieved attributes>------------------

void Display::getAttributesOfElemInfo(attribs elemattribs)
{
	if (elemattribs.size() != 0)
	{
		for (auto attrib : elemattribs)
			std::cout << "\n" << attrib.first << "= " << "\"" << attrib.second << "\"" << endl;
	}
	else
		std::cout << "\n" << "Attributes are not present to the given element" << endl;
}

//-------------------<Display the tree after the given elem get deleted>-------------------

void Display::removeElemFromTreebyIDInfo(bool delStatus)
{
	if (delStatus == true)
	{
		std::cout << "\n" << "XML Tree after deletion of the element with value venkat is ";
		displayXMLToString();
	}		
	else
		std::cout << "The given ID is not present in the tree" << endl;
}

//----------------------<Display the tree after the tag get deleted>----------------

void Display::removeElemFromTreebyTagInfo(bool delStatus)
{
	if (delStatus == true)
	{
		std::cout << "\n" << "XML after the deletion of child-note";
		displayXMLToString();
	}		
	else
		std::cout << "\n" << "The given child is not present in the tree " << "\n";
}

//----------------------<Display the tree after the element get added to tree>-----------------

void Display::addElementToTreeInfo(bool status)
{	
	if (status == true)
	{
		std::cout << "\n" << "XML after the addition of the element: <pChild course=\"CSE-681\"> </pChild>," << "\n";
		displayXMLToString();
	}		
	else
		std::cout << "\n" << "The searched tag is not present in the XML" << "\n";
}

//------------------------<display the tree after the element get added(searched by ID)>---------------

void Display::addElementtoTreebyIdInfo(bool status)
{
	if (status == true)
	{
		std::cout << "\n" << "XML after the addition of the element: <pChild course=\"CSE-681\"> </pChild>,";
		displayXMLToString();
	}		
	else
		std::cout << "\n" << "Either XML doesn't have tagged elems or the searched id is not present in the XML" << "\n";
}

//-----------------------<To print a string, utility>--------------------------

void Display::printStatement(const string& statement)
{
	std::cout << "\n" << statement << endl;
}

//------------------------<Display if ID are present in the tree after the search>-----------------------

void Display::disElemIDInfo(sPtr tempPtr)
{	
	if (tempPtr != nullptr)
		std::cout << "\n" << "The given id is present in the " << tempPtr->value() << " tag" << "\n";
	else
		printStatement("The given id is not present the XML Tree");
}

//--------------------------<Display the list of tags after the search>--------------------

void Display::getElementsForTagInfo(vector<sPtr> tagElementsVec)
{
	if (tagElementsVec.size() != 0)
		std::cout << "\n" << "The given tag is present at " << tagElementsVec.size() << " places in the given XML Tree" << endl;
	else
		printStatement("The given tag is not present in the XML document");
}

//----------------------< Display children>------------------------------

void Display::dispChildren(vector<sPtr> children)
{
	if (children.size() != 0)
	{
		std::cout << "\n" << "children of the given element :" << endl;
		for (auto s : children)
			std::cout << s->value() << endl;
	}
	else
		printStatement("The element donot have any children");
}

//----------------<Test Stub>---------------------------------

#ifdef TEST_DISPLAY
int main()
{
	Display::printStatus("This is package is used by other packages like TestXmlDocument, XMlDocument pacakge to display the results of the operations performed");
	Display::printStatus(" Retreive an element for an Id provided if present");
	Display::printStatus("To search recursively a tree to find an element of an ID");
	Display::printStatus("Retrieve a list of element for a tag provided if present");
	Display::printStatus("Search the recursively for a tag");
	Display::printStatus(" To add an element to a parent in the given tree");
}

#endif